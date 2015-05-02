// =================================================================================
// Includes
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "Memory/Memory.h"
#include "ScriptEngine/ScriptEngine.h"
#include "lua/Lua.h"

// =================================================================================
// Test Thread
// =================================================================================
class TestThread : public ScriptThreadWrapper
{
public:
	void OnRun()
	{
		

		if (GetAsyncKeyState(VK_F9) & 1)
		{
			printf("OK!\n");
			printf("at +0x110: %p\n", *(DWORD64*) (this + 0x110));

			InvokeNative get_player_ped(0x687D51F360787909);
			get_player_ped.PushArgument<int>(-1);
			get_player_ped.Call();
			int player_ped_id = get_player_ped.GetResult<int>(0);
			printf("player ped : %i\n", player_ped_id);

			InvokeNative get_entity_coords(0xBF1B13057E5119A4);
			get_entity_coords.PushArgument<int>(player_ped_id);
			get_entity_coords.PushArgument<bool>(true);
			get_entity_coords.Call();
			rage::CVector player_pos = get_entity_coords.GetResult<rage::CVector>();
			printf("pos: %f %f %f\n", player_pos.x, player_pos.y, player_pos.z);

			InvokeNative has_model_loaded(0xD291857D0C9C7FEC);
			has_model_loaded.PushArgument<int>(0xC703DB5F);
			has_model_loaded.Call();
			bool has_loaded = has_model_loaded.GetResult<bool>();
			printf("has loaded: %i\n", (int)has_loaded);

			if (has_loaded)
			{
				InvokeNative create_vehicle(0x546974B676313326);
				create_vehicle.PushArgument<int>(0xC703DB5F);
				create_vehicle.PushArgument<float>(player_pos.x);
				create_vehicle.PushArgument<float>(player_pos.y);
				create_vehicle.PushArgument<float>(player_pos.z);
				create_vehicle.PushArgument<float>(0.0f);
				create_vehicle.PushArgument<bool>(true);
				create_vehicle.PushArgument<bool>(true);
				create_vehicle.Call();
				int vehicle_id = create_vehicle.GetResult<int>();
				printf("vehicle id: %i\n", vehicle_id);
			}
			else {
				printf("request!\n");

				InvokeNative request_model(0xCBE6AC5010E5CE5C);
				request_model.PushArgument<int>(0xC703DB5F);
				request_model.Call();
			}
		}
	}
};

// =================================================================================
// Test
// =================================================================================
void TestingStuff()
{
	printf("Testing Stuff\n");

	// Size Checks
	printf("size ScriptThreadContext: %i (should be 168)\n", sizeof(ScriptThreadContext));
	printf("size ScriptThread: %i (should be 208)\n", sizeof(ScriptThread));
	printf("size ScriptThreadWrapper: %i (should be 344)\n", sizeof(ScriptThreadWrapper));

	// Addresses
	if (!ScriptEngine::CollectAddresses())
	{
		printf("Failed to collect addresses!\n");
		return;
	}

	// Register
	TestThread* pThread = new TestThread();
	bool r = ScriptEngine::CreateScriptThread((ScriptThread*) pThread);
	if (!r)
		printf("Fail!\n");

	/*
	DWORD64* VTable = *(DWORD64**)ScriptEngine::HandlerManager;
	printf("VTable: %p\n", VTable - GameMemory::Base);
	for (int i = 0; i < 15; i++)
	{
		printf("\t%i: %p\n", i, VTable[i] - GameMemory::Base);
	}*/
}

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

	// Init our stuff
	if (!GameMemory::ScriptEngineInitialized)
	{
		// Mark as initialized
		GameMemory::ScriptEngineInitialized = true;
		printf("[GTA ScriptEngine] Initialized\n");

		// Lua Callback
		//lua->GetEvent("OnScriptEngineInitialized");
		//lua->ProtectedCall(1);

		// Test
		TestingStuff();
	}
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