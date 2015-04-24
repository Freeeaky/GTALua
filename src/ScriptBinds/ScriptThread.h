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
			void CallLuaCallback(char* callback);
		};
	}
}