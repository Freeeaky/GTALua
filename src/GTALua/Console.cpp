// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "Memory/Memory.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds/ScriptBinds.h"
#include "UTIL/UTIL.h"

// =================================================================================
// Process 
// =================================================================================
void GTALua::ProcessConsoleInput()
{
	// Input
	string input_line;
	getline(cin, input_line);

	// Pre-Lua?
	if (lua == NULL)
	{
		printf("Please wait until Lua has initialized!\n");
		return;
	}

	// Split spaces
	vector<string> args = UTIL::SplitString(input_line, " ");
	if (args.size() == 0) return;
	string cmd = args.at(0);
	args.erase(args.begin());

	// Lock
	lua->Lock();

	// Lua: args table
	luabind::object l_args = luabind::newtable(lua->State());
	int l_index = 1;
	for (vector<string>::iterator it = args.begin(); it != args.end(); ++it)
	{
		string arg = *it;
		l_args[l_index] = arg;
		l_index++;
	}

	bool bSuccess = true;
	try
	{
		luabind::object event_callback = luabind::globals(lua->State())["event"]["Call"];
		luabind::call_function<bool>(event_callback, "OnConsoleInput", cmd, l_args);
	} catch(...) {
		bSuccess = false;
	}

	// Unlock
	lua->Unlock();

	// Lua: result-check
	if (!bSuccess)
	{
		printf("Unknown console command: %s\n", cmd);
		return;
	}
}