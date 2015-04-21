// =================================================================================
// Includes
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "Memory/Memory.h"

// =================================================================================
// BinkOpen
// Skips the intro movie so you can get ingame more quickly
// =================================================================================
typedef int(*BinkOpen_t)(DWORD64 a, DWORD64 b);
BinkOpen_t pBinkOpen = NULL;
bool bIsIntroMovie = true;

int BinkOpen_Hook(DWORD64 a, DWORD64 b)
{
	// Skip if first-time-call
	if (bIsIntroMovie)
	{
		bIsIntroMovie = false;
		return 0;
	}

	// Original
	return pBinkOpen(a, b);
}

// =================================================================================
// Hooks
// =================================================================================
void GameMemory::InstallHooks()
{
	// BinkOpen (intro movie)
	Memory::HookLibraryFunction("bink2w64.dll", "BinkOpen", &BinkOpen_Hook, (void**)&pBinkOpen);
}

// =================================================================================
// ShowWindow
// =================================================================================
typedef bool(__stdcall* ShowWindow_t)(HWND hWnd, int nCmdShow);
ShowWindow_t pShowWindow = NULL;

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
void GameMemory::InstallInitHook()
{
	// ShowWindow
	Memory::HookLibraryFunction("user32.dll", "ShowWindow", &ShowWindow_Hook, (void**)&pShowWindow);
}