// =================================================================================
// Includes
// =================================================================================
#include "Includes.h"
#include "Memory.h"

// =================================================================================
// Init
// =================================================================================
void GameMemory::Init()
{
	// Module
	GameModule = GetModuleHandle("GTA5.exe");
	if (GameModule == NULL)
	{
		printf("GameMemory::Init GTA5.exe module not found!");
		return;
	}

	// Base
	Base = (DWORD64) GameModule;
	printf("[GameMemory] Game Base: %p\n", Base);

	// Size
	Size = Memory::GetModuleSize(GameModule);
	printf("[GameMemory] Game Size: %p\n", Size);

	// Version
	Version = NULL;
	FetchVersion();

	// Init Hook
	InstallInitHook();
}

// =================================================================================
// Wrapper
// =================================================================================
DWORD64 GameMemory::At(DWORD64 dwOffset)
{
	return Base + dwOffset;
}
DWORD64 GameMemory::Find(BYTE* bMask, char* szMask)
{
	return Memory::Find(Base, Size, bMask, szMask);
}

// =================================================================================
// Version
// =================================================================================
void GameMemory::FetchVersion()
{
	// One-Time-Only
	if (Version != NULL) return;

	// Game EXE
	char* sVersionFile = Memory::GetModulePath((HMODULE) Base);
	if (sVersionFile == NULL)
	{
		printf("GameMemory::FetchVersion failed [Memory::GetModulePath returned 0]\n");
		return;
	}

	// Version Info Size
	DWORD dwVersionInfoSize = GetFileVersionInfoSize(sVersionFile, NULL);
	if (dwVersionInfoSize == NULL)
	{
		printf("GameMemory::FetchVersion failed! [GetFileVersionInfoSize returned 0]\n");
		
		// Cleanup
		free(sVersionFile);

		return;
	}

	// Version Info
	VS_FIXEDFILEINFO* pFileInfo = (VS_FIXEDFILEINFO*) new BYTE[dwVersionInfoSize];
	DWORD dwVersionHandle = NULL;
	if (!GetFileVersionInfo(sVersionFile, dwVersionHandle, dwVersionInfoSize, pFileInfo))
	{
		printf("GameMemory::FetchVersion failed! [GetFileVersionInfo failed]\n");
		
		// Cleanup
		free(sVersionFile);
		delete[] pFileInfo;

		return;
	}

	// Query
	UINT uiFileInfoLength = 0;
	VS_FIXEDFILEINFO* pVersionInfo = NULL;
	if (!VerQueryValue(pFileInfo, "\\", (LPVOID*) &pVersionInfo, &uiFileInfoLength) || uiFileInfoLength == 0)
	{
		printf("GameMemory::FetchVersion failed! [VerQueryValue failed]\n");

		// Cleanup
		free(sVersionFile);
		delete[] pFileInfo;
		if (pVersionInfo != NULL)
			delete pVersionInfo;

		return;
	}

	// Signature
	if (pVersionInfo->dwSignature != 0xFEEF04BD)
	{
		printf("GameMemory::FetchVersion failed! [Signature mismatch, got %X]\n", pVersionInfo->dwSignature);

		// Cleanup
		free(sVersionFile);
		delete[] pFileInfo;
		if (pVersionInfo != NULL)
			delete pVersionInfo;

		return;
	}

	// Build Version String
	Version = new char[128];
	sprintf(Version, "%d.%d.%d.%d",
		(pVersionInfo->dwFileVersionMS >> 16) & 0xffff,
		(pVersionInfo->dwFileVersionMS >> 0) & 0xffff,
		(pVersionInfo->dwFileVersionLS >> 16) & 0xffff,
		(pVersionInfo->dwFileVersionLS >> 0) & 0xffff);
	printf("[GameMemory] Detected Version %s\n", Version);

	// Cleanup
	free(sVersionFile);
	delete[] pFileInfo;
}