// ====================================================================================================
// Includes
// ====================================================================================================
#include "../Includes.h"
#include "Lua.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"
#include "UTIL/UTIL.h"

// ====================================================================================================
// include
// ====================================================================================================
void LuaFunctions::include(std::string file)
{
	char* currentpath = lua->DebugGetPath();
	luaL_checkstring(lua->State(), 1);

	char path[364];
	sprintf(path, "%s%s", currentpath, file.c_str());
	std::string filepath(path);
	UTIL::ParseFilePath(filepath);

	char* sPath = const_cast<char*>(filepath.c_str());
	lua->IncludeFile(sPath);

	if (!lua->IsOnFileList(sPath))
		lua->AddToFileList(sPath);

	// AutoRefresh will be added later :)
	//LuaFunctions::Autorefresh::AddDirectory(filepath);
}

// ====================================================================================================
// Register Functions
// ====================================================================================================
void LuaFunctions::RegisterLuaFunctions() 
{
	// General
	luabind::module(lua->State()) [
		luabind::def("include", &LuaFunctions::include)
	];
}