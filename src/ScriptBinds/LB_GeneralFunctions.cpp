// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds.h"

// =================================================================================
// type 
// =================================================================================
string LB_type(luabind::object obj)
{
	// check table/userdata
	if (lua->IsTable(1) || lua_isuserdata(lua->State(), 1))
	{
		// call __type
		const char* sType = NULL;
		try
		{
			sType = luabind::call_member<const char*>(obj, "__type");
		}
		catch (...) {
			sType = NULL;
		};

		// check & return
		if (sType != NULL)
		{
			return string(sType);
		}
	}

	// call original
	return lua_typename(lua->State(), lua_type(lua->State(), 1));
}

// =================================================================================
// Binds
// =================================================================================
void ScriptBinds::GeneralFunctions::Bind()
{
	luabind::module(lua->State())
	[
		luabind::def("type", LB_type)
	];

	// like include
	LuaFunctions::RegisterLuaFunctions();
}