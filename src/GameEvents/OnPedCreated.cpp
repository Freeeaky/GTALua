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
typedef __int64*(__thiscall* World__CreatePed_t)(__int64* pThis, __int64 a2, __int64 a3, __int64 a4, bool a5, bool a6, bool a7);
World__CreatePed_t pWorld_CreatePed = NULL;

// =================================================================================
// Callback
// =================================================================================
__int64* __fastcall World__CreatePed(__int64* pThis, __int64 a2, __int64 a3, __int64 a4, bool a5, bool a6, bool a7)
{
	__int64* pEntity = pWorld_CreatePed(pThis, a2, a3, a4, a5, a6, a7);
	if (pEntity != NULL)
	{
		int handle = GameEvents::GetEntityID(pEntity);

		if (handle != 0)
		{
			GameEvents::QueueMutex.Lock();
			GameEvents::vEventQueue.push_back(GameEvents::GameEventCallback(GameEvents::GAME_EVENT_PED_CREATED, handle));
			GameEvents::QueueMutex.Unlock();
		}
	}

	return pEntity;
}

// =================================================================================
// Install
// =================================================================================
void GameEvents::Install::OnPedCreated()
{
	// OnPedCreated
	Memory::HookFunction(GameMemory::Find((PBYTE)"\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x68\x10\x48\x89\x78\x18\x41\x55", "xxxxxxxxxxxxxxxxx"), &World__CreatePed, (void**)&pWorld_CreatePed);
}