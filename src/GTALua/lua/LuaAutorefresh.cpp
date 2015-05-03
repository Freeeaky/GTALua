// =================================================================================
// Includes 
// =================================================================================
#include "../Includes.h"
#include "Lua.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"
#include "thirdparty/SimpleFileWatcher/include/FileWatcher.h"
#include "Shlwapi.h"
#include "UTIL/UTIL.h"

// =================================================================================
// Globals 
// =================================================================================
using namespace LuaFunctions;
FW::FileWatcher* Autorefresh::pFileWatcher = NULL;
Autorefresh::UpdateListener* Autorefresh::pListener = NULL;
vector<string> Autorefresh::vRegisteredDirectories;

// =================================================================================
// Update Listener 
// =================================================================================
class Autorefresh::UpdateListener : public FW::FileWatchListener
{
public:
	UpdateListener()
	{
	}

	void handleFileAction(FW::WatchID watchid, const string& dir, const string& filename, FW::Action action)
	{
		char fullpath_c[712];
		sprintf(fullpath_c, "%s/%s", dir.c_str(), filename.c_str());
		std::string fullpath(fullpath_c);
		UTIL::ParseFilePath(fullpath);

		if (action == FW::Actions::Modified)
		{
			char* path = const_cast<char*>(fullpath.c_str());

			if (lua->IsOnFileList(path) && m_sLastFile != path)
			{
				lua->IncludeFile(path);
				m_sLastFile = path;
			}
		}
	}

	string m_sLastFile;
};

// =================================================================================
// Init 
// =================================================================================
void Autorefresh::Init()
{
	pFileWatcher = new FW::FileWatcher();
	pListener = new UpdateListener(); 
}
bool Autorefresh::IsInitialized()
{
	return pFileWatcher != NULL &&
		pListener != NULL;
}

// =================================================================================
// Update 
// =================================================================================
void Autorefresh::Update()
{
	if (IsInitialized())
	{
		pListener->m_sLastFile = string("");
		pFileWatcher->update();
	}
	else
		printf("[Lua] LuaFunctions::Autorefresh::Update called too early!\n");
}

// =================================================================================
// Add Directory 
// =================================================================================
void Autorefresh::AddDirectory(string path)
{
	// Check if already registered
	UTIL::ParseFilePath(path);
	string fn = UTIL::SplitFilename(path);
	for (vector<string>::iterator it = vRegisteredDirectories.begin(); it != vRegisteredDirectories.end(); ++it)
	{
		if (*it == fn)
			return;
	}

	// Add
	vRegisteredDirectories.push_back(fn);
	pFileWatcher->addWatch(fn, pListener);
}

// =================================================================================
// Destroy 
// =================================================================================
void Autorefresh::Destroy()
{
	delete pFileWatcher;
	pFileWatcher = NULL;
}