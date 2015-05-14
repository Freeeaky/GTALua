// =================================================================================
// Includes
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "Memory/Memory.h"
#include "ScriptEngine/ScriptEngine.h"
#include "lua/Lua.h"
#include "thirdparty/ScriptHookV/ScriptHookV.h"
#include "UTIL/UTIL.h"

// =================================================================================
// Globals
// =================================================================================
vector<GameEvents::GameEventCallback> GameEvents::vEventQueue;
Mutex GameEvents::QueueMutex;

// =================================================================================
// typedefs for hooked functions
// =================================================================================
// GetEntityID, returns 0 if fails
typedef DWORD32(__fastcall* GetEntityID_t)(__int64* pEntity);
GetEntityID_t GetEntityID = NULL;

// CreatePed
typedef __int64*(__thiscall* World__CreatePed_t)(__int64* pThis, __int64 a2, __int64 a3, __int64 a4, bool a5, bool a6, bool a7);
World__CreatePed_t pWorld_CreatePed = NULL;

// CreateVehicle
typedef __int64*(__thiscall* World__CreateVehicle_t)(__int64* pThis, __int64* a2, __int64 a3, __int64 a4, __int64 a5, __int64* a6, bool a7, bool a8);
World__CreateVehicle_t pWorld_CreateVehicle = NULL;

// =================================================================================
// Create Ped
// =================================================================================
__int64* __fastcall World__CreatePed(__int64* pThis, __int64 a2, __int64 a3, __int64 a4, bool a5, bool a6, bool a7)
{
	__int64* pEntity = pWorld_CreatePed(pThis, a2, a3, a4, a5, a6, a7);
	if (pEntity != NULL)
	{
		GameEvents::QueueMutex.Lock();
		GameEvents::vEventQueue.push_back(GameEvents::GameEventCallback(GameEvents::GAME_EVENT_PED_CREATED, GetEntityID(pEntity)));
		GameEvents::QueueMutex.Unlock();
	}

	return pEntity;
}

// =================================================================================
// Create Vehicle
// =================================================================================
__int64* __fastcall World__CreateVehicle(__int64* pThis, __int64* a2, __int64 a3, __int64 a4, __int64 a5, __int64* a6, bool a7, bool a8)
{
	__int64* pEntity = pWorld_CreateVehicle(pThis, a2, a3, a4, a5, a6, a7, a8);
	if (pEntity != NULL)
	{
		GameEvents::QueueMutex.Lock();
		GameEvents::vEventQueue.push_back(GameEvents::GameEventCallback(GameEvents::GAME_EVENT_VEHICLE_CREATED, GetEntityID(pEntity)));
		GameEvents::QueueMutex.Unlock();
	}

	return pEntity;
}

// =================================================================================
// Install Hooks
// =================================================================================
void GameEvents::InstallHooks()
{
	// World::CreateEntity/Ped
	GetEntityID = GameMemory::Find<GetEntityID_t>((PBYTE)"\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x20\x8B\x15\x00\x00\x00\x00\x48\x8B\xF9\x48\x83\xC1\x10\x33\xDB", "xxxx?xxxx?xxxxxxx????xxxxxxxxx");
	Memory::HookFunction(GameMemory::Find((PBYTE)"\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x68\x10\x48\x89\x78\x18\x41\x55", "xxxxxxxxxxxxxxxxx"), &World__CreatePed, (void**)&pWorld_CreatePed);
	Memory::HookFunction(GameMemory::Find((PBYTE)"\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x70\x18\x48\x89\x78\x20\x55\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x68\xB9", "xxxxxxxxxxxxxxxxxxxxxxxxxxxx"), &World__CreateVehicle, (void**)&pWorld_CreateVehicle);
}

void GameEvents::DispatchEvents()
{
	// Mutex
	if (!QueueMutex.TryLock())
		return;
	lua->GetMutex()->Lock();

	// Loop & Dispatch
	for (vector<GameEventCallback>::iterator it = vEventQueue.begin(); it != vEventQueue.end(); ++it)
	{
		GameEventCallback gevent = *it;

		// Event
		if (gevent.eType == GAME_EVENT_PED_CREATED)
			lua->GetEvent("OnPedCreated");
		else if (gevent.eType == GAME_EVENT_VEHICLE_CREATED)
			lua->GetEvent("OnVehicleCreated");
		else
			continue;

		// Arguments
		lua->PushNumber(gevent.param_1);
		lua->PushNumber(gevent.param_2);
		
		// Call
		lua->ProtectedCall(3);
		lua->Pop(2);
	}

	// Clear Queue
	vEventQueue.erase(vEventQueue.begin(), vEventQueue.end());

	// Mutex
	lua->GetMutex()->Unlock();
	QueueMutex.Unlock();
}