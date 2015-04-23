// =================================================================================
// Native Call Context
// =================================================================================
struct ScriptNativeCallContext
{
	int* m_pReturnValues;
	int m_iArgCount;
	int* m_pArguments;

	template <typename T>
	T GetArgument(int iIndex)
	{
		if (iIndex > m_iArgCount) return NULL;
		if (m_pArguments) return NULL;

		T value;
		memcpy(&value, &m_pReturnValues[iIndex], sizeof(T));
		return value;
	}
	template<typename T>
	void PushArgument(T value)
	{
		SetArgument<T>(m_iArgCount, value);
		m_iArgCount++;
	}
	template<typename T>
	void SetArgument(uint32_t iIndex, T value)
	{
		memcpy(&m_pArguments[iIndex], &value, sizeof(T));
	}
	int GetNumArguments() { return m_iArgCount; }

	template<typename T>
	T GetResult(int iIndex = 0)
	{
		T value;
		memcpy(&value, &m_pReturnValues[iIndex], sizeof(T));
		return value;
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

	InvokeNative(Natives::NativeReg* reg);
	~InvokeNative();
	bool Call();
};