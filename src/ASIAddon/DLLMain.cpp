// =================================================================================
// Includes 
// =================================================================================
#include <Windows.h>
#define ASI_ADDON_VERSION 1

// =================================================================================
// Imports 
// =================================================================================
extern "C"
{
	__declspec(dllimport) void LoadAddon(int version, HMODULE hModule);
	__declspec(dllimport) void UnloadAddon(HMODULE hModule);
}
#pragma comment(lib,"build/GTALua.lib")

// =================================================================================
// DLLMain 
// =================================================================================
BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	// Startup
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		// Let GTALua.dll load our addon
		LoadAddon(ASI_ADDON_VERSION, (HMODULE) hModule);
	}

	// Cleanup
	if (dwReason == DLL_PROCESS_DETACH)
	{
		// Let GTALua.dll unload our addon
		UnloadAddon((HMODULE) hModule);
	}

	return TRUE;
}