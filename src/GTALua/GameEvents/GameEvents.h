// =================================================================================
// Game Events
// =================================================================================
class Mutex;
namespace GameEvents
{
	enum eGameEvents
	{
		GAME_EVENT_PED_CREATED,
		GAME_EVENT_VEHICLE_CREATED
	};
	struct GameEventCallback
	{
		GameEventCallback(eGameEvents typ, int param1 = 0, int param2 = 0)
		{
			eType = typ;
			param_1 = param1;
			param_2 = param2;
		}
		eGameEvents eType;
		int param_1;
		int param_2;
	};

	extern vector<GameEventCallback> vEventQueue;
	extern Mutex QueueMutex;
	void DispatchEvents();
	int GetEntityID(__int64* pEntity);

	namespace Install
	{
		void Entity();
		void OnPedCreated();
		void OnVehicleCreated();
	}
}