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

// =================================================================================
// Init 
// =================================================================================
GTALua::GTALua()
{
#ifndef GTA_LUA_TEST_EXE
	// Attach Console
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout); 
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
	// Debug
	printf("[GTALua] Initializing..\n");

	// Hooks
#ifndef GTA_LUA_TEST_EXE
	GameMemory::InstallHooks();
#endif

	// Initialize Lua
	lua = new LuaManager();
	lua->Init();

	// Script Binds
	try
	{
		// General
		ScriptBinds::GeneralFunctions::Bind();
		ScriptBinds::Console::Bind();
		ScriptBinds::FileModule::Bind();

		// Script Engine
		ScriptBinds::ScriptHookBind::Bind();
		ScriptBinds::NativesWrapper::Bind();
		ScriptBinds::Types::Bind();
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

	// Run _main
	lua->GetGlobal("_main");
	if (!lua->ProtectedCall(0, 1))
	{
		printf("[Lua] Failed to run _main! GTALua will not work properly!\n");
		return;
	}
	if (!lua->GetBool())
	{
		printf("[GTALua] Failed to initialize!\n");
		return;
	}

	// Success
	printf("[GTALua] Successfully initialized!\n\n");
}

// =================================================================================
// ScriptThread 
// =================================================================================
void GTALua::DoScriptThread()
{
	lua->GetEvent("OnScriptThread");
	lua->ProtectedCall(1);
}