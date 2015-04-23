// =================================================================================
// GTALua 
// =================================================================================
class GTALua
{
public:
	GTALua();
	void ProperInit();

	// Game Version
	bool VersionCheck();
	char* GetGameVersion();

	// Configuration file(s)
	void LoadNativesINI();
	void LoadCallLayoutsINI();
};

// =================================================================================
// Global Instance 
// =================================================================================
extern GTALua* g_pGTALua;