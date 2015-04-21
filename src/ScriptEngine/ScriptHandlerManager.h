// =================================================================================
// Script Handler Manager
// =================================================================================
class ScriptHandlerManager
{
public:
	virtual void Function0() = 0;
	virtual void Function1() = 0;
	virtual void Function2() = 0;
	virtual void Function3() = 0;
	virtual void Function4() = 0;
	virtual void Function5() = 0;
	virtual void Function6() = 0;
	virtual void Function7() = 0;
	virtual void Function8() = 0;
	virtual void Function9() = 0;
	virtual void AttachScript(ScriptThread* pThread) = 0;
};