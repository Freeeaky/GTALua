// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "Memory/Memory.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds/ScriptBinds.h"
#include "UTIL/UTIL.h"
#include "thirdparty/SimpleFileWatcher/include/FileWatcher.h"
#include "GameEvents/GameEvents.h"

// =================================================================================
// CTor/DTor 
// =================================================================================
GTALua::GTALua()
{
	// Active
	m_bActive = true;
}
GTALua::~GTALua()
{
	// Update-Thread
	m_bActive = false;

	// Lua
	if (lua != NULL)
		lua->Destroy();
	
	// Memory & Hooking
	Memory::CleanUp();

	// Console
	DestroyWindow(GetConsoleWindow());
}

// =================================================================================
// Init
// Called right after the CTor
// =================================================================================
void GTALua::Init()
{
	// Main Config
	LoadGTALuaIni();

	// Attach Console
#ifndef GTA_LUA_TEST_EXE
	if (m_sConfig.bConsole_Enabled)
	{
		UTIL::Attach_Console(m_sConfig.bConsole_AutomaticPosition, m_sConfig.iConsole_ManualX, m_sConfig.iConsole_ManualY);
		SetConsoleTitle("GTALua - Version 1.1.2");
	}
#endif

	// Prepare Memory
	Memory::Init();
	GameMemory::Init();

	// Configuration Files
	LoadNativesINI();
	LoadCallLayoutsINI();
}

// =================================================================================
// Init 
// This is called shortly before the game window is created
// At this point the exe is already unpacked, safe to do anything we want
// =================================================================================
void GTALua::ProperInit()
{
	printf("[GTALua] Initializing..\n");

	// Hooks
#ifndef GTA_LUA_TEST_EXE
	GameMemory::InstallHooks();
	
	// Game Events
	GameEvents::Install::Entity();
	GameEvents::Install::OnPedCreated();
	GameEvents::Install::OnVehicleCreated();
#endif

	// Initialize Lua
	lua = new LuaManager();
	lua->Init();

	/*// Initialize AutoRefresh
	LuaFunctions::Autorefresh::Init();
	LuaFunctions::Autorefresh::Update();*/

	// Script Binds
	try
	{
		// General
		ScriptBinds::GeneralFunctions::Bind();
		ScriptBinds::FileModule::Bind();

		// Script Engine
		ScriptBinds::ScriptThread::Bind();
		ScriptBinds::ScriptHookBind::Bind();
		ScriptBinds::NativesWrapper::Bind();
		ScriptBinds::Types::Bind();
		ScriptBinds::Memory::Bind();
	}
	catch (std::exception& e)
	{
		printf("[Lua] Failed to bind functions!\n");
		lua->PrintErrorMessage(const_cast<char*>(e.what()), true, true);
	}
	catch (...)
	{
		printf("[Lua] Failed to bind functions! (unknown exception)\n");
	}

	// Include main.lua
	if (!lua->IncludeFile("GTALua/internal/main.lua"))
	{
		printf("[Lua] Failed to include main.lua! GTALua will not work properly!\n");
		return;
	}
}

// =================================================================================
// Addons 
// =================================================================================
void GTALua::InitAddons()
{
	if (lua == NULL) return;

	// Queued Addons
	printf("\n");
	API::LoadQueuedAddons();

	// Run _main
	lua->GetGlobal("_main");
	if (!lua->ProtectedCall(0, 1))
	{
		lua->Pop(2);
		printf("[Lua] Failed to run _main!\n");
		return;
	}
	if (!lua->GetBool())
	{
		lua->Pop(2);
		printf("[GTALua] Failed to load addons!\n");
		return;
	}
	lua->Pop(2);

	// Success
	printf("===================================================================\n");
	printf("[GTALua] Initialized!\n");
	printf("===================================================================\n\n");
}

// =================================================================================
// Update 
// =================================================================================
void GTALua::Update()
{
	// AutoRefresh
	/*if (LuaFunctions::Autorefresh::IsInitialized())
		LuaFunctions::Autorefresh::Update();*/

	// Console Input
	ProcessConsoleInput();
}

// =================================================================================
// Update Loop 
// =================================================================================
void GTALua::UpdateLoop()
{
	while (m_bActive)
	{
		Update();
	}
}