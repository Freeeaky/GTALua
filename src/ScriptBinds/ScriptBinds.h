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
		// "Exception"
		// Hack to force stop
		struct ScriptThreadReset : public std::exception {};

		// ScriptThread
		class LuaScriptThread : public luabind::wrap_base
		{
		public:
			LuaScriptThread(string sName);
			~LuaScriptThread();

			// Internal
			bool IsCallbackPresent(char* sName);
			bool Call_LuaCallback(char* sName); // returns true if normal exit

			void Start();
			void Run();
			void Run_IdleState();

			// Getter
			string GetName() { return m_sName; };
			bool IsActive() { return m_bActive; };
			bool IsRunning() { return m_bActive && !m_bResetting; };

			// Thread Functions
			void Wait(DWORD uiTime);
			void Kill();
			void Reset();
		private:
			string m_sName;
			bool m_bActive;
			bool m_bResetting;
		};

		// Bind
		void Bind();
	}
}