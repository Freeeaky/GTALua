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
	void ProcessConsoleInput();

	// Game Version
	bool VersionCheck();
	char* GetGameVersion();

	// Configuration file(s)
	void LoadNativesINI();
	void LoadCallLayoutsINI();

private:
	bool m_bActive;
};

// =================================================================================
// Global Instance 
// =================================================================================
extern GTALua* g_pGTALua;