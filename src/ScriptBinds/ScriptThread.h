// =================================================================================
// Script Thread 
// =================================================================================
namespace ScriptBinds
{
	namespace ScriptThread
	{
		void Bind();

		// Lua Thread
		class LuaScriptThread : public ScriptThreadWrapper, public luabind::wrap_base
		{
		public:
			LuaScriptThread();
			~LuaScriptThread();

			// ScriptThreadWrapper Callbacks
			virtual void OnReset();
			virtual void OnRun();
			virtual void OnTick();
			virtual void OnKill();

			// Lua
			char* __tostring() {
				return "LuaScriptThread";
			};
			char* __type() {
				return "LuaScriptThread";
			};

		private:
			// Callbacks
			luabind::object m_lResetCallback;
			bool m_bHasResetCallback;
			luabind::object m_lRunCallback;
			bool m_bHasRunCallback;
			luabind::object m_lTickCallback;
			bool m_bHasTickCallback;
			luabind::object m_lKillCallback;
			bool m_bHasKillCallback;

			void CallLuaCallback(char* callback);
		};
	}
}