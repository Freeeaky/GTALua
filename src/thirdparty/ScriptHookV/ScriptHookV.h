// =================================================================================
// ScriptHookV
// =================================================================================
// Forward Declarations
namespace ScriptBinds { namespace Memory { class MemoryBlock; }; };

// Includes
#include "inc/main.h"
#pragma comment(lib, "src/thirdparty/ScriptHookV/lib/ScriptHookV.lib")

// ScriptHook
namespace ScriptHook
{
	// Initialized
	extern bool CanRegisterThreads;

	// Push Value Wrapper
	template <typename T>
	static inline void PushValue(T val)
	{
		UINT64 val64 = NULL;
		*reinterpret_cast<T *>(&val64) = val;
		nativePush64(val64);
	}

	// Call Wrapper
	template <typename T>
	static inline T Call()
	{
		return *reinterpret_cast<T *>(nativeCall());
	}
	static inline void CallVoid()
	{
		nativeCall();
	}

	// Push: Memory Pointer
	void PushMemory(ScriptBinds::Memory::MemoryBlock* pMemBlock);
}