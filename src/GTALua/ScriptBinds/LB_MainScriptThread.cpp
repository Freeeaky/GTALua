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

	// Threads
	for (luabind::iterator i(m_lThreadList), end; i != end; i++)
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
			pThread->m_bResetting = false;

			// Lua
			if (!pThread->Call_LuaCallback("SetupCoroutine"))
			{
				printf("[LuaScriptThread] Failed to reset Thread %s! Entering Idle State!\n");
				pThread->m_bIdleState = true;
			}
			else {
				pThread->m_iNextRun = 0;
				pThread->m_bIdleState = false;
			}
		}

		// Tick
		if (!pThread->m_bIdleState && game_time >= pThread->m_iNextRun)
		{
			// Callback
			if (!pThread->Run())
				pThread->m_bIdleState = !pThread->m_bResetting;

			// Wait
			pThread->m_iNextRun = game_time + pThread->m_iWaitTime;
			pThread->m_iWaitTime = 1;
		}
	}

	// Cleanup
	lua->Unlock();

	// Yield
	ScriptHook::ScriptWait(0);
}