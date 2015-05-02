// =================================================================================
// ScriptThreadWrapper
// =================================================================================
class ScriptThreadWrapper : public ScriptThread
{
protected:
	char _0x0000[64];
	void* m_pMissionCleanup; //0x0040 
	char _0x0048[40];
	char m_cFlag1; //0x0070 
	char m_cNetworkFlag; //0x0074 
	char _0x0078[22];

public:
	virtual eScriptThreadState Reset(uint32_t hash, DWORD64 pArgs, uint32_t iArgsCount);
	virtual eScriptThreadState Run(uint32_t opsToExecute);
	virtual eScriptThreadState Tick(uint32_t opsToExecute);
	virtual void Kill();

	virtual void OnRun() = 0;
};