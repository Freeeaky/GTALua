// =================================================================================
// Ini 
// =================================================================================
typedef int(*IniFile_IniParser)(void* pCustom, const char* sSection, const char* sName, const char* sValue);

class IniFile
{
public:
	IniFile(char* sPath, IniFile_IniParser pParser, void* pCustom = NULL);

	// TODO: Add stuff here
};