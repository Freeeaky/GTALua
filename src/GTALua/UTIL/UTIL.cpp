// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "UTIL.h"

// =================================================================================
// Console 
// _ needed
// =================================================================================
void UTIL::Attach_Console(bool bAutomatic, int x, int y)
{
	// Console
	AllocConsole();
	AttachConsole(GetCurrentProcessId());

	// Console Window
	HWND hConsole = GetConsoleWindow();
	RECT rect;
	GetWindowRect(hConsole, &rect);

	// Automatic
	// If you have multiple screens, this will automatically move the console to the 2nd
	if (bAutomatic && GetSystemMetrics(SM_CMONITORS) > 1)
	{
		// Desktop
		HWND hDesktop = GetDesktopWindow();
		RECT rDesktopRect;
		GetWindowRect(hDesktop, &rDesktopRect);

		// Update Position
		SetWindowPos(hConsole, NULL, rDesktopRect.right + 100, 50, rect.right - rect.left, rect.bottom - rect.top, 0);
	}

	// Manual
	if (!bAutomatic)
	{
		// Update Position
		SetWindowPos(hConsole, NULL, x, y, rect.right - rect.left, rect.bottom - rect.top, 0);
	}

	// Input/Output
	freopen("CON", "w", stdout);
	freopen("CONIN$", "r", stdin);
}

// =================================================================================
// String 
// =================================================================================
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

// =================================================================================
// File Names 
// =================================================================================
string UTIL::SplitFilename(string& str)
{
	size_t found;
	found = str.find_last_of("/");
	return str.substr(0, found);
}
void UTIL::ParseFilePath(std::string& path)
{
	ReplaceString(path, "\\", "/");
	ReplaceString(path, "/\\", "/");
	ReplaceString(path, "\\/", "/");
	ReplaceString(path, "//", "/");
}
vector<string> UTIL::SplitString(string str, string del)
{
	string temp;
	vector<string> res;
	while (temp != str)
	{
		temp = str.substr(0, str.find_first_of(del));
		str = str.substr(str.find_first_of(del) + 1);
		res.push_back(temp);
	}
	return res;
}