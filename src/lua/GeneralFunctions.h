// ====================================================================================================
// Lua: General Functions
// ====================================================================================================
namespace LuaFunctions
{
	void RegisterLuaFunctions();

	void include(std::string file);
	void sleep(unsigned long ms);

	namespace Autorefresh
	{
		void Update();
		void Init();
		void Destroy();

		void AddDirectory(std::string path);
	}
}