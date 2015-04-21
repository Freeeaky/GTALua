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
	static HMODULE GameModule;
	static DWORD64 Base;
	static DWORD64 Size;

	// Version
	static char* Version;

	// Function Wrappers
	DWORD64 Find(BYTE* bMask, char* szMask);

	// Calculate
	DWORD64 At(DWORD64 dwOffset);
}