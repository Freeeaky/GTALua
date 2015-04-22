// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"
#include "UTIL.h"

// ====================================================================================================
// Center
// ====================================================================================================
void UTIL::ReplaceString(std::string& str, const std::string& from, const std::string& to)
{
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}
void UTIL::ParseFilePath(std::string& path)
{
	ReplaceString(path, "\\", "/");
	ReplaceString(path, "/\\", "/");
	ReplaceString(path, "\\/", "/");
	ReplaceString(path, "//", "/");
}

void UTIL::Lowercase(char* sText)
{
	for (char* it = sText; *it != '\0'; ++it)
	{
		*it = tolower(*it);
		++it;
	}
}
void UTIL::Uppercase(char* sText)
{
	for (char* it = sText; *it != '\0'; ++it)
	{
		*it = toupper(*it);
		++it;
	}
}