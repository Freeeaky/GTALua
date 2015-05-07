// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "ScriptEngine.h"
#include "Memory/Memory.h"
#include "UTIL/UTIL.h"
#include "lua/Lua.h"
#include "ScriptBinds/ScriptBinds.h"
#include "thirdparty/ScriptHookV/ScriptHookV.h"

#include "thirdparty/ScriptHookV/inc/main.h"

// =================================================================================
// ScriptHook Member 
// =================================================================================
bool ScriptHook::CanRegisterThreads = true;

// =================================================================================
// Push Memory 
// =================================================================================
void ScriptHook::PushMemory(ScriptBinds::Memory::MemoryBlock* pMemBlock)
{
	if (pMemBlock == NULL || !pMemBlock->IsValid())
	{
		lua->PushString("ScriptHook::PushMemory failed! Invalid CMemoryBlock passed!");
		throw luabind::error(lua->State());
	}
	PushValue(pMemBlock->GetMemoryPointer()); 
}

int ScriptHook::GetGameTime()
{
#ifndef GTA_LUA_TEST_EXE
	NativeInit(0x9CD27B0045628463);
	return Call<int>();
#else
	SYSTEMTIME st;
	GetSystemTime(&st);
	return st.wMilliseconds;
#endif
}

// =================================================================================
// Wrapper
// I don't want the imported functions to be global
// =================================================================================
void ScriptHook::ScriptWait(DWORD dwTime)
{
#ifndef GTA_LUA_TEST_EXE
	scriptWait(dwTime);
#else
	Sleep(dwTime);
#endif
}
void ScriptHook::ScriptRegister(HMODULE hModule, ScriptHook_Callback ptr)
{
#ifndef GTA_LUA_TEST_EXE
	scriptRegister(hModule, ptr);
#endif
}
void ScriptHook::ScriptUnregister(ScriptHook_Callback ptr)
{
#ifndef GTA_LUA_TEST_EXE
	scriptUnregister(ptr);
#endif
}

void ScriptHook::NativeInit(UINT64 hash)
{
#ifndef GTA_LUA_TEST_EXE
	nativeInit(hash);
#endif
}
void ScriptHook::NativePush64(UINT64 val)
{
#ifndef GTA_LUA_TEST_EXE
	nativePush64(val);
#endif
}
PUINT64 ScriptHook::NativeCall()
{
#ifndef GTA_LUA_TEST_EXE
	return nativeCall();
#else
	UINT64 p = 0;
	return &p;
#endif
}