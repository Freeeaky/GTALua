// =================================================================================
// Includes
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "Memory/Memory.h"
#include "UTIL/UTIL.h"
#include "GameEvents.h"

// =================================================================================
// Typedefs
// =================================================================================
// GetEntityID, returns 0 if fails
typedef DWORD32(__fastcall* GetEntityID_t)(__int64* pEntity);
GetEntityID_t pGetEntityID = NULL;

// =================================================================================
// Entity ID/Handle
// Should be failsafe
// =================================================================================
int GameEvents::GetEntityID(__int64* pEntity)
{
	if (pEntity == NULL || pGetEntityID == NULL)
		return 0;

	return pGetEntityID(pEntity);
}

// =================================================================================
// Install
// =================================================================================
void GameEvents::Install::Entity()
{
	// Entity ID
	pGetEntityID = GameMemory::Find<GetEntityID_t>((PBYTE)"\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x20\x8B\x15\x00\x00\x00\x00\x48\x8B\xF9\x48\x83\xC1\x10\x33\xDB", "xxxx?xxxx?xxxxxxx????xxxxxxxxx");
}