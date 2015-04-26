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
// Script Thread 
// =================================================================================
namespace ScriptBinds
{
	namespace ScriptThread
	{
		// Lua Callback
		void LuaScriptThread::CallLuaCallback(char* sName)
		{
			// Check if callback is present
			m_self.get(lua->State());
			if (lua->IsNil())
			{
				lua->Pop(1);
				return;
			}
			lua->GetField(sName, -1);
			if (lua->IsNil())
			{
				lua->Pop(2);
				return;
			}
			lua->Pop(2);

			// Call
			try
			{
				call<void>(sName);
			}
			catch (luabind::error& e) {
				printf("[LuaScriptThread] Failed to call a thread callback!\n");

				if (lua->IsString(-1))
					lua->PrintErrorMessage(lua->GetString(-1), true, false);
				else 
					lua->PrintErrorMessage(const_cast<char*>(e.what()), true, false);
			}
			catch (LuaException& e) {
				printf("[LuaScriptThread] Failed to call a thread callback!\n");
				lua->PrintErrorMessage(const_cast<char*>(e.what()), true, true);
			}
			catch (std::exception& e) {
				printf("[LuaScriptThread] Failed to call a thread callback: %s\n", e.what());
			}
			catch (...) {
				printf("[LuaScriptThread] Failed to call a thread callback (unknown exception thrown)\n");
			}
		}

		// ScriptThreadWrapper Callbacks
		void LuaScriptThread::OnReset()
		{
			CallLuaCallback("OnReset");
		}
		void LuaScriptThread::OnRun()
		{
			CallLuaCallback("OnRun");
		}
		void LuaScriptThread::OnTick()
		{
			CallLuaCallback("OnTick");
		}
		void LuaScriptThread::OnKill()
		{
			CallLuaCallback("OnKill");
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
		luabind::class_<ScriptThreadWrapper>("CScriptThreadWrapper"),
		luabind::class_<LuaScriptThread, ScriptThreadWrapper>("ScriptThread")
			.def(luabind::constructor<>())
			.def("__tostring", &LuaScriptThread::__tostring)
			.def("__type", &LuaScriptThread::__type)
	];
}