// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "Memory/Memory.h"
#include "lua/Lua.h"
#include "thirdparty/ScriptHookV/ScriptHookV.h"
#include "ScriptBinds/ScriptBinds.h"

// =================================================================================
// Exports 
// =================================================================================
#define ASI_ADDON_VERSION 4

// Noone needs name mangling
extern "C"
{
	__declspec(dllexport) void LoadAddon(int version, HMODULE hModule);
	__declspec(dllexport) void UnloadAddon(HMODULE hModule);
}

// Imports
typedef void(*SetActualCallback_t)(ScriptHook_Callback pCallback);

// =================================================================================
// Load Queued Addons 
// =================================================================================
void API::LoadQueuedAddons()
{
	for (vector<char*>::iterator it = vLoadQueue.begin(); it != vLoadQueue.end(); ++it)
	{
		char* sName = *it;
		if (sName != NULL)
		{
			// Load
			lua->GetGlobal("addon");
			lua->GetField("Load");
			lua->PushString(sName);
			lua->ProtectedCall(1);
			lua->Pop(2);

			// Cleanup
			free(sName);
		}
	}

	// erase vector
	vLoadQueue.erase(vLoadQueue.begin(), vLoadQueue.end());
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

	// Version
	if (version != ASI_ADDON_VERSION)
	{
		printf("[ASIAddon] Module %s unsupported! Version: %i, Required Version: %i\n", sFileName, version, ASI_ADDON_VERSION);
		return;
	}

	// Callback
	SetActualCallback_t pSetCallback = (SetActualCallback_t)GetProcAddress(hModule, "SetActualCallback");
	if (!pSetCallback)
	{
		printf("[ASIAddon] %s: Failed to import SetActualCallback!\n", sFileName);
		return;
	}
	pSetCallback(&Lua_StartThread);

	// Load
	API::vLoadQueue.push_back(sFileName);
	if (lua != NULL)
		API::LoadQueuedAddons();
}

// =================================================================================
// Unload Addon 
// =================================================================================
__declspec(dllexport) void UnloadAddon(HMODULE hModule)
{
	// Get Module File Name
	char* sPath = Memory::GetModulePath(hModule);
	char* sFileName = new char[64];
	_splitpath(sPath, NULL, NULL, sFileName, NULL);
	free(sPath);

	// Already shut down
	if (lua == NULL || g_pGTALua == NULL)
		return;

	// Debug
	printf("[GTALua] Unloading %s\n", sFileName);

	// Unload
	lua->GetGlobal("addon");
	lua->GetField("Unload");
	lua->PushString(sPath);
	lua->ProtectedCall(1);
	lua->Pop(3);

	// Cleanup
	free(sPath);
}