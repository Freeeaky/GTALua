// =================================================================================
// GTALua 
// =================================================================================
class GTALua
{
public:
	GTALua();
	~GTALua();
	void ProperInit();

	// Update
	void Update();
	void UpdateLoop();

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