// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds.h"
#include "Memory/Memory.h"
#include "thirdparty/ScriptHookV/ScriptHookV.h"

// Imports
typedef void(*RegisterThread_Proxy_t)();

// =================================================================================
// Sleep 
// =================================================================================
void LB_ThreadSleep(UINT s)
{
#ifndef GTA_LUA_TEST_EXE
	ScriptHook::ScriptWait(s);
#endif
}

// =================================================================================
// Init Native
// =================================================================================
void LB_InitNative(Natives::NativeReg* pNative)
{
	ScriptHook::NativeInit(pNative->hHash);
}

// =================================================================================
// Start Lua Thread
// Called from ScriptHookV, but redirected through ASI Addon
// =================================================================================
vector<ScriptBinds::ScriptThread::LuaScriptThread*> vScriptThreadQueue;
void Lua_StartThread()
{
	ScriptHook::CanRegisterThreads = false;

	// Update Queue
	if (vScriptThreadQueue.size() == 0) return;
	ScriptBinds::ScriptThread::LuaScriptThread* pScriptThread = vScriptThreadQueue.at(0);
	vScriptThreadQueue.erase(vScriptThreadQueue.begin());

	// Start Thread
	try
	{
		pScriptThread->Start();
	}
	catch (...)
	{
		printf("[GTALua] Script Thread caused an unexpected exception!\n");
	}
}

// =================================================================================
// Register Thread 
// Returns:
//   -1: Fail, already registered
//    1: Add to main thread
//    2: Addon has ASI
// =================================================================================
int LB_RegisterThread(ScriptBinds::ScriptThread::LuaScriptThread* pThread)
{
#ifdef GTA_LUA_TEST_EXE
	vScriptThreadQueue.push_back(pThread);
	if (!pThread->m_bIsMainThread)
		pThread->m_bRunsOnMainThread = true;
	return 1;
#endif

	// Only register once
	// (Autorefresh)
	for (vector<ScriptBinds::ScriptThread::LuaScriptThread*>::iterator it = vScriptThreadQueue.begin(); it != vScriptThreadQueue.end(); ++it)
		if (*it == pThread) return -1;

	// Main Thread
	if (pThread->m_bIsMainThread)
	{
		vScriptThreadQueue.push_back(pThread);
		ScriptHook::ScriptRegister(GetModuleHandle("GTALua.asi"), Lua_StartThread);
		return 2;
	}

	// Get Module
	char buf[256];
	sprintf(buf, "%s.asi", pThread->GetName().c_str());
	HMODULE hASIAddon = GetModuleHandle(buf);

	// Check
	if (hASIAddon == NULL && !pThread->m_bIsMainThread)
	{
		pThread->m_bRunsOnMainThread = true;
		return 1;
	}

	// RegisterThread Proxy
	RegisterThread_Proxy_t pRegisterThreadProxy = (RegisterThread_Proxy_t) GetProcAddress(hASIAddon, "RegisterThread_Proxy");
	if (hASIAddon != NULL && pRegisterThreadProxy == NULL)
	{
		char error_buf[512];
		sprintf(error_buf, "[ASIAddon] %s: Failed to import RegisterThread_Proxy!\n", buf);
		lua->PushString(error_buf);
		throw luabind::error(lua->State());
	}

	// Register
	vScriptThreadQueue.push_back(pThread);
	ScriptHook::ScriptRegister(hASIAddon, pRegisterThreadProxy);
	return 2;
}

// =================================================================================
// State Check
// =================================================================================
bool LB_CanRegisterThreads()
{
	return ScriptHook::CanRegisterThreads;
}

// =================================================================================
// Bind 
// =================================================================================
void ScriptBinds::ScriptHookBind::Bind()
{
	luabind::module(lua->State(), "scripthookv")
	[
		luabind::def("CanRegisterThreads", LB_CanRegisterThreads),

		luabind::def("RegisterThread", LB_RegisterThread),
		luabind::def("ThreadSleep", LB_ThreadSleep),
		luabind::def("InitNative", LB_InitNative),
		luabind::def("NativePushInt", ScriptHook::PushValue<__int32>),
		luabind::def("NativePushFloat", ScriptHook::PushValue<float>),
		luabind::def("NativePushVector", ScriptHook::PushValue<rage::CVector>),
		luabind::def("NativePushBool", ScriptHook::PushValue<bool>),
		luabind::def("NativePushString", ScriptHook::PushValue<const char*>),
		luabind::def("NativePushMemoryBlock", ScriptHook::PushMemory),
		luabind::def("NativeCall_GetInt", ScriptHook::Call<__int32>),
		luabind::def("NativeCall_GetFloat", ScriptHook::Call<float>),
		luabind::def("NativeCall_GetVector", ScriptHook::Call<rage::CVector>),
		luabind::def("NativeCall_GetBool", ScriptHook::Call<bool>),
		luabind::def("NativeCall_GetString", ScriptHook::Call<const char*>),
		luabind::def("NativeCall_Void", ScriptHook::CallVoid),

		luabind::def("GetGameTime", ScriptHook::GetGameTime)
	];
}