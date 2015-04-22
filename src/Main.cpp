// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "Memory/Memory.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds/ScriptBinds.h"

// =================================================================================
// Init 
// =================================================================================
GTALua::GTALua()
{
	// Attach Console
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout); 

	// Prepare Memory
	Memory::Init(); 
	GameMemory::Init();
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

	// Hooks & Patches
	GameMemory::InstallHooks();
	GameMemory::InstallPatches();

	// Initialize Lua
	lua = new LuaManager();
	lua->Init();

	// General
	ScriptBinds::GeneralFunctions::Bind();
	ScriptBinds::Console::Bind();
	ScriptBinds::BindBlockedFunctions();

	// Script Engine
	ScriptBinds::ScriptEngine::Bind();
	ScriptBinds::ScriptThread::Bind();

	// Include main.lua
	if (!lua->IncludeFile("GTALua/lua/main.lua"))
	{
		printf("[Lua] Failed to include main.lua! GTALua will not work properly!\n");
		return;
	}
}