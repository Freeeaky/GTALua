// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"
#include "../Lua.h"
#include <sstream>
#include <vector>

using namespace std;

// ====================================================================================================
// Utility Functions
// ====================================================================================================
vector<string>& StringExplode(const string &s, char* delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	char tmp = *delim;
	while (getline(ss, item, tmp)) {
		elems.push_back(item);
	}
	return elems;
}
vector<char*> StringExplode(char *s, char *delim)
{
	return vector<char*>();
}

// ====================================================================================================
// General
// ====================================================================================================
lua_Debug LuaManager::GetDebugInformation()
{
	lua_Debug rv;
	lua_getstack(State(), 1, &rv);
	return rv;
}

// ====================================================================================================
// File Operations
// ====================================================================================================
char* LuaManager::DebugGetFilename()
{
	lua_State* L = State();

	lua_Debug ar1;
	lua_getstack(L, 1, &ar1);
	lua_getinfo(L, "f", &ar1);
	lua_Debug ar2;
	lua_getinfo(L, ">S", &ar2);
	char* filename = const_cast<char*>(ar2.source);

	return filename;
}
char* LuaManager::DebugGetPath()
{
	string filename(DebugGetFilename());
	vector<string> exp1;
	StringExplode(filename, "@", exp1);

	if (exp1.size() != 2) { return "?"; }

	string fullpath(exp1.at(1));
	vector<string> exp2;
	StringExplode(fullpath, "/", exp2);

	if (exp2.size() <= 1) { return ""; }

	char path[364];
	sprintf(path, "");

	int iIndex = 1;
	for (vector<string>::iterator it = exp2.begin(); it != exp2.end(); ++it)
	{
		string item = *it;
		if (iIndex < exp2.size())
		{
			char deli[12];
			sprintf(deli, "/");
			if (strcmp(path, "") == 0) sprintf(deli, "");
			sprintf(path, "%s%s%s", path, deli, item.c_str());
		}

		iIndex++;
	}

	sprintf(path, "%s/", path);
	return path;
}

// ====================================================================================================
// Dump Stack
// ====================================================================================================
void LuaManager::DumpStack() {
	int index = lua_gettop(m_pState);
	while (index > 0) {
		int ltype = lua_type(m_pState, index);
		printf("%i: ", index);
		switch (ltype) {
			case LUA_TSTRING:
				printf("%s", index, lua_tostring(m_pState, index));
			break;
			case LUA_TBOOLEAN:
				printf("%s", index, lua_toboolean(m_pState, index) ? "true" : "false");
			break;
			case LUA_TNUMBER:
				printf("%g", index, lua_tonumber(m_pState, index));
			break;
			default:
				printf("%s", index, lua_typename(m_pState, ltype));
			break;
		}
		printf("\n");
		index--;
	}
}
