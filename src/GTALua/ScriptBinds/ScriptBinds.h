// =================================================================================
// Script Binds 
// TODO: Clean up this file
// =================================================================================
void Lua_StartThread();

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
			bool IsCallbackPresent(char* sName);
			bool Call_LuaCallback(char* sName); // returns true if normal exit

			void Start();
			bool Run();
			void Run_IdleState();
			void Run_MainThread();

			// Getter
			string GetName() { return m_sName; };
			bool IsActive() { return m_bActive; };
			bool IsRunning() { return m_bActive && !m_bResetting; };

			// Thread Functions
			void Wait(DWORD uiTime);
			void Kill();
			void Reset();

			// Main Thread
			bool m_bRunsOnMainThread;
			bool m_bIsMainThread;
			int m_iWaitTime;
			int m_iNextRun;

			// Data
			string m_sName;
			bool m_bActive;
			bool m_bIdleState;
			bool m_bResetting;
		};

		// Bind
		void Bind();
	}

	namespace Memory
	{
		// =================================================================================
		// Memory 
		// =================================================================================
		class MemoryBlock
		{
		public:
			MemoryBlock(int iSize);
			~MemoryBlock();
			void Release();

			// Memory Pointer
			// Used for native invocation
			int* GetMemoryPointer() { return m_pMemory; };

			// Valid-Check
			bool IsValid();
			
			// Read
			template <typename T>
			T Read(int iOffset)
			{
				if (!IsValid())
				{
					lua->PushString("CMemoryBlock::Read - IsValid returned false!");
					throw luabind::error(lua->State());
				}
				if ((iOffset + sizeof(T)) > m_iSize)
				{
					lua->PushString("CMemoryBlock::Read - Offset out of allocated memory");
					throw luabind::error(lua->State());
				}
				return *(T*)(m_pMemory + iOffset);
			}

			// Write
			template <typename T>
			void Write(int iOffset, T tValue)
			{
				if (!IsValid())
				{
					lua->PushString("CMemoryBlock::Write - IsValid returned false!");
					throw luabind::error(lua->State());
				}
				if ((iOffset + sizeof(T)) > m_iSize)
				{
					lua->PushString("CMemoryBlock::Write - Offset out of allocated memory");
					throw luabind::error(lua->State());
				}
				*(T*)(m_pMemory + iOffset) = tValue;
			}

		private:
			int m_iSize;
			int* m_pMemory;
		};

		void Bind();
	}
}