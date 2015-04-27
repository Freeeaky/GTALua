// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "ScriptEngine.h"
#include "Memory/Memory.h"
#include "UTIL/UTIL.h"
#include "thirdparty/ScriptHookV/ScriptHookV.h"

// =================================================================================
// ScriptHook Member 
// =================================================================================
ScriptHook::scriptRegister_t ScriptHook::RegisterScript = NULL;
ScriptHook::scriptWait_t ScriptHook::ThreadWait = NULL;
ScriptHook::nativeInit_t ScriptHook::InitNative = NULL;
ScriptHook::nativePush64_t ScriptHook::NativePush64 = NULL;
ScriptHook::nativeCall_t ScriptHook::CallNative = NULL;

// =================================================================================
// Category By Name 
// =================================================================================
Natives::eNativeCategory Natives::FindCategoryByName(char* sName)
{
	// find category
	eNativeCategory eCategory = NATIVE_UNKNOWN;
	for (int i = 0; i < _NATIVE_ENUM_SIZE; i++)
	{
		if (strcmp(sName, CategoryNames[i]) == 0)
		{
			return (eNativeCategory)i;
		}
	}

	// unknown
	return NATIVE_UNKNOWN;
}