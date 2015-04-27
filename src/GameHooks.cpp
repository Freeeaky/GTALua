// =================================================================================
// Includes
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "Memory/Memory.h"
#include "ScriptEngine/ScriptEngine.h"
#include "lua/Lua.h"
#include "thirdparty/ScriptHookV/ScriptHookV.h"

// =================================================================================
// Local Definitions
// =================================================================================
// BinkOpen (intro)
typedef int(*BinkOpen_t)(DWORD64 a, DWORD64 b);
BinkOpen_t pBinkOpen = NULL;
bool bIsIntroMovie = true;

// Script Engine
typedef void(*ScriptEngine__Init_t)(DWORD64 ptr);
ScriptEngine__Init_t pScriptEngine__Init = NULL;

// ShowWindow
typedef bool(__stdcall* ShowWindow_t)(HWND hWnd, int nCmdShow);
ShowWindow_t pShowWindow = NULL;

// =================================================================================
// BinkOpen
// Skips the intro movie so you can get ingame more quickly
// =================================================================================
int BinkOpen_Hook(DWORD64 a, DWORD64 b)
{
	// Skip if first-time-call
	if (bIsIntroMovie)
	{
		printf("[Intro Movie] Skipped\n");

		bIsIntroMovie = false;
		return 0;
	}

	// Original
	return pBinkOpen(a, b);
}

// =================================================================================
// ScriptEngine Init
// =================================================================================
void ScriptEngine__Init(DWORD64 ptr)
{
	// Original
	pScriptEngine__Init(ptr);

	// Mark as initialized
	GameMemory::ScriptEngineInitialized = true;
	printf("[GTA ScriptEngine] Initialized\n");
	
	// Init ScriptHook
	ScriptHook::Initialize();

	// Lua Callback
	lua->GetEvent("OnScriptEngineInitialized");
	lua->ProtectedCall(1);
}

// =================================================================================
// Hooks
// =================================================================================
void GameMemory::InstallHooks()
{
	// BinkOpen (intro movie)
	Memory::HookLibraryFunction("bink2w64.dll", "BinkOpen", &BinkOpen_Hook, (void**)&pBinkOpen);

	// ScriptEngine::Init
	Memory::HookFunction(GameMemory::Find((PBYTE)"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x33\xFF\x48\x8B\xD9\x66\x89\x39\x48\x89\x79\x04", "xxxx?xxxxxxxxxxxxxxxxx"), &ScriptEngine__Init, (void**)&pScriptEngine__Init);
}

// =================================================================================
// ShowWindow
// =================================================================================
bool ShowWindow_Hook(HWND hWnd, int nCmdShow)
{
	if (hWnd == GetConsoleWindow() && nCmdShow == 0)
	{
		// Init
		// This gets called shortly before the game window is created
		// At this point, the game exe has been unpacked and patching is safe
		g_pGTALua->ProperInit();

		// Prevent hiding the console window
		return true;
	}

	// Original
	return pShowWindow(hWnd, nCmdShow);
}

// =================================================================================
// Init Hook
// =================================================================================
void GameMemory::InstallInitHooks()
{
	// ShowWindow
	Memory::HookLibraryFunction("user32.dll", "ShowWindow", &ShowWindow_Hook, (void**)&pShowWindow);
}