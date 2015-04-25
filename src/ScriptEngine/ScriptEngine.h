// =================================================================================
// Includes
// =================================================================================
#include "rage.h"
#include "ScriptThread.h"
#include "ScriptHandlerManager.h"
#include "ScriptThreadWrapper.h"
#include "Natives.h"
#include "NativeInvocation.h"

// =================================================================================
// ScriptEngine
// =================================================================================
namespace ScriptEngine
{
	// Addresses
	extern rage::PtrCollection* ThreadCollection;
	extern uint32_t* ThreadID;
	extern uint32_t* ThreadCount;
	extern ScriptHandlerManager* HandlerManager;
	bool CollectAddresses();

	// Script Threads
	ScriptThread* GetActiveThread();
	void SetActiveThread(ScriptThread* pThread);
	bool CreateScriptThread(ScriptThread* pThread);

	// Natives
	Native_t GetNativeAddress(DWORD64 hHash);
}