// =================================================================================
// Includes 
/*
 * DEPRECATED!
 * This will be removed in the next release!
 *
 * This feature is no longer neccessary. Currently we use just one thread that
 * manages all addons at the same time. This works without issues, multiple threads
 * are not neccessary.
 *
 * In the future, I might use ScriptHookV's function to add another thread.
 */
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "Memory/Memory.h"
#include "lua/Lua.h"
#include "thirdparty/ScriptHookV/ScriptHookV.h"
#include "ScriptBinds/ScriptBinds.h"

// =================================================================================
// Exports 
// =================================================================================
//#define ASI_ADDON_VERSION 4

// Noone needs name mangling
extern "C"
{
	__declspec(dllexport) void LoadAddon(int version, HMODULE hModule);
	__declspec(dllexport) void UnloadAddon(HMODULE hModule);
}

// =================================================================================
// Load Addon 
// =================================================================================
__declspec(dllexport) void LoadAddon(int version, HMODULE hModule)
{
	// Get Module File Name
	char* sPath = Memory::GetModulePath(hModule);
	char* sFileName = new char[64];
	_splitpath(sPath, NULL, NULL, sFileName, NULL);
	free(sPath);

	// Deprecated
	static bool warning = false;

	if (!warning)
	{
		printf("[ASIAddon] Deprecated! Please do not use ASI Addons anymore!\n;");
		printf("[ASIAddon] This feature is not working anymore and will be completely removed in the next version.\n");
		warning = true;
	}
	printf("[ASIAddon] Deprecated Feature: Please delete %s !\n", sPath);
}

// =================================================================================
// Unload Addon 
// =================================================================================
__declspec(dllexport) void UnloadAddon(HMODULE hModule)
{
	// Deprecated
}