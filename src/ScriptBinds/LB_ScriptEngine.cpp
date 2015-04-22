// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "ScriptBinds.h"
#include "ScriptEngine/ScriptEngine.h"
#include "lua/Lua.h"

void RegisterScriptThread(luabind::object thread)
{

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