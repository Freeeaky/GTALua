// =================================================================================
// Forward Declarations
// =================================================================================
class ScriptThread;
class ScriptHandlerManager;
class ScriptThreadWrapper;

// =================================================================================
// Includes
// =================================================================================
#include "rage.h"
#include "Natives.h"
#include "ScriptThread.h"
#include "ScriptThreadWrapper.h"
#include "ScriptHandlerManager.h"
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
}