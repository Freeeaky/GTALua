// =================================================================================
// ScriptThreadWrapper
// =================================================================================
class ScriptThreadWrapper : public ScriptThread
{
protected:
	char gta_pad[64];
	void* m_pMissionCleanup;
	char gta_pad2[40];
	char flag1;
	char m_networkFlag;
	char gta_pad3[22];

public:
	// Internal, do not overwrite
	virtual eScriptThreadState Reset(uint32_t hash, void* pArgs, uint32_t iArgumentsCount);
	virtual eScriptThreadState Run(uint32_t iNumber);
	virtual eScriptThreadState Tick(uint32_t iNumber);
	virtual void Kill();

	// Overwrite
	virtual void OnReset();
	virtual void OnRun();
	virtual void OnTick();
	virtual void OnKill();
};