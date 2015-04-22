// ====================================================================================================
// Includes
// ====================================================================================================
#include "../../Includes.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"
#include "FileWatcher/FileWatcher.h"
#include "Shlwapi.h"
#pragma comment(lib,"shlwapi.lib")

// ====================================================================================================
// Init Auto Refresh
// ====================================================================================================
namespace LuaFunctions
{
	namespace Autorefresh
	{
		class UpdateListener : public FW::FileWatchListener
		{
		public:
			UpdateListener()
			{
			}

			void handleFileAction(FW::WatchID watchid, const std::string& dir, const std::string& filename, FW::Action action)
			{
				char fullpath_c[712];
				sprintf(fullpath_c, "%s/%s", dir.c_str(), filename.c_str());
				std::string fullpath(fullpath_c);
				UTIL::ParseFilePath(fullpath);

				if (action == FW::Actions::Modified)
				{
					if (lua->IsOnFileList(const_cast<char*>(fullpath.c_str())))
					{
						printf("[Lua] Reloaded %s\n", fullpath.c_str());
						lua->IncludeFile(const_cast<char*>(fullpath.c_str()));
						//lua->Pop();
						m_sLastFile = fullpath;
					}
				}
			}

		private:
			std::string m_sLastFile;
		};

		UpdateListener* listener = NULL;
		FW::FileWatcher* fileWatcher = NULL;

		void Init()
		{
			fileWatcher = new FW::FileWatcher();
			listener = new UpdateListener();
			fileWatcher->addWatch("lua/", listener);
			Update();
		}
		void Update()
		{
			if (fileWatcher != NULL)
				fileWatcher->update();
			else
				printf("[Lua] LuaFunctions::Autorefresh::Update called too early!\n");
		}
		std::string SplitFilename(const std::string& str)
		{
			size_t found;
			found = str.find_last_of("/");
			return str.substr(0, found);
		}
		std::vector<std::string> vecRegisteredDirectories;
		void AddDirectory(std::string path)
		{
			UTIL::ParseFilePath(path);
			std::string fn = SplitFilename(path);
			for (std::vector<std::string>::iterator it = vecRegisteredDirectories.begin(); it != vecRegisteredDirectories.end(); ++it)
			{
				if (*it == fn)
					return;
			}

			vecRegisteredDirectories.push_back(fn);
			fileWatcher->addWatch(fn, listener);
		}
		void Destroy()
		{
			delete fileWatcher;
			fileWatcher = NULL;
		}
	}
}