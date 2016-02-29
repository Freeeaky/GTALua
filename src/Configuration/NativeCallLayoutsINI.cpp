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
// Includes 
// =================================================================================
int ini_native_call_layouts_parser(void* pCustom, const char* sSection, const char* sName, const char* sValue)
{
	// find category
	Natives::eNativeCategory eCategory = Natives::FindCategoryByName(const_cast<char*>(sSection));

	// check
	if (eCategory == Natives::NATIVE_UNKNOWN)
	{
		printf("[native_call_layout.ini] Unknown category %s\n", sSection);
		return 1;
	}

	// find registered native
	for (vector<Natives::NativeReg*>::iterator it = Natives::Registered[eCategory].begin(); it != Natives::Registered[eCategory].end(); ++it)
	{
		Natives::NativeReg* reg = *it;
		if (strcmp(reg->sName, sName) == 0)
		{
			reg->bHasCallLayout = true;
			reg->sCallLayout = _strdup(sValue);
			return 1;
		}
	}

	// failed
	printf("[native_call_layout.ini] Native %s/%s is not defined in natives.ini\n", sSection, sName);
	return 0;
}

// =================================================================================
// Load 
// =================================================================================
void GTALua::LoadCallLayoutsINI()
{
	// Load natives ini
	IniFile file("GTALua/native_call_layout.ini", ini_native_call_layouts_parser, NULL);
}