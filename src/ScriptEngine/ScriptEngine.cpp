// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "ScriptEngine.h"
#include "Memory/Memory.h"

// =================================================================================
// Addresses
// =================================================================================
rage::PtrCollection<ScriptThread>* ScriptEngine::ThreadCollection = NULL;
uint32_t* ScriptEngine::ThreadID = NULL;
uint32_t* ScriptEngine::ThreadCount = NULL;
ScriptHandlerManager* ScriptEngine::HandlerManager = NULL;

// =================================================================================
// Collect
// =================================================================================
bool ScriptEngine::CollectAddresses()
{
	// Scan
	ThreadCollection = GameMemory::FindAbsoluteAddress<rage::PtrCollection<ScriptThread>*>((PBYTE)"\x4C\x8B\x05\x00\x00\x00\x00\x41\x8B\xDF", "xxx????xxx", 3);
	ThreadID = GameMemory::FindAbsoluteAddress<uint32_t*>((PBYTE)"\x89\x15\x00\x00\x00\x00\x48\x8B\x0C\xD8", "xx????xxxx", 2);
	ThreadCount = GameMemory::FindAbsoluteAddress<uint32_t*>((PBYTE)"\xFF\x05\x00\x00\x00\x00\xFF\x40\x5C", "xx????xxx", 2);
	HandlerManager = GameMemory::FindAbsoluteAddress<ScriptHandlerManager*>((PBYTE)"\x48\x8B\x05\x00\x00\x00\x00\x48\x8D\x0D\x00\x00\x00\x00\x48\x8B\xD3\x48\x83\xC4\x20\x5B\x48\xFF\x60\x50", "xxx????xxx????xxxxxxxxxxxx", 3);

	// If one of them is 0, the pattern is outdated
	return ! (ThreadCollection == NULL ||
		ThreadID == NULL ||
		ThreadCount == NULL ||
		HandlerManager == NULL);
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
// Create Thread 
// =================================================================================
bool ScriptEngine::CreateScriptThread(ScriptThread* pNewThread)
{
	int iSlot = 0;

	// Find Slot
	for (auto& thread : *ThreadCollection)
	{
		auto context = thread->GetContext();

		if (context->uiThreadID == 0)
			break;

		iSlot++;
	}

	// Slot-Check
	if (iSlot == ThreadCollection->count())
		return false;

	// Reset
	pNewThread->Reset((*ThreadCount) + 1, NULL, 0);
	
	// Thread ID & Count
	if (*ThreadID == 0)
		(*ThreadID)++;
	pNewThread->GetContext()->uiThreadID = *ThreadID;
	(*ThreadID)++;
	(*ThreadCount)++;

	// Register Thread in Game Memory
	ThreadCollection->set(iSlot, pNewThread);
	HandlerManager->AttachScript(pNewThread);

	// Done
	return true;
}