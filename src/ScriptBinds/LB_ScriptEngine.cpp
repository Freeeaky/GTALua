// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds.h"
#include "Memory/Memory.h"

// =================================================================================
// Register Thread 
// =================================================================================
bool RegisterScriptThread(ScriptBinds::ScriptThread::LuaScriptThread* pThread)
{
	// Script Engine
	if (!GameMemory::ScriptEngineInitialized)
	{
		printf("[Lua] You cannot register a script thread yet! Wait until the script engine is initialized!\n");
		return false;
	}
	
	// Check Thread
	if (pThread == NULL)
	{
		printf("[Lua] You passed an invalid script thread to RegisterScriptThread!\n");
		return false;
	}
	
	// Create Thread
	if (!ScriptEngine::CreateScriptThread(pThread))
	{
		printf("[Lua] Failed to register script thread!\n");
		return false;
	}

	// Success
	return true;
}

// =================================================================================
// Bind 
// =================================================================================
void ScriptBinds::ScriptEngine::Bind()
{
	luabind::module(lua->State(), "engine")
	[
		luabind::def("RegisterScriptThread", RegisterScriptThread)
	];
}