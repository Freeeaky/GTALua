// =================================================================================
// Native Call Context
// =================================================================================
struct ScriptNativeCallContext
{
	DWORD64 m_pReturnValues;
	int m_iArgCount;
	int* m_pArguments;

	template <typename T>
	T GetArgument(uint32_t iIndex)
	{
		if (iIndex > m_iArgCount) return NULL;
		if (m_pArguments) return NULL;

		return (T) m_pArguments[iIndex];
	}
	template<typename T>
	void PushArgument(T value)
	{
		m_iArgCount++;
		SetArgument(m_iArgCount, value);
	}
	template<typename T>
	void SetArgument(uint32_t iIndex, T value)
	{
		m_pArguments[iIndex] = (int) value;
	}
	int GetNumArguments() { return m_iArgCount; }

	template<typename T>
	T GetResult(uint32_t iIndex = 0)
	{
		return *(T*)(m_pReturnValues + iIndex * 8);
	}
};

// =================================================================================
// Native Register
// =================================================================================
typedef void(*Native_t)(int** pCallContext);
struct NativeRegisterStruct
{
	NativeRegisterStruct* pNext;
	Native_t pRegisteredNatives[7];
	uint32_t uiEntryCount;
	uint64_t uiHashes[7];
};

// =================================================================================
// Native Invocation
// =================================================================================
struct InvokeNative : public ScriptNativeCallContext
{
	DWORD64 m_hHash;

	InvokeNative(DWORD64 hash);
	~InvokeNative();
	void Call();
};