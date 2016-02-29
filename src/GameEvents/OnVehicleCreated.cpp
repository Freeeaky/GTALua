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
typedef __int64*(__thiscall* World__CreateVehicle_t)(__int64* pThis, __int64* a2, __int64 a3, __int64 a4, __int64 a5, __int64* a6, bool a7, bool a8);
World__CreateVehicle_t pWorld_CreateVehicle = NULL;

// =================================================================================
// Callback
// =================================================================================
__int64* __fastcall World__CreateVehicle(__int64* pThis, __int64* a2, __int64 a3, __int64 a4, __int64 a5, __int64* a6, bool a7, bool a8)
{
	__int64* pEntity = pWorld_CreateVehicle(pThis, a2, a3, a4, a5, a6, a7, a8);
	if (pEntity != NULL)
	{
		int handle = GameEvents::GetEntityID(pEntity);

		if (handle != 0)
		{
			GameEvents::QueueMutex.Lock();
			GameEvents::vEventQueue.push_back(GameEvents::GameEventCallback(GameEvents::GAME_EVENT_VEHICLE_CREATED, handle));
			GameEvents::QueueMutex.Unlock();
		}
	}

	return pEntity;
}

// =================================================================================
// Install
// =================================================================================
void GameEvents::Install::OnVehicleCreated()
{
	// OnVehicleCreated
	Memory::HookFunction(GameMemory::Find((PBYTE)"\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x70\x18\x48\x89\x78\x20\x55\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x68\xB9", "xxxxxxxxxxxxxxxxxxxxxxxxxxxx"), &World__CreateVehicle, (void**)&pWorld_CreateVehicle);
}