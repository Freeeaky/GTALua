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

// =================================================================================
// ScriptHook Member 
// =================================================================================
bool ScriptHook::CanRegisterThreads = false;

// =================================================================================
// Push Memory 
// =================================================================================
void ScriptHook::PushMemory(ScriptBinds::Memory::MemoryBlock* pMemBlock)
{
	PushValue(pMemBlock->GetMemoryPointer());
}