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
class ScriptThread
{
protected:
	ScriptThreadContext m_pContext;
	void* m_pStack; // B0
	char _0x0B8[16];
	const char* m_sExitMessage; // 0xC8

public:
	virtual ~ScriptThread() { };
	virtual eScriptThreadState Reset(uint32_t hash, DWORD64 pArgs, uint32_t iArgsCount) = 0;
	virtual eScriptThreadState Run(uint32_t opsToExecute) = 0;
	virtual eScriptThreadState Tick(uint32_t opsToExecute) = 0;
	virtual void Kill() = 0;

	ScriptThreadContext* GetContext() { return &m_pContext; }
};