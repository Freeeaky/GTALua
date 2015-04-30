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

// =================================================================================
// Sleep 
// =================================================================================
void LB_ThreadSleep(UINT s)
{
#ifndef GTA_LUA_TEST_EXE
	ScriptHook::ThreadWait(s);
#endif
}

// =================================================================================
// Init Native
// =================================================================================
void LB_InitNative(Natives::NativeReg* pNative)
{
	ScriptHook::InitNative(pNative->hHash);
}

// =================================================================================
// Start Lua Thread
// Called from ScriptHookV
// =================================================================================
vector<ScriptBinds::ScriptThread::LuaScriptThread*> vScriptThreadQueue;
void Lua_StartThread()
{
	ScriptHook::CanRegisterThreads = false;

	// Update Queue
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
// =================================================================================
void LB_RegisterThread(ScriptBinds::ScriptThread::LuaScriptThread* pThread)
{
	// Only register once
	// (Autorefresh)
	for (vector<ScriptBinds::ScriptThread::LuaScriptThread*>::iterator it = vScriptThreadQueue.begin(); it != vScriptThreadQueue.end(); ++it)
		if (*it == pThread) return;

	// Register
	vScriptThreadQueue.push_back(pThread);
	ScriptHook::RegisterScript(GetModuleHandle("GTALua.dll"), Lua_StartThread);
}

// =================================================================================
// State Check
// =================================================================================
bool LB_IsInitialized()
{
	return ScriptHook::IsInitialized;
}
bool LB_CanRegisterThreads()
{
	return ScriptHook::CanRegisterThreads;
}

// =================================================================================
// Bind 
// =================================================================================
void ScriptBinds::ScriptHookBind::Bind()
{
	// TODO: Add ability to register own threads
	luabind::module(lua->State(), "scripthookv")
	[
		luabind::def("IsInitialized", LB_IsInitialized),
		luabind::def("CanRegisterThreads", LB_CanRegisterThreads),

		luabind::def("internal_RegisterThread", LB_RegisterThread),
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
		luabind::def("NativeCall_Void", ScriptHook::CallVoid)
	];
}