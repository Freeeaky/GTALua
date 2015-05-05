// =================================================================================
// Includes 
// =================================================================================
#include <Windows.h>
#define ASI_ADDON_VERSION 3
typedef void(*ScriptHook_Callback)();

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
// Exports 
// =================================================================================
extern "C"
{
	__declspec(dllexport) void SetActualCallback(ScriptHook_Callback pCallback);
	__declspec(dllexport) void RegisterThread_Proxy();
}

// =================================================================================
// Actual Callback 
// =================================================================================
ScriptHook_Callback g_pThreadCallback = NULL;
void SetActualCallback(ScriptHook_Callback pCallback)
{
	g_pThreadCallback = pCallback;
}

// =================================================================================
// Script Thread 
// =================================================================================
void RegisterThread_Proxy()
{
	// Actual Callback
	if (g_pThreadCallback != NULL)
	{
		g_pThreadCallback();
		return;
	}

	// No Callback specified
	MessageBox(0, "GTALua: ASIAddon Fatal Error!\nScript Thread created but no actual callback set!", "GTALua Fatal Error!", 0);
}

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
		// Check ScriptHookV & GTALua
		if (!GetModuleHandle("ScriptHookV.dll") || !GetModuleHandle("GTALua.dll"))
			return TRUE;

		// Let GTALua.dll unload our addon
		UnloadAddon((HMODULE) hModule);
	}

	return TRUE;
}