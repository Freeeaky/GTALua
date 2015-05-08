// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptBinds.h"
#include "thirdparty/ScriptHookV/ScriptHookV.h"
using namespace ScriptBinds::ScriptThread;

// =================================================================================
// Main Thread 
// =================================================================================
void LuaScriptThread::Run_MainThread()
{
	lua->Lock();

	// Time
	int game_time = ScriptHook::GetGameTime();

	// Get Thread List
	m_self.get(lua->State());
	lua->GetField("ThreadList");
	luabind::object thread_list(luabind::from_stack(lua->State(), -1));

	// Threads
	for (luabind::iterator i(thread_list), end; i != end; i++)
	{
		luabind::object l_thread = *i;
		LuaScriptThread* pThread = luabind::object_cast<LuaScriptThread*>(l_thread);
		pThread->m_bActive = true;

		// Next Run
		if (pThread->m_iNextRun == 0)
			pThread->m_iNextRun = game_time - 1;

		// Reset
		if (pThread->m_bResetting)
		{
			printf("[LuaScriptThread] Thread %s reset\n", m_sName.c_str());
			pThread->Call_LuaCallback("SetupCoroutine");
			pThread->m_bResetting = false;
			pThread->m_iNextRun = game_time - 1;
			pThread->m_bIdleState = false;
		}

		// Tick
		if (game_time >= pThread->m_iNextRun && !pThread->m_bIdleState)
		{
			// Callback
			if (!pThread->Run())
			{
				pThread->m_bIdleState = !pThread->m_bResetting;
			}

			// Wait
			pThread->m_iNextRun = game_time + pThread->m_iWaitTime;
			pThread->m_iWaitTime = 1;
		}
	}

	// Cleanup
	lua->Pop(2);
	lua->Unlock();

	// Yield
	ScriptHook::ScriptWait(0);
}