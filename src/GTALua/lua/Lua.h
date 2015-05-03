// ====================================================================================================
// Lua Includes
// ====================================================================================================
extern "C"
{
	#include "lua/lua.h"
	#include "lua/lualib.h"
	#include "lua/lauxlib.h"
}
#include "luabind/luabind.hpp"

#pragma comment(lib,"src/GTALua/lua/lib/lua.lib")
#pragma comment(lib,"src/GTALua/lua/lib/luabind.lib")

#define lua_nil luabind::globals(lua->State())["nil"]

// ====================================================================================================
// Lua Manager
// ====================================================================================================
#include "luamanager/LuaManager.h"
#include "GeneralFunctions.h"