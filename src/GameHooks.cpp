// =================================================================================
// Includes
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "Memory/Memory.h"
#include "ScriptEngine/ScriptEngine.h"

// =================================================================================
// BinkOpen
// Skips the intro movie so you can get ingame more quickly
// =================================================================================
typedef int(*BinkOpen_t)(DWORD64 a, DWORD64 b);
BinkOpen_t pBinkOpen = NULL;
bool bIsIntroMovie = true;

int BinkOpen_Hook(DWORD64 a, DWORD64 b)
{
	// Skip if first-time-call
	if (bIsIntroMovie)
	{
		bIsIntroMovie = false;
		return 0;
	}

	// Original
	return pBinkOpen(a, b);
}

ScriptThread* GetActiveThread()
{
	char* moduleTls = *(char**)__readgsqword(88);

	return *reinterpret_cast<ScriptThread**>(moduleTls + 0x830);
}

void SetActiveThread(ScriptThread* thread)
{
	char* moduleTls = *(char**)__readgsqword(88);

	*reinterpret_cast<ScriptThread**>(moduleTls + 0x830) = thread;
}

class TestThread : public ScriptThread
{
public:
	TestThread()
	{
		printf("TestThread ctor\n");
	}

	virtual void DoRun()
	{
		printf("RUN\n");
	}

	typedef void(*thread_init_t)(void* pThis);
	
	virtual eScriptThreadState		Reset(uint32_t scriptHash, void* pArgs, uint32_t argCount)
	{
		printf("ScriptThread::Reset\n");

		memset(&m_pContext, 0, sizeof(m_pContext));

		m_pContext.eState = THREAD_STATE_IDLE;
		m_pContext.uiScriptHash = scriptHash;
		m_pContext._mUnk1 = -1;
		m_pContext._mUnk2 = -1;
		m_pContext._set1 = 1;

		thread_init_t pInit = (thread_init_t)GameMemory::At(0x997850);
		pInit(this);

		

		return m_pContext.eState;
	}
	virtual eScriptThreadState		Run(uint32_t opsToExecute)
	{
		printf("ScriptThread::Run\n");

		ScriptThread* pActiveThread = GetActiveThread();
		SetActiveThread(this);

		if (m_pContext.eState != THREAD_STATE_KILLED)
			DoRun();

		SetActiveThread(pActiveThread);

		return m_pContext.eState;
	}

	typedef eScriptThreadState(*thread_tick_t)(void* pThis, uint32_t ops);

	virtual eScriptThreadState	Tick(uint32_t opsToExecute)
	{
		printf("ScriptThread::Tick\n");
		thread_tick_t thread_tick = (thread_tick_t) GameMemory::At(0x9A2124);
		return thread_tick(this, opsToExecute);
	}
	virtual void					Kill()
	{
		printf("ScriptThread::Kill\n");
	}
};

// =================================================================================
// ScriptEngine Init
// =================================================================================
typedef void(*ScriptEngine__Init_t)(DWORD64 ptr);
ScriptEngine__Init_t pScriptEngine__Init = NULL;

void ScriptEngine__Init(DWORD64 ptr)
{
	// Original
	pScriptEngine__Init(ptr);

	// Mark as initialized
	GameMemory::ScriptEngineInitialized = true;
	printf("[ScriptEngine] Initialized\n");

	// Thread
	TestThread* pThread = new TestThread();
	ScriptEngine::CreateScriptThread(pThread);
}

// =================================================================================
// Hooks
// =================================================================================
void GameMemory::InstallHooks()
{
	// BinkOpen (intro movie)
	Memory::HookLibraryFunction("bink2w64.dll", "BinkOpen", &BinkOpen_Hook, (void**)&pBinkOpen);

	// ScriptEngine::Init (Inspired by NTAuthority)
	Memory::HookFunction(GameMemory::Find((PBYTE)"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x33\xFF\x48\x8B\xD9\x66\x89\x39\x48\x89\x79\x04", "xxxx?xxxxxxxxxxxxxxxxx"), &ScriptEngine__Init, (void**)&pScriptEngine__Init);
}

// =================================================================================
// ShowWindow
// =================================================================================
typedef bool(__stdcall* ShowWindow_t)(HWND hWnd, int nCmdShow);
ShowWindow_t pShowWindow = NULL;

bool ShowWindow_Hook(HWND hWnd, int nCmdShow)
{
	if (hWnd == GetConsoleWindow() && nCmdShow == 0)
	{
		// Init
		// This gets called shortly before the game window is created
		// At this point, the game exe has been unpacked and patching is safe
		g_pGTALua->ProperInit();

		// Prevent hiding the console window
		return true;
	}

	// Original
	return pShowWindow(hWnd, nCmdShow);
}

// =================================================================================
// Init Hook
// =================================================================================
void GameMemory::InstallInitHook()
{
	// ShowWindow
	Memory::HookLibraryFunction("user32.dll", "ShowWindow", &ShowWindow_Hook, (void**)&pShowWindow);
}