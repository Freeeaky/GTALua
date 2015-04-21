// =================================================================================
// Includes
// =================================================================================
#include "rage.h"
#include "ScriptThread.h"
#include "ScriptHandlerManager.h"
#include "ScriptThreadWrapper.h"

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

	// Active Thread
	ScriptThread* GetActiveThread();
	void SetActiveThread(ScriptThread* pThread);

	// Create Thread
	bool CreateScriptThread(ScriptThread* pThread);
}