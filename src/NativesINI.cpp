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
	Natives::eNativeCategory eCategory = Natives::FindCategoryByName(const_cast<char*>(sSection));

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
	reg->sCategory = Natives::CategoryNames[eCategory]; // as they are static no need to copy anything
	reg->bHasCallLayout = false;
	reg->sCallLayout = NULL;

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