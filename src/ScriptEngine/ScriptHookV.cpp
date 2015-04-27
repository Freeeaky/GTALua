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
bool ScriptHook::IsInitialized = false;

// =================================================================================
// Init ScriptHookV 
// =================================================================================
bool ScriptHook::Initialize()
{
	// Load ScriptHook
	HMODULE hModule = GetModuleHandle("ScriptHookV.dll");
	if (!hModule)
		hModule = LoadLibrary("ScriptHookV.dll");

	// ScriptHook Check
	if (!hModule)
	{
		// ScriptHook is not installed
		printf("[GTALua] ScriptHookV is not installed! GTALua will NOT work without it!\n");
		return false;
	}

	// ScriptHook
	RegisterScript = (ScriptHook::scriptRegister_t) Memory::Find((DWORD64)hModule, Memory::GetModuleSize(hModule), (PBYTE)"\x48\x8B\xC4\x57", "xxxx");
	ThreadWait = (ScriptHook::scriptWait_t) Memory::Find((DWORD64)hModule, Memory::GetModuleSize(hModule), (PBYTE)"\x40\x57\x48\x83\xEC\x20\x65\x4C\x8B\x0C\x25\x00\x00\x00\x00", "xxxxxxxxxxx????");
	CallNative = (ScriptHook::nativeCall_t) Memory::Find((DWORD64)hModule, Memory::GetModuleSize(hModule), (PBYTE)"\x48\x83\xEC\x28\x48\x8D\x0D\x00\x00\x00\x00\xFF\x15\x00\x00\x00\x00\x48\x63\x05\x00\x00\x00\x00", "xxxxxxx????xx????xxx????");
	InitNative = (ScriptHook::nativeInit_t) Memory::Find((DWORD64)hModule, Memory::GetModuleSize(hModule), (PBYTE)"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x48\x8B\xD9\x48\x8D\x3D\x00\x00\x00\x00\x33\xD2", "xxxx?xxxxxxxxxxx????xx");
	NativePush64 = (ScriptHook::nativeInit_t) Memory::Find((DWORD64)hModule, Memory::GetModuleSize(hModule), (PBYTE)"\x48\x8B\x05\x00\x00\x00\x00\x48\x8B\x15\x00\x00\x00\x00", "xxx????xxx????");

	// Checkup
	if (!ScriptHook::RegisterScript || !ScriptHook::ThreadWait || !ScriptHook::CallNative || !ScriptHook::InitNative || !ScriptHook::NativePush64)
	{
		printf("[ScriptHook] GTALua failed to find all ScriptHook functions! Make sure you have the most recent version installed!\n");
		return false;
	}

	// Mark as initialized
	IsInitialized = true;
	return true;
}