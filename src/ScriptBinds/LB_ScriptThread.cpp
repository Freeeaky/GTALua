// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptBinds.h"
#include "ScriptEngine/ScriptEngine.h"
#include "thirdparty/ScriptHookV/ScriptHookV.h"
#include "UTIL/UTIL.h"
using namespace ScriptBinds::ScriptThread;

// =================================================================================
// ScriptThread 
// =================================================================================
LuaScriptThread::LuaScriptThread(string sName)
{
	m_sName = sName;
	m_bActive = false;
	m_bResetting = false;
	m_bIdleState = false;
	m_iWaitTime = 0;
	m_iNextRun = 0;

	// Main Thread
	m_bIsMainThread = sName == "main_thread";
	m_bRunsOnMainThread = !m_bIsMainThread;
	if (m_bIsMainThread)
		m_lThreadList = luabind::newtable(lua->State());
	else
		m_lThreadList = lua_nil;
}
LuaScriptThread::~LuaScriptThread()
{
	m_bActive = false;
	m_bResetting = false;
	m_iWaitTime = 0;

	// unregister thread here in future
}

// =================================================================================
// Wait 
// =================================================================================
void LuaScriptThread::Wait(DWORD uiTime)
{
	// Reset
	if (m_bActive && m_bResetting)
	{
		lua->PushString("ScriptThreadReset");
		throw luabind::error(lua->State());
		return;
	}

	// No longer active
	if (!m_bActive)
	{
		lua->PushString("ScriptThread:Wait called on an invalid thread!");
		throw luabind::error(lua->State());
	}

	// Wait
	m_iWaitTime = uiTime;
}

// =================================================================================
// IsCallbackPresent 
// =================================================================================
bool LuaScriptThread::IsCallbackPresent(char* sName)
{
	lua->GetMutex()->Lock();

	// Check if callback is present
	m_self.get(lua->State());
	if (lua->IsNil())
	{
		lua->Pop(1);
		lua->GetMutex()->Unlock();
		return false;
	}
	lua->GetField(sName, -1);
	if (lua->IsNil())
	{
		lua->Pop(2);
		lua->GetMutex()->Unlock();
		return false;
	}
	lua->Pop(2);

	lua->GetMutex()->Unlock();
	return true;
}

// =================================================================================
// Call Lua Callback
// Returns true when normal exit
// =================================================================================
bool LuaScriptThread::Call_LuaCallback(char* sName)
{
	try
	{
		call<void>(sName);
	}
	catch (luabind::error& e)
	{
		// Reset
		if (lua->IsString() && strcmp(lua->GetString(), "ScriptThreadReset") == 0)
		{
			lua->Pop(1);
			return true;
		}

		// Error
		printf("[LuaScriptThread] Thread %s:%s caused an error!\n", m_sName.c_str(), sName);

		if (lua->IsString())
		{
			lua->PrintErrorMessage(lua->GetString(), true, true);
			lua->Pop(1);
		}
		else
			lua->PrintErrorMessage(const_cast<char*>(e.what()), true, true);

		return false;
	}
	catch (std::exception& e)
	{
		printf("[LuaScriptThread] Thread %s:%s caused an error: %s\n", m_sName.c_str(), sName, e.what());
		return false;
	}
	catch (...)
	{
		printf("LuaScriptThread] Thread %s:%s caused an error: (unknown exception thrown)\n", m_sName.c_str(), sName);
		return false;
	}

	// Normal Exit
	return true;
}

// =================================================================================
// Start 
// =================================================================================
void LuaScriptThread::Start()
{
	// Message
	printf("[LuaScriptThread] Thread %s started\n", m_sName.c_str());

	// Flag
	m_bActive = true;

	// Run
	while (m_bActive)
	{
		// Normal Threads: Run
		if (!m_bIsMainThread)
			Run();

		// Main Thread: Run
		if (m_bIsMainThread)
			Run_MainThread();

		// Main Thread will never be in idle state
		if (!m_bIsMainThread && m_bActive)
			Run_IdleState();
	}

	// Flag
	m_bActive = false;

	// Message
	printf("[LuaScriptThread] Thread %s quit\n", m_sName.c_str());
}

// =================================================================================
// Run 
// =================================================================================
bool LuaScriptThread::Run()
{
	// Idle State
	m_bIdleState = false;

	// Coroutine
	if (!m_bRunsOnMainThread && !m_bIsMainThread)
	{
		lua->GetMutex()->Lock();
		if (!Call_LuaCallback("SetupCoroutine"))
		{
			printf("[LuaScriptThread] Thread %s failed to setup its coroutine (lua thread)!", m_sName.c_str());
			lua->GetMutex()->Unlock();
			return false;
		}
		lua->GetMutex()->Unlock();
	}

	// Call
	bool bNormalExit = true;
	while (bNormalExit && m_bActive && !m_bResetting)
	{
		// Callback
		lua->GetMutex()->Lock();
		bNormalExit = Call_LuaCallback("Tick");
		lua->GetMutex()->Unlock();

		// Break
		if (m_bRunsOnMainThread)
			break;

		// Wait
		ScriptHook::ScriptWait(m_iWaitTime);
		m_iWaitTime = 1;
	}

	// Quit
	if (!m_bRunsOnMainThread && !m_bActive)
	{
		printf("[LuaScriptThread] Thread %s quit\n", m_sName.c_str());
		return false;
	}

	// OnError
	if (!bNormalExit && IsCallbackPresent("OnError"))
	{
		lua->GetMutex()->Lock();
		Call_LuaCallback("OnError");
		lua->GetMutex()->Unlock();
		return false;
	}

	// smooth
	return true;
}

// =================================================================================
// Idle State
// Thread is still alive, but idling
// =================================================================================
void LuaScriptThread::Run_IdleState()
{
	// Idle
	m_bIdleState = true;

	// Idle Loop
	while (m_bActive && m_bIdleState)
	{
		// Handle Reset
		if (m_bResetting)
		{
			m_bResetting = false;
			m_bIdleState = false;
			printf("[LuaScriptThread] Thread %s reset\n", m_sName.c_str());

			return;
		}

		// Idle State
		m_bIdleState = true;

		// Wait
		ScriptHook::ScriptWait(5);
	}

	// Idle
	m_bIdleState = false;
}

// =================================================================================
// Resest 
// =================================================================================
void LuaScriptThread::Reset()
{
	m_bResetting = true;
}

// =================================================================================
// Kill 
// =================================================================================
void LuaScriptThread::Kill()
{
	m_bActive = false;
	m_bResetting = false;
}

// =================================================================================
// Bind 
// =================================================================================
void ScriptBinds::ScriptThread::Bind()
{
	luabind::module(lua->State())
	[
		luabind::class_<LuaScriptThread>("CScriptThread")
		.def(luabind::constructor<string>())
		.def("GetName", &LuaScriptThread::GetName)
		.def("IsRunning", &LuaScriptThread::IsRunning) // is running
		.def("IsActive", &LuaScriptThread::IsActive) // is started
		.def("Wait", &LuaScriptThread::Wait, luabind::yield)
		.def("Reset", &LuaScriptThread::Reset)
		.def("internal_Kill", &LuaScriptThread::Kill)
		.def_readwrite("ThreadList", &LuaScriptThread::m_lThreadList)
		.def_readonly("m_bRunsOnMainThread", &LuaScriptThread::m_bRunsOnMainThread)
		.def_readonly("m_iNextRun", &LuaScriptThread::m_iNextRun)
	];
}