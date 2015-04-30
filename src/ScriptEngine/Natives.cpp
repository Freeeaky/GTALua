// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "ScriptEngine.h"
#include "Memory/Memory.h"
#include "UTIL/UTIL.h"

// =================================================================================
// Native Address
// TODO: Pattern for Native List (48 8D 1D ? ? ? ? 33 F6 48 8B 3B) 
// =================================================================================
Natives::Native_t Natives::FindNative(DWORD64 hHash)
{
	NativeRegisterStruct** pNatives = (NativeRegisterStruct**)GameMemory::At(0x29932B0);
	NativeRegisterStruct* pTable = pNatives[hHash & 0xFF];

	while (pTable != NULL)
	{
		for (int i = 0; i < pTable->uiEntryCount; i++)
		{
			if (hHash == pTable->uiHashes[i])
				return pTable->pRegisteredNatives[i];
		}

		pTable = pTable->pNext;
	}

	return NULL;
}

// =================================================================================
// Category By Name 
// =================================================================================
Natives::eNativeCategory Natives::FindCategoryByName(char* sName)
{
	// find category
	eNativeCategory eCategory = NATIVE_UNKNOWN;
	for (int i = 0; i < _NATIVE_ENUM_SIZE; i++)
	{
		if (strcmp(sName, CategoryNames[i]) == 0)
		{
			return (eNativeCategory)i;
		}
	}

	// unknown
	return NATIVE_UNKNOWN;
}