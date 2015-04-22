// =================================================================================
// UTIL
// =================================================================================
namespace UTIL
{
	void ReplaceString(std::string& str, const std::string& from, const std::string& to);
	void ParseFilePath(std::string& path); // replaces \/ /\ // \\ so they can be compared to other paths

	void Lowercase(char* sText);
	void Uppercase(char* sText);
};

// =================================================================================
// Include
// =================================================================================
#include "IniFile.h"