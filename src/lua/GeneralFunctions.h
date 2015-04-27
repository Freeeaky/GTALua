// ====================================================================================================
// Lua: General Functions
// ====================================================================================================
// Forward Declaration for SimpleFileWatcher
namespace FW
{
	class FileWatcher;
};

// Lua Functions
namespace LuaFunctions
{
	void RegisterLuaFunctions();

	void include(std::string file);
	void sleep(unsigned long ms);

	namespace Autorefresh
	{
		class UpdateListener;
		extern vector<string> vRegisteredDirectories;
		extern FW::FileWatcher* pFileWatcher;
		extern UpdateListener* pListener;

		// Functions
		void Update();
		void Init();
		bool IsInitialized();
		void Destroy();

		void AddDirectory(string path);
	}
}