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
struct ScriptThreadContext
{
	uint32_t uiThreadID; // 0x4
	uint32_t uiScriptHash; // 0x8
	eScriptThreadState eState; // 0x12
	uint32_t uiIP; // 0x10
	uint32_t uiFrameSP; // 0x14
	uint32_t TimerA;
	uint32_t TimerB;
	uint32_t TimerC;
	uint32_t _unknown_1; // 0x1C
	uint32_t _unknown_2; // 0x20

	uint32_t _f2C;
	uint32_t _f30;
	uint32_t _f34;
	uint32_t _f38;
	uint32_t _f3C;
	uint32_t _f40;
	uint32_t _f44;
	uint32_t _f48;
	uint32_t _f4C;
	uint32_t _f50;

	uint32_t pad1;
	uint32_t pad2;
	uint32_t pad3;

	uint32_t _unknown_3; // 0x60
	BYTE _shit2[68]; // 0xA4 (168)

	uint32_t pad[68 / 4];
};

// =================================================================================
// ScriptThread
// =================================================================================
class ScriptThread
{
public:
	ScriptThreadContext m_pContext;
	void* m_pStack;
	void* pad;
	void* pad2;

	const char* m_szExitMessage;

	virtual ~ScriptThread() {};
	virtual eScriptThreadState Reset(uint32_t hash, void* pArgs, uint32_t iArgumentsCount) = 0;
	virtual eScriptThreadState Run(uint32_t iNumber) = 0;
	virtual eScriptThreadState Tick(uint32_t iNumber) = 0;
	virtual void Kill() = 0;

	ScriptThreadContext* GetContext() { return &m_pContext; }
};