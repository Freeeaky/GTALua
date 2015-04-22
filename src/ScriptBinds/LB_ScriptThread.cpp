// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "ScriptBinds.h"
#include "ScriptEngine/ScriptEngine.h"
#include "lua/Lua.h"

namespace ScriptBinds
{
	namespace ScriptThread
	{
		class LuaScriptThread
		{
		public:
			LuaScriptThread();
			~LuaScriptThread();

			// Lua
			char* __tostring() {
				return "ScriptThread";
			}
		};
	}
}

namespace ScriptBinds
{
	namespace ScriptThread
	{
		LuaScriptThread::LuaScriptThread()
		{

		}

		LuaScriptThread::~LuaScriptThread()
		{

		}
	}
};

// =================================================================================
// Bind 
// =================================================================================
void ScriptBinds::ScriptThread::Bind()
{
	luabind::module(lua->State())
	[
		luabind::class_<LuaScriptThread>("ScriptThread")
			.def(luabind::constructor<>())
			.def("__tostring", &LuaScriptThread::__tostring)
	];
}