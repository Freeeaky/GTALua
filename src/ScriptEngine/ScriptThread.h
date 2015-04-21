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
// Native Call Context
// =================================================================================
struct ScriptNativeCallContext
{
	DWORD64 m_pReturn;
	uint32_t m_iArgCount;
	DWORD64 m_pArguments;

	DWORD64 GetArgument(int iIndex);
	int GetNumArguments();

	DWORD64 SetResult(int iIndex, DWORD64 pValue);
	DWORD64 GetResult(int iIndex);
};

// =================================================================================
// Thread Context
// =================================================================================
struct ScriptThreadContext
{
	uint32_t uiThreadID;
	uint32_t uiScriptHash;
	eScriptThreadState eState;
	uint32_t uiIP;
	uint32_t uiFrameSP;
	uint32_t TimerA; // + 24
	uint32_t TimerB; // + 28
	uint32_t TimerC; // + 32, aka + 40
	uint32_t _mUnk1;
	uint32_t _mUnk2;
	uint32_t _f2C;
	uint32_t _f30;
	uint32_t _f34;
	uint32_t _f38;
	uint32_t _f3C;
	uint32_t _f40;
	uint32_t _f44;
	uint32_t _f48;
	uint32_t _f4C;
	uint32_t _f50; // should be +88 aka +80; stack size?

	uint32_t pad1;
	uint32_t pad2;
	uint32_t pad3;

	uint32_t _set1;

	uint32_t pad[68 / 4];
};

// =================================================================================
// ScriptThread
// =================================================================================
class ScriptThread
{
public:
	ScriptThreadContext m_pContext;

	virtual ~ScriptThread() {};
	virtual eScriptThreadState Reset(uint32_t hash, void* pArgs, uint32_t iArgumentsCount) = 0;
	virtual eScriptThreadState Run(uint32_t iNumber) = 0;
	virtual eScriptThreadState Tick(uint32_t iNumber) = 0;
	virtual void Kill() = 0;

	ScriptThreadContext* GetContext() { return &m_pContext; }
};