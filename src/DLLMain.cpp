// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "Memory/Memory.h"
#include "lua/Lua.h"

// =================================================================================
// Global 
// =================================================================================
GTALua* g_pGTALua = NULL;

// =================================================================================
// Init 
// =================================================================================
void Init()
{
	// Init
	g_pGTALua = new GTALua();

	// Update
	//g_pGTALua->UpdateLoop();
}

// =================================================================================
// DLLMain 
// =================================================================================
BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	// Startup
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Init, 0, 0, 0);
		Init();
	}

	// Cleanup
	if (dwReason == DLL_PROCESS_DETACH)
	{
		if (g_pGTALua != NULL)
		{
			delete g_pGTALua;
			g_pGTALua = NULL;
		}
	}

	// Success
	return TRUE;
}

// =================================================================================
// Test-Purpose
// This allows building as exe to test lua stuff
// Starting the time every 2 minutes is annoying and a waste of time
// =================================================================================
#ifdef GTA_LUA_TEST_EXE
int main()
{
	// "Thread"
	Init();

	// Proper Init
	g_pGTALua->ProperInit();

	// Mark as initialized
	GameMemory::ScriptEngineInitialized = true;
	printf("[GTA ScriptEngine] Initialized\n");

	// Lua Callback
	lua->GetEvent("OnScriptEngineInitialized");
	lua->ProtectedCall(1);

	// Done
	return 0;
}
#endif