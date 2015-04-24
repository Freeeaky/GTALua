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

	// Hooks & Patches
#ifndef GTA_LUA_TEST_EXE
	GameMemory::InstallHooks();
	GameMemory::InstallPatches();
#endif

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
	ScriptBinds::NativeInvocation::Bind();
	ScriptBinds::NativesWrapper::Bind();

	// Include main.lua
	if (!lua->IncludeFile("GTALua/lua/main.lua"))
	{
		printf("[Lua] Failed to include main.lua! GTALua will not work properly!\n");
		return;
	}
}