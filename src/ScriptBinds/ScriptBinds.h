// =================================================================================
// Script Binds 
// =================================================================================
namespace ScriptBinds
{
	namespace GeneralFunctions
	{
		void Bind();
	}

	namespace ScriptHookBind
	{
		void Bind();
	}

	namespace Types
	{
		void Bind();
	}

	namespace NativesWrapper
	{
		void Bind();
	}

	namespace Console
	{
		void Bind();
	}

	namespace FileModule
	{
		void Bind();
	}

	namespace ScriptThread
	{
		// ScriptThread
		class LuaScriptThread : public luabind::wrap_base
		{
		public:
			LuaScriptThread(string sName);
			~LuaScriptThread();

			// Internal
			void Run();

			// Getter
			string GetName() { return m_sName; };
			bool IsActive() { return m_bActive; };

			// Thread Functions
			void Wait(DWORD uiTime);

		private:
			string m_sName;
			bool m_bActive;
		};

		// Bind
		void Bind();
	}
}