// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds.h"

// =================================================================================
// Script Thread 
// =================================================================================
namespace ScriptBinds
{
	namespace ScriptThread
	{
		LuaScriptThread::LuaScriptThread() : ScriptThreadWrapper()
		{
			//m_lSelf = luabind::object(lua->State(), this);
		}

		LuaScriptThread::~LuaScriptThread()
		{

		}

		// Lua Callback
		void LuaScriptThread::CallLuaCallback(char* sName)
		{
			try
			{
				call<void>(sName);
			}
			catch (luabind::error e) {
				printf("[LuaScriptThread] Failed to call a thread callback!\n");

				if (lua->IsString(-1))
					lua->PrintErrorMessage(lua->GetString(-1), true, false);
				else 
					lua->PrintErrorMessage(const_cast<char*>(e.what()), true, false);
			}
			catch (LuaException e) {
				printf("[LuaScriptThread] Failed to call a thread callback!\n");
				lua->PrintErrorMessage(const_cast<char*>(e.what()), true, true);
			}
			catch (std::exception e) {
				printf("[LuaScriptThread] Failed to call a thread callback: %s\n", e.what());
			}
			catch (...) {
				printf("[LuaScriptThread] Failed to call a thread callback (unknown exception thrown)\n");
			}
		}

		// ScriptThreadWrapper Callbacks
		void LuaScriptThread::OnReset()
		{
			printf("call reset!\n");
			//CallLuaCallback("OnReset");
		}
		void LuaScriptThread::OnRun()
		{
			printf("call run!\n");
			CallLuaCallback("OnRun");
		}
		void LuaScriptThread::OnTick()
		{
			printf("call tick!\n");
			//CallLuaCallback("OnTick");
		}
		void LuaScriptThread::OnKill()
		{
			printf("call kill!\n");
			//CallLuaCallback("OnKill");
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
			.def("OnRun", &ScriptThreadWrapper::OnRun)
			.def("OnReset", &ScriptThreadWrapper::OnReset)
			.def("OnTick", &ScriptThreadWrapper::OnTick)
			.def("OnKill", &ScriptThreadWrapper::OnKill)
			.def("__tostring", &LuaScriptThread::__tostring)
			.def("__type", &LuaScriptThread::__type)
	];
}