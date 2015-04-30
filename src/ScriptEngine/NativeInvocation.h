// =================================================================================
// Native Call Context
// =================================================================================
struct ScriptNativeCallContext
{
	int* m_pReturnValues;
	int m_iArgCount;
	int* m_pArguments;

	// Arguments
	template <typename T>
	T GetArgument(int iIndex)
	{
		T value;
		memcpy(&value, &m_pArguments[iIndex], sizeof(T));
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

	// Result
	template<typename T>
	T GetResult(int iIndex = 0)
	{
		T value;
		memcpy(&value, &m_pReturnValues[iIndex], sizeof(T));
		return value;
	}

	// Special: rage::CVector
	void PushVector(rage::CVector vec)
	{
		SetArgument<rage::CVector>(m_iArgCount, vec);
		m_iArgCount += 3;
	}
};

// =================================================================================
// Native Invocation
// =================================================================================
struct InvokeNative : public ScriptNativeCallContext
{
	DWORD64 m_hHash;

	InvokeNative(Natives::NativeReg* reg);
	InvokeNative(DWORD64 hHash);
	~InvokeNative();
	bool Call();
};