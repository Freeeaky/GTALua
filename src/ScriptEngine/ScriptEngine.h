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
	// Getter
	rage::PtrCollection* GetThreadCollection();
	uint32_t* GetThreadId();
	uint32_t* GetThreadCount();
	ScriptHandlerManager* GetHandlerManager();

	// Script Threads
	ScriptThread* GetActiveThread();
	void SetActiveThread(ScriptThread* pThread);
	bool CreateScriptThread(ScriptThread* pThread);

	// Natives
	Native_t GetNativeAddress(DWORD64 hHash);
}