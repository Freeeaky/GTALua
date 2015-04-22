// =================================================================================
// Script Thread 
// =================================================================================
namespace ScriptBinds
{
	namespace ScriptThread
	{
		void Bind();

		// Lua Thread
		class LuaScriptThread
		{
		public:
			LuaScriptThread();
			~LuaScriptThread();

			// Lua
			char* __tostring() {
				return "ScriptThread";
			};
			char* __type() {
				return "ScriptThread";
			}
		};
	}
}