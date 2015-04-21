// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "ScriptEngine.h"
#include "Memory/Memory.h"

// =================================================================================
// Getter
// TODO: Actually use the patterns
// =================================================================================
rage::PtrCollection* ScriptEngine::GetThreadCollection()
{
	return (rage::PtrCollection*) GameMemory::At(0x2972CC0);
	//return (rage::PtrCollection*) (GameMemory::Find((PBYTE)"\x48\x8B\x05\x00\x00\x00\x00\xFF\xC2", "xxx????xx") + 2);
}
uint32_t* ScriptEngine::GetThreadId()
{
	return (uint32_t*)GameMemory::At(0x2971EA0);
	//return (uint32_t*) (GameMemory::Find((PBYTE)"\x8B\x15\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\xFF\xC2", "xx????xxx????xx") + 2);
}
uint32_t* ScriptEngine::GetThreadCount()
{
	return (uint32_t*)GameMemory::At(0x2972C8C);
	//return (uint32_t*) (GameMemory::Find((PBYTE)"\xFF\x05\x00\x00\x00\x00\xFF\x40\x5C", "xx????xxx") + 2);
}
ScriptHandlerManager* ScriptEngine::GetHandlerManager()
{
	return (ScriptHandlerManager*)GameMemory::At(0x227E7C0);
	//return (ScriptHandlerManager*)(GameMemory::Find((PBYTE)"\x48\x8D\x0D\x00\x00\x00\x00\x48\x8B\xD7\xE8\x00\x00\x00\x00\x8B\x15\x00\x00\x00\x00", "xxx????xxxx????xx????") + 2);
}

// =================================================================================
// Script Thread 
// =================================================================================
ScriptThread* ScriptEngine::GetActiveThread()
{
	char* pTLS = *(char**)__readgsqword(88);
	return *(ScriptThread**) (pTLS + 0x830);
}
void ScriptEngine::SetActiveThread(ScriptThread* pThread)
{
	char* pTLS = *(char**)__readgsqword(88);
	*(ScriptThread**)(pTLS + 0x830) = pThread;
}

// =================================================================================
// CreateThread 
// =================================================================================
bool ScriptEngine::CreateScriptThread(ScriptThread* pThread)
{
	// Thread Collection
	rage::PtrCollection* pThreadCollection = GetThreadCollection();
	int iSlot = 0;

	// Search for slot
	for (uint16_t iIndex = 0; iIndex < pThreadCollection->m_iCount; iIndex++)
	{
		// Thread
		ScriptThread* pThread = (ScriptThread*) pThreadCollection->m_ppData[iIndex];
		if (pThread == NULL) return false;

		// Context
		ScriptThreadContext* pContext = pThread->GetContext();
		if (pContext == NULL) return false;

		// Found slot
		if (pContext->uiThreadID == 0)
			break;
	}

	// Success-Check
	if (iSlot == pThreadCollection->m_iCount)
		return false;

	// Increase number
	// Don't use thread id 0
	uint32_t* uiScriptThreadID = GetThreadId();
	if (*uiScriptThreadID == 0)
		(*uiScriptThreadID)++;

	// Reset
	pThread->Reset(0, NULL, 0);

	// Update Context
	pThread->GetContext()->uiThreadID = *uiScriptThreadID;
	
	// Increase id/count
	(*uiScriptThreadID)++;
	(*GetThreadCount())++;

	// Add to collection
	pThreadCollection->m_ppData[iSlot] = (DWORD64*)pThread;

	// Attach Script
	GetHandlerManager()->AttachScript(pThread);

	// Done
	return true;
}