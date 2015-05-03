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
		throw ScriptThreadReset();

	// No longer active
	if (!m_bActive)
	{
		lua->PushString("ScriptThread:Wait called on an invalid thread!");
		throw luabind::error(lua->State());
	}

	// Wait
	scriptWait(uiTime);
}

// =================================================================================
// IsCallbackPresent 
// =================================================================================
bool LuaScriptThread::IsCallbackPresent(char* sName)
{
	// Check if callback is present
	m_self.get(lua->State());
	if (lua->IsNil())
	{
		lua->Pop(1);
		return false;
	}
	lua->GetField(sName, -1);
	if (lua->IsNil())
	{
		lua->Pop(2);
		return false;
	}
	lua->Pop(2);
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
	catch (ScriptThreadReset) {
		return true;
	}
	catch (luabind::error& e) {
		printf("[LuaScriptThread] Thread %s:%s caused an error!\n", m_sName.c_str(), sName);

		if (lua->IsString(-1))
			lua->PrintErrorMessage(lua->GetString(-1), true, false);
		else
			lua->PrintErrorMessage(const_cast<char*>(e.what()), true, false);
		lua->Pop(1);
		return false;
	}
	catch (std::exception& e) {
		printf("[LuaScriptThread] Thread %s:%s caused an error: %s\n", m_sName.c_str(), sName, e.what());
		return false;
	}
	catch (...) {
		printf("LuaScriptThread] Thread %s:%s caused an error: (unknown exception thrown)\n", m_sName.c_str(), sName);
		return false;
	}

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
		Run();

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

	// Call
	bool bNormalExit = Call_LuaCallback("Run");

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
		scriptWait(5);
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
		.def("Wait", &LuaScriptThread::Wait)
		.def("Reset", &LuaScriptThread::Reset)
		.def("internal_Kill", &LuaScriptThread::Kill)
	];
}