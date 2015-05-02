// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "ScriptEngine.h"
#include "Memory/Memory.h"

typedef void(*ScriptThread__Init_t)(ScriptThread* pThread);
ScriptThread__Init_t ScriptThread__Init = NULL;

// =================================================================================
// Reset 
// =================================================================================
eScriptThreadState ScriptThread::Reset(uint32_t hash, DWORD64 pArgs, uint32_t iArgsCount)
{
	printf("ScriptThreadWrapper::Reset\n");
	printf("%p\n", (DWORD64)(&m_pMissionCleanup) - (DWORD64)this);
	memset(&m_pContext, 0, sizeof(m_pContext));

	m_pContext.eState = THREAD_STATE_IDLE;
	m_pContext.uiScriptHash = hash;

	m_pContext._unknown_1 = -1;
	m_pContext._unknown_2 = -1;
	m_pContext._unknown_3 = 1;

	// TODO: Pattern
	if (ScriptThread__Init == NULL)
		ScriptThread__Init = GameMemory::At<ScriptThread__Init_t>(0x999024);

	ScriptThread__Init(this);

	m_pszExitMessage = "Normal exit";

	return m_pContext.eState;
}

// =================================================================================
// Run 
// =================================================================================
eScriptThreadState ScriptThread::Run(uint32_t opsToExecute)
{
	if (!m_pMissionCleanup)
	{
		printf("attach\n");
		ScriptEngine::HandlerManager->AttachScript(this);
		printf("val now: %p\n", m_pMissionCleanup);
		
		this->long_running_thread = true;
	}

	ScriptThread* pActiveThread = ScriptEngine::GetActiveThread();
	ScriptEngine::SetActiveThread(this);

	if (m_pContext.eState != THREAD_STATE_KILLED)
	{
		OnRun();
	}

	ScriptEngine::SetActiveThread(pActiveThread);
	return m_pContext.eState;
}

// =================================================================================
// Tick 
// =================================================================================
typedef eScriptThreadState(*ScriptThread__Tick_t)(ScriptThread* pThread, uint32_t opsToExecute);
ScriptThread__Tick_t ScriptThread__Tick = NULL;

eScriptThreadState ScriptThread::Tick(uint32_t opsToExecute)
{
	// TODO: Pattern
	if (ScriptThread__Tick == NULL)
		ScriptThread__Tick = GameMemory::At<ScriptThread__Tick_t>(0x9A3C34);

	// TODO: Add Callback

	// Wrapper
	return ScriptThread__Tick(this, opsToExecute);
}

// =================================================================================
// Kill
// =================================================================================
typedef void(*ScriptThread__Kill_t)(ScriptThread* pThread);
ScriptThread__Kill_t ScriptThread__Kill = NULL;

void ScriptThread::Kill()
{
	printf("ScriptThreadWrapper::Kill\n");

	if (ScriptThread__Kill == NULL)
		ScriptThread__Kill = GameMemory::At<ScriptThread__Kill_t>(0x99A96C);

	return ScriptThread__Kill(this);
}