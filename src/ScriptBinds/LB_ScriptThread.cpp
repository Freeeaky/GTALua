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
	printf("LuaScriptThread::~\n");
}

// =================================================================================
// Resest 
// =================================================================================
struct ScriptThreadReset : public std::exception {};
void LuaScriptThread::Reset()
{
	if (!m_bActive)
		m_bResetting = true;
}

// =================================================================================
// Run 
// =================================================================================
void LuaScriptThread::Run()
{
	printf("[LuaScriptThread] Thread %s started\n", m_sName.c_str());

	// Flag
	m_bActive = true;

	// Check if callback is present
	m_self.get(lua->State());
	if (lua->IsNil())
	{
		lua->Pop(1);
		return;
	}
	lua->GetField("Run", -1);
	if (lua->IsNil())
	{
		lua->Pop(2);
		return;
	}
	lua->Pop(2);

	// Call
	try
	{
		call<void>("Run");
	}
	catch (ScriptThreadReset) {
		// Do nothing
	}
	catch (luabind::error& e) {
		printf("[LuaScriptThread] Thread %s:Run caused an error!\n", m_sName.c_str());

		if (lua->IsString(-1))
			lua->PrintErrorMessage(lua->GetString(-1), true, false);
		else
			lua->PrintErrorMessage(const_cast<char*>(e.what()), true, false);
	}
	catch (LuaException& e) {
		printf("[LuaScriptThread] Thread %s:Run caused an error!\n", m_sName.c_str());
		lua->PrintErrorMessage(const_cast<char*>(e.what()), true, true);
	}
	catch (std::exception& e) {
		printf("[LuaScriptThread] Thread %s:Run caused an error: %s\n", m_sName.c_str(), e.what());
	}
	catch (...) {
		printf("LuaScriptThread] Thread %s:Run caused an error: (unknown exception thrown)\n", m_sName.c_str());
	}

	// Handle Reset
	if (m_bResetting && m_bActive)
	{
		m_bResetting = false;
		printf("[LuaScriptThread] Thread %s reset\n", m_sName.c_str());
		Run();
		return;
	}

	// Exit Message
	m_bActive = false;
	printf("[LuaScriptThread] Thread %s quit\n", m_sName.c_str());
}

// =================================================================================
// Wait 
// =================================================================================
void LuaScriptThread::Wait(DWORD uiTime)
{
	if (m_bActive && m_bResetting)
		throw ScriptThreadReset();
	if (!m_bActive)
		throw LuaException("ScriptThread:Wait called on an invalid thread!");
	
	ScriptHook::ThreadWait(uiTime);
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