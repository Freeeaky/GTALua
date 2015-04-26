// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "ScriptEngine.h"
#include "Memory/Memory.h"

// =================================================================================
// Thread 
// =================================================================================
typedef void(*ScriptThread__Init)(ScriptThread* pThis);
ScriptThreadWrapper::ScriptThreadWrapper()
{
	printf("INIT\n");

	// Context
	memset(&m_pContext, 0, sizeof(m_pContext));
	m_pContext.eState = THREAD_STATE_IDLE;
	m_pContext._unknown_1 = -1;
	m_pContext._unknown_2 = -1;
	m_pContext._unknown_3 = 1;

	// Init
	ScriptThread__Init pInit = (ScriptThread__Init)GameMemory::At(0x997850);
	pInit(this);

	// attach
	ScriptEngine::HandlerManager->AttachScript(this);
}

// =================================================================================
// Reset 
// =================================================================================

eScriptThreadState ScriptThreadWrapper::Reset(uint32_t hash, void* pArgs, uint32_t iArgumentsCount)
{
	printf("RESET\n");

	// Context
	memset(&m_pContext, 0, sizeof(m_pContext));
	m_pContext.eState = THREAD_STATE_IDLE;
	m_pContext._unknown_1 = -1;
	m_pContext._unknown_2 = -1;
	m_pContext._unknown_3 = 1;

	// Init
	ScriptThread__Init pInit = (ScriptThread__Init)GameMemory::At(0x997850);
	pInit(this);

	// attach
	ScriptEngine::HandlerManager->AttachScript(this);

	// Done
	return m_pContext.eState;
}

// =================================================================================
// Run 
// =================================================================================
eScriptThreadState ScriptThreadWrapper::Run(uint32_t iNumber)
{
	// Update Thread
	ScriptThread* pActiveThread = ScriptEngine::GetActiveThread();
	ScriptEngine::SetActiveThread(this);

	// Run
	bool bDown = (bool)(GetKeyState(VK_F9) & 0x8000);
	if (m_pContext.eState != THREAD_STATE_KILLED && GetAsyncKeyState(VK_F9) & 1)
		//	OnRun();
	{
		InvokeNative inv(0xAF35D0D2583051B0);
		if (!inv.Call())
		{
			printf("CALL FAILED\n");
		}
	}

	// Return
	ScriptEngine::SetActiveThread(pActiveThread);
	return m_pContext.eState;
}

// =================================================================================
// Tick
// =================================================================================
typedef eScriptThreadState (*ScriptThread__Tick)(ScriptThread* pThis, uint32_t iNumber);

eScriptThreadState ScriptThreadWrapper::Tick(uint32_t iNumber)
{
	// Callback
	if (m_pContext.eState != THREAD_STATE_KILLED)
		OnTick();

	// Tick
	ScriptThread__Tick pThread_Tick = (ScriptThread__Tick) GameMemory::At(0x9A2124);
	return pThread_Tick(this, iNumber);
}

// =================================================================================
// Kill 
// =================================================================================
typedef void (*ScriptThread__Kill)(ScriptThread* pThis);

void ScriptThreadWrapper::Kill()
{
	// Callback
	if (m_pContext.eState != THREAD_STATE_KILLED)
		OnKill();

	// Kill
	ScriptThread__Kill pThread_Kill = (ScriptThread__Kill) GameMemory::At(0x999128);
	pThread_Kill(this);
}

// =================================================================================
// Overwrite 
// =================================================================================
void ScriptThreadWrapper::OnRun() { }
void ScriptThreadWrapper::OnReset() { }
void ScriptThreadWrapper::OnTick() { }
void ScriptThreadWrapper::OnKill() { }