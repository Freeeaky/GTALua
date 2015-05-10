// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptBinds.h"

// =================================================================================
// Find Files
// =================================================================================
void LB_FindFiles(const char* sPath)
{
	// Block inside of threads
	if (strcmp(lua_typename(lua->State(), lua_type(lua->State(), 1)), "thread") == 0)
	{
		luaL_error(lua->State(), "file.FindFiles cannot be run inside of a thread");
		return;
	}

	// Handles
	HANDLE hDirectoryHandle;
	WIN32_FIND_DATA hFindData;

	if ((hDirectoryHandle = FindFirstFile(sPath, &hFindData)) == INVALID_HANDLE_VALUE)
	{
		lua->PushBool(false);
		return;
	}
	
	// Lua Table
	luabind::object file_table = luabind::newtable(lua->State());
	luabind::object dir_table = luabind::newtable(lua->State());
	int file_index = 1;
	int dir_index = 1;

	// Loop
	do
	{
		char* name = hFindData.cFileName;

		// ignore
		if (name[0] == '.')
			continue;

		// directory
		if ((hFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != NULL)
		{
			// push directory
			dir_table[dir_index] = string(name);
			dir_index++;
			continue;
		}

		// push file
		file_table[file_index] = string(name);
		file_index++;
	} while (FindNextFile(hDirectoryHandle, &hFindData));

	// Cleanup
	FindClose(hDirectoryHandle);

	// Success
	lua->PushBool(true);
	dir_table.push(lua->State());
	file_table.push(lua->State());
}

// =================================================================================
// Includes 
// =================================================================================
void ScriptBinds::FileModule::Bind()
{
	luabind::module(lua->State(), "file")
	[
		luabind::def("FindFiles", LB_FindFiles)
	];
}