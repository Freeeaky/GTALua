// =================================================================================
// ScriptThreadWrapper
// =================================================================================
class ScriptThreadWrapper : public ScriptThread
{
public:
	ScriptThreadWrapper();
	//~ScriptThreadWrapper();

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