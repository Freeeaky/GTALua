// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds.h"

// =================================================================================
// console.Log 
// =================================================================================
int console_Log(lua_State* L)
{
	printf("[Lua] ");

	int iArgumentCount = lua->Top();
	for (int i = 1; i <= iArgumentCount; i++)
	{
		luabind::object obj(luabind::from_stack(lua->State(), i));

		switch (luabind::type(obj))
		{
		case LUA_TSTRING:
			printf("%s", luabind::object_cast<const char*>(obj));
			break;
		case LUA_TNUMBER:
			printf("%i", luabind::object_cast<int>(obj));
			break;
		case LUA_TNIL:
			printf("nil");
			break;
		default:
			{
				// Tables/userdata: read __tostring
				if (lua->IsTable(i) || lua_isuserdata(L, i))
				{
					const char* sObject = NULL;
					try
					{
						sObject = luabind::call_member<const char*>(obj, "__tostring");
					}
					catch (...) {};

					if (sObject != NULL)
					{
						printf("%s", sObject);
						continue;
					}
				}

				// print type
				printf("[Unknown type %s]", luabind::call_function<const char*>(lua->State(), "type", luabind::type(obj)));
			}
		}
	}

	printf("\n");

	return 0;
}

// =================================================================================
// Bind 
// =================================================================================
void ScriptBinds::Console::Bind()
{
	/*
	luabind::module(lua->State(), "console")
		[
			luabind::def("test", NULL)
		];*/

	// luabind doesn't support variable arguments
	static const luaL_reg console_table[] =
	{
		{ "Log", console_Log },
		{ NULL, NULL }
	};
	luaL_register(lua->State(), "console", console_table);

	// redirect print to console.Log
	// again, va not supported
	lua_register(lua->State(), "print", console_Log);
}