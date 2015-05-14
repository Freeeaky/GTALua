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
	__int64* r = pWorld_CreatePed(pThis, a2, a3, a4, a5, a6, a7);
	if (r != NULL)
	{
		lua->GetMutex()->Lock();

		lua->GetEvent("OnPedCreated");
		lua->PushNumber(GetEntityID(r));
		lua->ProtectedCall(2);
		lua->Pop(2);

		lua->GetMutex()->Unlock();
	}

	return r;
}

// =================================================================================
// Create Vehicle
// =================================================================================
__int64* __fastcall World__CreateVehicle(__int64* pThis, __int64* a2, __int64 a3, __int64 a4, __int64 a5, __int64* a6, bool a7, bool a8)
{
	__int64* r = pWorld_CreateVehicle(pThis, a2, a3, a4, a5, a6, a7, a8);
	if (r != NULL)
	{
		lua->GetMutex()->Lock();

		lua->GetEvent("OnPedCreated");
		lua->PushNumber(GetEntityID(r));
		lua->ProtectedCall(2);
		lua->Pop(2);

		lua->GetMutex()->Unlock();
	}

	return r;
}

// =================================================================================
// Install Hooks
// =================================================================================
void GameMemory::InstallEventHooks()
{
	// World::CreateEntity/Ped
	GetEntityID = At<GetEntityID_t>(0x140A9D4);
	Memory::HookFunction(At(0x61A3DC), &World__CreatePed, (void**)&pWorld_CreatePed);
	Memory::HookFunction(At(0xE11F44), &World__CreateVehicle, (void**)&pWorld_CreateVehicle);
}