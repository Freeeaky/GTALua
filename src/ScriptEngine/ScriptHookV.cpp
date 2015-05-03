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
void ScriptHook::ScriptRegister(ScriptHook_Callback ptr)
{
	scriptRegister(GetModuleHandle("GTALua.asi"), ptr);
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