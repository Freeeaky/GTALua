// =================================================================================
// Game Memory 
// =================================================================================
namespace GameMemory
{
	// Init
	void Init();
	void FetchVersion();

	// "Installers"
	void InstallPatches();
	void InstallInitHook();
	void InstallHooks();

	// Module
	extern HMODULE GameModule;
	extern DWORD64 Base;
	extern DWORD64 Size;

	// Version
	extern char* Version;

	// Function Wrappers
	DWORD64 Find(BYTE* bMask, char* szMask);

	// Calculate
	DWORD64 At(DWORD64 dwOffset);

	/*
	 * Content
	 */
	static bool ScriptEngineInitialized;
}