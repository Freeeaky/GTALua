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
}

// =================================================================================
// Debug Thread
// TODO: Remove
// =================================================================================
void TempThread()
{
	while (lua == NULL)
		Sleep(50);

	while (g_pGTALua != NULL && lua != NULL)
	{
		char buf[256];
		sprintf(buf, "Stack Size: %i", lua->Top());
		SetConsoleTitle(buf);

		Sleep(500);
	}
}

// =================================================================================
// Init (Thread)
// =================================================================================
void ThreadInit()
{
	// Wait for GTALua
	while (g_pGTALua == NULL)
		Sleep(200);

	// Temporary debug thread
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)TempThread, 0, 0, 0);

	// Update
	g_pGTALua->UpdateLoop();
}

// =================================================================================
// DLLMain 
// =================================================================================
BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	// Startup
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		Init();
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE) ThreadInit, 0, 0, 0);
	}

	// Cleanup
	if (dwReason == DLL_PROCESS_DETACH && g_pGTALua != NULL)
	{
		delete g_pGTALua;
		g_pGTALua = NULL;
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
void Lua_StartThread();
void _main()
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
	lua->Pop(2);

	// Load
	lua->GetGlobal("addon");
	lua->GetField("Load");
	lua->PushString("police");
	lua->ProtectedCall(1);
	lua->Pop(2);

	// Thread
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Lua_StartThread, 0, 0, 0);
	ThreadInit();
}
int main()
{
	// Down-most
	try
	{
		_main();
	}
	catch (luabind::error& e) {
		printf("Error : %s\n", lua->GetString());
	}
	catch (...) {
		printf("Unhandled Exception!\n");
	}

	// Done
	return 0;
}
#endif