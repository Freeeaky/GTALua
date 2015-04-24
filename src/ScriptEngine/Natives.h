// =================================================================================
// Natives
// =================================================================================
namespace Natives
{
	// Category Enum
	enum eNativeCategory
	{
		NATIVE_UNKNOWN,
		NATIVE_APP,
		NATIVE_AUDIO,
		NATIVE_CAM,
		NATIVE_UI,
		NATIVE_GAMEPLAY,
		NATIVE_CONTROLS,
		NATIVE_PED,
		NATIVE_PLAYER,
		NATIVE_AI,
		NATIVE_VEHICLE,
		NATIVE_OBJECT,
		NATIVE_SCRIPT,
		NATIVE_STATS,
		NATIVE_STREAMING,
		NATIVE_PATHFIND,
		NATIVE_WEAPON,
		NATIVE_ZONE,
		NATIVE_GRAPHICS,
		NATIVE_CUTSCENE,
		NATIVE_TIME,
		NATIVE_NETWORK,
		NATIVE_BRAIN,
		NATIVE_WATER,
		NATIVE_DECISION_EVENT,
		NATIVE_INTERIOR,
		NATIVE_ROPE,
		NATIVE_MOBILE,
		NATIVE_ENTITY,
		NATIVE_ITEMSET,
		NATIVE_WORLD_PROBE,
		NATIVE_DECORATOR,
		_NATIVE_ENUM_SIZE
	};

	// Category Names
	static const char* CategoryNames[_NATIVE_ENUM_SIZE + 1] = {
		"unknown",
		"app",
		"audio",
		"cam",
		"uI",
		"gameplay",
		"controls",
		"ped",
		"player",
		"aI",
		"vehicle",
		"object",
		"script",
		"stats",
		"streaming",
		"pathfind",
		"weapon",
		"zone",
		"graphics",
		"cutscene",
		"time",
		"network",
		"brain",
		"water",
		"decisionevent",
		"interior",
		"rope",
		"mobile",
		"entity",
		"itemset",
		"worldprobe",
		"decorator",
		"datafile"
	};

	// Find category by name
	eNativeCategory FindCategoryByName(char* sName);

	// Registered Natives
	struct NativeReg
	{
		bool bValid;
		const char* sCategory;
		const char* sName;
		DWORD64 hHash;

		// Call Layout
		bool bHasCallLayout;
		const char* sCallLayout;
	};
	extern std::vector<NativeReg*> Registered[_NATIVE_ENUM_SIZE + 1];
}