// =================================================================================
// ScriptHookV
// I'm importing the functions because the ASI loader is too slow
// -> dinput8 is our loader
// =================================================================================
// Forward Declarations
namespace ScriptBinds { namespace Memory { class MemoryBlock; }; };

// ScriptHook
namespace ScriptHook
{
	// Initialized
	extern bool IsInitialized;
	extern bool CanRegisterThreads;
	bool Initialize();

	// Register Script
	typedef void(*scriptRegister_t)(HMODULE module, void(*LP_SCRIPT_MAIN)());
	extern scriptRegister_t RegisterScript;

	// Thread: Wait
	typedef void(*scriptWait_t)(DWORD t);
	extern scriptWait_t ThreadWait;

	// Init Native
	typedef void(*nativeInit_t)(DWORD64 hash);
	extern nativeInit_t InitNative;

	// Native Push
	typedef void(*nativePush64_t)(UINT64 value);
	extern nativePush64_t NativePush64;

	// Native Call
	typedef PUINT64(*nativeCall_t)();
	extern nativeCall_t CallNative;

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
		return *reinterpret_cast<T *>(CallNative());
	}
	static inline void CallVoid()
	{
		CallNative();
	}

	// Push: Memory Pointer
	void PushMemory(ScriptBinds::Memory::MemoryBlock* pMemBlock);
}