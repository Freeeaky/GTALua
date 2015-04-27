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
	// check for table/userdata
	int ttype = luabind::type(obj);
	if (ttype == LUA_TTABLE || ttype == LUA_TUSERDATA)
	{
		// call member __type
		const char* sType = NULL;
		try
		{
			sType = luabind::call_member<const char*>(obj, "__type");
		}
		catch (luabind::error e)
		{
			lua->Pop(1);
			sType = NULL;
		}
		catch (...) {
			sType = NULL;
		};

		// check & return
		if (sType != NULL)
			return string(sType);
	}

	// call typename
	const char* t = lua_typename(lua->State(), ttype);
	return t;
}

// =================================================================================
// IsKeyCurrentlyDown 
// =================================================================================
bool LB_IsKeyCurrentlyDown(int vk)
{
	return (bool)(GetKeyState(vk) & 0x8000);
}

// =================================================================================
// IsKeyDown
// =================================================================================
bool LB_IsKeyDown(int vk)
{
	return (bool)(GetAsyncKeyState(vk) & 1);
}

// =================================================================================
// Binds
// =================================================================================
void ScriptBinds::GeneralFunctions::Bind()
{
	luabind::module(lua->State())
	[
		luabind::def("type", LB_type),
		// TODO: Change this
		luabind::def("IsKeyCurrentlyDown", LB_IsKeyCurrentlyDown),
		luabind::def("IsKeyDown", LB_IsKeyDown)
	];

	// like include
	LuaFunctions::RegisterLuaFunctions();
}