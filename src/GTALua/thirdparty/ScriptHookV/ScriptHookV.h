// =================================================================================
// ScriptHookV
// =================================================================================
// Forward Declarations
namespace ScriptBinds { namespace Memory { class MemoryBlock; }; };
typedef void(*ScriptHook_Callback)();

// ScriptHook
namespace ScriptHook
{
	// Initialized
	extern bool CanRegisterThreads;

	// Imported
	void ScriptWait(DWORD dwTime);
	void ScriptRegister(ScriptHook_Callback ptr);
	void ScriptUnregister(ScriptHook_Callback ptr);

	void NativeInit(UINT64 hash);
	void NativePush64(UINT64 val);
	PUINT64 NativeCall();

	// Push Value Wrapper
	template <typename T>
	static inline void PushValue(T val)
	{
		UINT64 val64 = NULL;
		*reinterpret_cast<T *>(&val64) = val;
		NativePush64(val64);
	}

	// Call Wrapper
	template <typename T>
	static inline T Call()
	{
		return *reinterpret_cast<T *>(NativeCall());
	}
	static inline void CallVoid()
	{
		NativeCall();
	}

	// Push: Memory Pointer
	void PushMemory(ScriptBinds::Memory::MemoryBlock* pMemBlock);
}