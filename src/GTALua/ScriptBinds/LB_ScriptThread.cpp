// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptBinds.h"
#include "thirdparty/ScriptHookV/ScriptHookV.h"
using namespace ScriptBinds::ScriptThread;

// =================================================================================
// ScriptThread 
// =================================================================================
LuaScriptThread::LuaScriptThread(string sName)
{
	m_sName = sName;
	m_bActive = false;
	m_bResetting = false;
}
LuaScriptThread::~LuaScriptThread()
{
	m_bActive = false;
	m_bResetting = false;
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
	ScriptHook::ScriptWait(uiTime);
}

// =================================================================================
// IsCallbackPresent 
// =================================================================================
bool LuaScriptThread::IsCallbackPresent(char* sName)
{
	lua->Lock();

	// Check if callback is present
	m_self.get(lua->State());
	if (lua->IsNil())
	{
		lua->Pop(1);
		lua->Unlock();
		return false;
	}
	lua->GetField(sName, -1);
	if (lua->IsNil())
	{
		lua->Pop(2);
		lua->Unlock();
		return false;
	}
	lua->Pop(2);
	lua->Unlock();
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
		//Run();
		Run();

		//
		if (m_bActive)
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
void LuaScriptThread::Run()
{
	// Check if callback is present
	if (!IsCallbackPresent("Run"))
	{
		printf("[LuaScriptThread] Thread %s has no Run callback!", m_sName.c_str());
		return;
	}

	// Coroutine
	lua->Lock();
	if (!Call_LuaCallback("SetupCoroutine"))
	{
		printf("[LuaScriptThread] Thread %s failed to setup its coroutine (lua thread)!", m_sName.c_str());
		return;
	}
	lua->Unlock();

	// Call
	bool bNormalExit = true;
	while (bNormalExit && m_bActive && !m_bResetting)
	{
		lua->Lock();
		bNormalExit = Call_LuaCallback("Tick");
		lua->Unlock();

		ScriptHook::ScriptWait(0);
	}

	// Quit
	if (!m_bActive)
	{
		printf("[LuaScriptThread] Thread %s quit\n", m_sName.c_str());
		return;
	}

	// OnError
	if (!bNormalExit && IsCallbackPresent("OnError"))
		Call_LuaCallback("OnError");
}

// =================================================================================
// Idle State
// Thread is still alive, but idling
// =================================================================================
void LuaScriptThread::Run_IdleState()
{
	while (m_bActive)
	{
		// Handle Reset
		if (m_bResetting)
		{
			m_bResetting = false;
			printf("[LuaScriptThread] Thread %s reset\n", m_sName.c_str());

			return;
		}

		// Wait
		ScriptHook::ScriptWait(5);
	}
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
		.def("IsActive", &LuaScriptThread::IsActive) // is valid in general
		.def("Wait", &LuaScriptThread::Wait, luabind::yield)
		.def("Reset", &LuaScriptThread::Reset)
		.def("internal_Kill", &LuaScriptThread::Kill)
	];
}