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
		MessageBox(0, 0, 0, 0);
		lua->PushString("ScriptHook::PushMemory failed! Invalid CMemoryBlock passed!");
		throw luabind::error(lua->State());
	}
	PushValue(pMemBlock->GetMemoryPointer()); 
}

// =================================================================================
// Wrapper
// I don't want the imported functions to be global
// =================================================================================
void ScriptHook::ScriptWait(DWORD dwTime)
{
	scriptWait(dwTime);
}
void ScriptHook::ScriptRegister(HMODULE hModule, ScriptHook_Callback ptr)
{
	scriptRegister(hModule, ptr);
}
void ScriptHook::ScriptUnregister(ScriptHook_Callback ptr)
{
	scriptUnregister(ptr);
}

void ScriptHook::NativeInit(UINT64 hash)
{
	nativeInit(hash);
}
void ScriptHook::NativePush64(UINT64 val)
{
	nativePush64(val);
}
PUINT64 ScriptHook::NativeCall()
{
	return nativeCall();
}