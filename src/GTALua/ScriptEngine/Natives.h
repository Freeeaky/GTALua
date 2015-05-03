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
		NATIVE_NETWORKCASH,
		NATIVE_FIRE,
		NATIVE_DECORATOR,
		NATIVE_DATAFile,
		NATIVE_DLC1,
		NATIVE_DLC2,
		NATIVE_UNK_SC,
		NATIVE_UNK1,
		NATIVE_UNK2,
		NATIVE_UNK3,
		NATIVE_SYSTEM,
		NATIVE_OTHER,
		_NATIVE_ENUM_SIZE
	};

	// Category Names
	static const char* CategoryNames[_NATIVE_ENUM_SIZE + 1] = {
		"UNKNOWN",
		"APP",
		"AUDIO",
		"CAM",
		"UI",
		"GAMEPLAY",
		"CONTROLS",
		"PED",
		"PLAYER",
		"AI",
		"VEHICLE",
		"OBJECT",
		"SCRIPT",
		"STATS",
		"STREAMING",
		"PATHFIND",
		"WEAPON",
		"ZONE",
		"GRAPHICS",
		"CUTSCENE",
		"TIME",
		"NETWORK",
		"BRAIN",
		"WATER",
		"DECISIONEVENT",
		"INTERIOR", 
		"ROPE",
		"MOBILE",
		"ENTITY",
		"ITEMSET",
		"WORLDPROBE",
		"NETWORKCASH",
		"FIRE",
		"DECORATOR",
		"DATAFILE",
		"DLC1",
		"DLC2",
		"UNK_SC",
		"UNK",
		"UNK1",
		"UNK2",
		"UNK3",
		"SYSTEM"
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

// =================================================================================
// Native Register
// =================================================================================
typedef void(*Native_t)(int** pCallContext);
struct NativeRegisterStruct
{
	NativeRegisterStruct* pNext;
	Native_t pRegisteredNatives[7];
	uint32_t uiEntryCount;
	uint64_t uiHashes[7];
};