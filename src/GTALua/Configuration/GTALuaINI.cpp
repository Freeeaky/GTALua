// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "Memory/Memory.h"
#include "UTIL/UTIL.h"

// =================================================================================
// Parser
// =================================================================================
int ini_gtalua_parser(void* pCustom, const char* sSection, const char* sName, const char* sValue)
{
	// Console
	if (strcmp(sSection, "Console") == 0)
	{
		// Enabled
		if (strcmp(sName, "Enabled") == 0)
			g_pGTALua->GetConfig()->bConsole_Enabled = strcmp(sValue, "true") == 0;

		// Automatic Position
		if (strcmp(sName, "AutomaticPosition") == 0)
			g_pGTALua->GetConfig()->bConsole_AutomaticPosition = strcmp(sValue, "true") == 0;

		// Position
		if (strcmp(sName, "Manual_PosX") == 0)
			g_pGTALua->GetConfig()->iConsole_ManualX = atoi(sValue);
		if (strcmp(sName, "Manual_PosY") == 0)
			g_pGTALua->GetConfig()->iConsole_ManualY = atoi(sValue);
	}

	// Done
	return 1;
}

// =================================================================================
// Load 
// =================================================================================
void GTALua::LoadGTALuaIni()
{
	memset(&m_sConfig, 0, sizeof(m_sConfig));

	// Load ini
	IniFile file("GTALua/gtalua.ini", ini_gtalua_parser, NULL);
}