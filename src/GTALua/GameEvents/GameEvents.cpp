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
#include "GameEvents.h"

// =================================================================================
// Globals
// =================================================================================
vector<GameEvents::GameEventCallback> GameEvents::vEventQueue;
Mutex GameEvents::QueueMutex;

// =================================================================================
// Dispatch
// =================================================================================
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