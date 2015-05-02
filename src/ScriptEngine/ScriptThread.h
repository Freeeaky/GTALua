// =================================================================================
// Thread State
// =================================================================================
enum eScriptThreadState
{
	THREAD_STATE_IDLE,
	THREAD_STATE_RUNNING,
	THREAD_STATE_KILLED,
	THREAD_STATE_UNKNOWN_1,
	THREAD_STATE_UNKNOWN_2
};

// =================================================================================
// Thread Context
// =================================================================================
class ScriptThreadContext
{
public:
	uint32_t uiThreadID; //0x0000 
	uint32_t uiScriptHash; //0x0004 
	eScriptThreadState eState; //0x0008 
	char _0x000C[20];
	uint32_t _unknown_1; //0x0020 
	uint32_t _unknown_2; //0x0024 
	char _0x0028[56];
	uint32_t _unknown_3; //0x0060 
	char _0x0064[68];
};//Size=0x00A8

// =================================================================================
// Script Thread
// =================================================================================
class scrThread
{
protected:
	ScriptThreadContext m_pContext; // 0x8 - 0xB0
	char _0x00B0[24];
	const char*	m_pszExitMessage; // 0xC8
	char _0x00D0[64];
	void* m_pMissionCleanup; // 0x110
	char _0x0118[41];
	bool long_running_thread; //0x0141 
	char _0x0142[22];

public:
	virtual ~scrThread() { };
	virtual eScriptThreadState Reset(uint32_t hash, DWORD64 pArgs, uint32_t iArgsCount) = 0;
	virtual eScriptThreadState Run(uint32_t opsToExecute) = 0;
	virtual eScriptThreadState Tick(uint32_t opsToExecute) = 0;
	virtual void Kill() = 0;

	ScriptThreadContext* GetContext() { return &m_pContext; }
};