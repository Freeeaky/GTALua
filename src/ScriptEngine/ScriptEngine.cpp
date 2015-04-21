// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "ScriptEngine.h"
#include "Memory/Memory.h"

rage::PtrCollection* GetScriptThreadCollection()
{
	return (rage::PtrCollection*) GameMemory::At(0x2972CC0);
	//return (rage::PtrCollection*) (GameMemory::Find((PBYTE)"\x48\x8B\x05\x00\x00\x00\x00\xFF\xC2", "xxx????xx") + 2);
}

uint32_t* GetScriptThreadId()
{
	return (uint32_t*)GameMemory::At(0x2971EA0);
	//return (uint32_t*) (GameMemory::Find((PBYTE)"\x8B\x15\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\xFF\xC2", "xx????xxx????xx") + 2);
}

uint32_t* GetScriptThreadCount()
{
	return (uint32_t*)GameMemory::At(0x2972C8C);
	//return (uint32_t*) (GameMemory::Find((PBYTE)"\xFF\x05\x00\x00\x00\x00\xFF\x40\x5C", "xx????xxx") + 2);
}

ScriptHandlerManager* GetScriptHandleManager()
{
	return (ScriptHandlerManager*)GameMemory::At(0x227E7C0);
	//return (ScriptHandlerManager*)(GameMemory::Find((PBYTE)"\x48\x8D\x0D\x00\x00\x00\x00\x48\x8B\xD7\xE8\x00\x00\x00\x00\x8B\x15\x00\x00\x00\x00", "xxx????xxxx????xx????") + 2);
}

// =================================================================================
// CreateThread 
// =================================================================================
bool ScriptEngine::CreateScriptThread(ScriptThread* pThread)
{
	printf("find slot\n");

	// Thread Collection
	rage::PtrCollection* pThreadCollection = GetScriptThreadCollection();
	int iSlot = 0;

	printf("base %p\n", GameMemory::Base);
	printf("pThreadColleciton %p\n", pThreadCollection);
	printf("size: %i\n", pThreadCollection->m_iCount);

	// Search for slot
	for (uint16_t iIndex = 0; iIndex < pThreadCollection->m_iCount; iIndex++)
	{
		printf("in loop %i\n", iIndex);

		// Thread
		ScriptThread* pThread = (ScriptThread*) pThreadCollection->m_ppData[iIndex];
		if (pThread == NULL) return false;

		printf("get context\n");

		// Context
		ScriptThreadContext* pContext = pThread->GetContext();
		if (pContext == NULL) return false;

		printf("continue loop\n");

		// Found slot
		if (pContext->uiThreadID == 0)
			break;
	}

	printf("slot %i\n", iSlot);

	// Success-Check
	if (iSlot == pThreadCollection->m_iCount)
		return false;

	printf("slot %i still, now spannend\n", iSlot);

	// Increase number
	// Don't use thread id 0
	uint32_t* uiScriptThreadID = GetScriptThreadId();
	if (*uiScriptThreadID == 0)
		(*uiScriptThreadID)++;

	// Reset
	pThread->Reset(0, NULL, 0);

	// Update Context
	printf("thread id: %i\n", *uiScriptThreadID);
	pThread->GetContext()->uiThreadID = *uiScriptThreadID;
	
	// Increase id/count
	(*uiScriptThreadID)++;
	(*GetScriptThreadCount())++;

	// Add to collection
	pThreadCollection->m_ppData[iSlot] = (DWORD64*)pThread;

	// Attach Script
	GetScriptHandleManager()->AttachScript(pThread);

	printf("attached done go! %i\n", iSlot);

	// Done
	return true;
}