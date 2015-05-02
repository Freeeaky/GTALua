// =================================================================================
// ScriptThreadWrapper
// =================================================================================
class ScriptThread : public scrThread
{
public:
	virtual eScriptThreadState Reset(uint32_t hash, DWORD64 pArgs, uint32_t iArgsCount);
	virtual eScriptThreadState Run(uint32_t opsToExecute);
	virtual eScriptThreadState Tick(uint32_t opsToExecute);
	virtual void Kill();

	virtual void OnRun() = 0;
};