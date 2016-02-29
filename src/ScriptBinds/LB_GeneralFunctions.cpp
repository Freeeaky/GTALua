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
// print 
// =================================================================================
static int LB_print(lua_State *L) {
	int n = lua_gettop(L);  /* number of arguments */
	int i;
	lua_getglobal(L, "tostring");
	for (i = 1; i <= n; i++) {
		const char *s;
		size_t l;
		lua_pushvalue(L, -1);  /* function to be called */
		lua_pushvalue(L, i);   /* value to print */
		int r = lua_pcall(L, 1, 1, 0);
		if (r != 0)
		{
			lua_pop(L, 1);
			lua_getglobal(L, "type");
			lua_pushvalue(L, i);
			lua_pcall(L, 1, 1, 0);
			printf("[type: %s]", lua_tostring(L, -1));
			lua_pop(L, 1);
			continue;
		}
		s = lua_tolstring(L, -1, &l);  /* get result */
		if (s == NULL)
			return luaL_error(L, "'tostring' must return a string to 'print'");
		if (i>1) printf(" ");
		printf(s, l);
		lua_pop(L, 1);  /* pop result */
	}
	printf("\n");
	return 0;
}

// =================================================================================
// IsKeyCurrentlyDown 
// =================================================================================
bool LB_IsKeyCurrentlyDown(int vk)
{
	return (GetKeyState(vk) & 0x8000)!=0;
}

// =================================================================================
// IsKeyDown
// =================================================================================
bool LB_IsKeyDown(int vk)
{
	return (bool)(GetAsyncKeyState(vk) & 1);
}

// =================================================================================
// Script Engine
// =================================================================================
bool LB_IsScriptEngineInitialized()
{
	return GameMemory::ScriptEngineInitialized;
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
		luabind::def("IsKeyDown", LB_IsKeyDown),
		// TODO: Add game module
		luabind::def("IsScriptEngineInitialized", LB_IsScriptEngineInitialized)
	];

	// print (luabind doesnt support va)
	lua_register(lua->State(), "print", LB_print);

	// like include
	LuaFunctions::RegisterLuaFunctions();
}