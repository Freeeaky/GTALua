// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "ScriptEngine.h"
#include "Memory/Memory.h"
#include "UTIL/UTIL.h"

// =================================================================================
// Category By Name 
// =================================================================================
Natives::eNativeCategory Natives::FindCategoryByName(char* sName)
{
	// find category
	UTIL::Lowercase(const_cast<char*>(sName));
	eNativeCategory eCategory = NATIVE_UNKNOWN;
	for (int i = 0; i < _NATIVE_ENUM_SIZE; i++)
	{
		if (strcmp(sName, CategoryNames[i]) == 0)
		{
			return (eNativeCategory)i;
		}
	}

	// unknown
	return NATIVE_UNKNOWN;
}