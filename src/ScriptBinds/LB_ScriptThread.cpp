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
}
LuaScriptThread::~LuaScriptThread()
{
	printf("LuaScriptThread::~\n");
}

// =================================================================================
// Run 
// =================================================================================
void LuaScriptThread::Run()
{
	printf("[LuaScriptThread] Thread %s started\n", m_sName.c_str());
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

	// Exit Message
	m_bActive = false;
	printf("[LuaScriptThread] Thread %s quit\n", m_sName.c_str());
}

// =================================================================================
// Wait 
// =================================================================================
void LuaScriptThread::Wait(DWORD uiTime)
{
	if (!m_bActive)
	{
		throw LuaException("ScriptThread:Wait called on an invalid thread!");
	}
	
	ScriptHook::ThreadWait(uiTime);
}

// =================================================================================
// Kill 
// =================================================================================
void LuaScriptThread::Kill()
{
	m_bActive = false;
}

// =================================================================================
// Bind 
// =================================================================================
void ScriptBinds::ScriptThread::Bind()
{
	// TODO: Add ability to register own threads
	luabind::module(lua->State())
	[
		luabind::class_<LuaScriptThread>("CScriptThread")
		.def(luabind::constructor<string>())
		.def("GetName", &LuaScriptThread::GetName)
		.def("IsActive", &LuaScriptThread::IsActive)
		.def("Wait", &LuaScriptThread::Wait)
		.def("internal_Kill", &LuaScriptThread::Kill)
	];
}