// =================================================================================
// Includes
// =================================================================================
#include "Includes.h"
#include "Memory.h"
#include "minhook/include/MinHook.h"

// =================================================================================
// Init
// =================================================================================
void Memory::Init()
{
	// Init MinHook
	if (MH_Initialize() != MH_OK)
	{
		printf("[Memory::Init] MH_Initialize failed!\n");
		return;
	}
}

// =================================================================================
// Hook Function
// =================================================================================
bool Memory::HookFunction(DWORD64 pAddress, void* pDetour, void** pOriginal)
{
	// Create Hook
	int iResult = MH_CreateHook((void*)pAddress, pDetour, pOriginal);
	if (iResult != MH_OK)
	{
		printf("[Memory::HookFunction] MH_CreateHook failed: %p [Error %i]\n", pAddress, iResult);
		return false;
	}

	// Enable Hook
	iResult = MH_EnableHook((void*)pAddress);
	if (iResult != MH_OK)
	{
		printf("[Memory::HookFunction] MH_EnableHook failed: %p [Error %i]\n", pAddress, iResult);
		return false;
	}

	// Success
	return true;
}
bool Memory::HookLibraryFunction(char* sLibrary, char* sName, void* pDetour, void** pOriginal)
{
	// Module
	HMODULE hModule = GetModuleHandle(sLibrary);
	if (hModule == NULL)
	{
		printf("[Memory::HookLibraryFunction] Module %s not (yet) loaded!\n", sLibrary);
		return false;
	}

	// Proc
	void* pProc = GetProcAddress(hModule, sName);
	if (pProc == NULL)
	{
		printf("[Memory::HookLibraryFunction] Module %s has no exported function %s!\n", sLibrary, sName);
		return false;
	}

	// Hook
	return HookFunction((DWORD64)pProc, pDetour, pOriginal);
}