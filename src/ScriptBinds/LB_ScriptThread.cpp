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
			// callback bools
			// I could also check if the callback is lua_nil but that's slower than checking bools
			m_bHasResetCallback = false;
			m_bHasRunCallback = false;
			m_bHasTickCallback = false;
			m_bHasKillCallback = false;
		}

		LuaScriptThread::~LuaScriptThread()
		{

		}

		// Callbacks
		void LuaScriptThread::RegisterCallback_OnReset(luabind::object callback)
		{
			m_lResetCallback = callback;
			m_bHasResetCallback = true;
		}
		void LuaScriptThread::RegisterCallback_OnRun(luabind::object callback)
		{
			m_lRunCallback = callback;
			m_bHasRunCallback = true;
		}
		void LuaScriptThread::RegisterCallback_OnTick(luabind::object callback)
		{
			m_lTickCallback = callback;
			m_bHasTickCallback = true;
		}
		void LuaScriptThread::RegisterCallback_OnKill(luabind::object callback)
		{
			m_lKillCallback = callback;
			m_bHasKillCallback = true;
		}
		void LuaScriptThread::CallLuaCallback(luabind::object callback)
		{
			try
			{
				luabind::call_function<void>(callback);
			}
			catch (LuaException& e) {
				printf("[LuaScriptThread] Failed to call a thread callback!\n");
				lua->PrintErrorMessage(const_cast<char*>(e.what()), true, true);
			}
		}

		// ScriptThreadWrapper Callbacks
		void LuaScriptThread::OnReset()
		{
			if (m_bHasResetCallback)
				CallLuaCallback(m_lResetCallback);
		}
		void LuaScriptThread::OnRun()
		{
			if (m_bHasRunCallback)
				CallLuaCallback(m_lRunCallback);
		}
		void LuaScriptThread::OnTick()
		{
			if (m_bHasTickCallback)
				CallLuaCallback(m_lTickCallback);
		}
		void LuaScriptThread::OnKill()
		{
			if (m_bHasKillCallback)
				CallLuaCallback(m_lKillCallback);
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
			.def("OnReset", &LuaScriptThread::RegisterCallback_OnReset)
			.def("OnRun", &LuaScriptThread::RegisterCallback_OnRun)
			.def("OnTick", &LuaScriptThread::RegisterCallback_OnTick)
			.def("OnKill", &LuaScriptThread::RegisterCallback_OnKill)
			.def("__tostring", &LuaScriptThread::__tostring)
			.def("__type", &LuaScriptThread::__type)
	];
}