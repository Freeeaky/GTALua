// ====================================================================================================
// Lua Manager
// ====================================================================================================
#ifndef H_LUA_MANAGER
#define H_LUA_MANAGER

class Mutex;

class LuaManager
{
public:
	// Main
	LuaManager();
	void Init();
	void Destroy();
	lua_State* State() { return m_pState; }

	// Mutex
	Mutex* GetMutex() { return m_pMutex; }

	// Utility
	bool IncludeFile(char* sPath);									// nothrow, uses ProtectedCall
	void AddToFileList(char* sPath);
	bool IsOnFileList(char* sPath);
	void ClearFileList();

	// Error Handling
	bool Success();
	void CheckForLuaErrors(int iErrorIndex = 0);
	void PrintErrorMessage(char* sErrorMsg, bool bDoNotTriggerLuaError = false, bool bDoNotCreateTraceback = false);

	// Calling
	void Call(int iArgCount = 0, int iResultCount = 0);				// can throw an exception! make sure to catch it
	bool ProtectedCall(int iArgCount = 0, int iResultCount = 0);	// calls Call() but catches itself. return value = success?

	// Get*
	void GetGlobal(char* sName);
	void GetEvent(char* sName);
	char* GetString(int iStackIndex = -1);
	double GetNumber(int iStackIndex = -1);
	bool GetBool(int iStackIndex = -1);
	void GetTypeName(int iStackIndex);

	// Is*
	bool IsNil(int iStackIndex = -1);
	bool IsString(int iStackIndex = -1);
	bool IsNumber(int iStackIndex = -1);
	bool IsBool(int iStackIndex = -1);
	bool IsTable(int iStackIndex = -1);
	bool IsUserData(int iStackIndex = -1);

	// Push*
	void PushString(char* sString);
	void PushNil();
	void PushNumber(double iNumber);
	void PushBool(bool bBool);
	void PushValue(int iStackIndex = -1);

	// Tables
	bool GetField(char* sKey, int iStackIndex = -1);
	void SetField(char* sKey, int iStackIndex = -1);

	// Stack Operations
	int Top(); // stack count [argument count]
	void Pop(int iStackIndex = 1);
	void SetTop(int iStackIndex);
	void Remove(int iStackIndex = -1);

	// Debug Functions
	lua_Debug GetDebugInformation();
	char* DebugGetFilename();
	void DebugGetPath(char *path);
	void DumpStack();
	
private:
	std::vector<std::string> m_vFileList;
	lua_State* m_pState;
	bool m_bSuccess;
	Mutex* m_pMutex;
};

// ====================================================================================================
// Error Handling
// ====================================================================================================
int LuaPanicHandler(lua_State* L) throw(...);

extern LuaManager* lua;

#endif