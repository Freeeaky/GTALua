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
// Global 
// =================================================================================
std::vector<Natives::NativeReg*> Natives::Registered[Natives::_NATIVE_ENUM_SIZE + 1];

// =================================================================================
// Parser
// =================================================================================
int ini_natives_parser(void* pCustom, const char* sSection, const char* sName, const char* sValue)
{
	// find category
	UTIL::Lowercase(const_cast<char*>(sSection));
	Natives::eNativeCategory eCategory = Natives::NATIVE_UNKNOWN;
	for (int i = 0; i < Natives::_NATIVE_ENUM_SIZE; i++)
	{
		if (strcmp(sSection, Natives::CategoryNames[i]) == 0)
		{
			eCategory = (Natives::eNativeCategory) i;
			break;
		}
	}

	// check
	if (eCategory == Natives::NATIVE_UNKNOWN)
	{
		printf("[natives.ini] Unknown category %s\n", sSection);
		return 1;
	}

	// add to registered natives
	Natives::NativeReg* reg = new Natives::NativeReg();
	reg->bValid = true;
	reg->hHash = _strtoui64(sValue, NULL, 0);
	reg->sName = _strdup(sName);

	// register
	Natives::Registered[eCategory].push_back(reg);
	return 1;
}

// =================================================================================
// Load 
// =================================================================================
void GTALua::LoadNativesINI()
{
	// Load natives ini
	IniFile file("GTALua/natives.ini", ini_natives_parser, NULL);
}