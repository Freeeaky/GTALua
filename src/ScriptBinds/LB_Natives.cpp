// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds.h"
using namespace Natives;

// =================================================================================
// Additional Functions 
// =================================================================================
struct NativeReg_AdditionalFunctions : NativeReg
{
	string __tostring() {
		return "CNativeReg";
	}
	string __type() {
		return "CNativeReg";
	}
};

// =================================================================================
// Bind 
// =================================================================================
void ScriptBinds::NativesWrapper::Bind()
{
	// Register NativeReg struct
	luabind::module(lua->State())
	[
		luabind::class_<NativeReg>("CNativeReg_AdditionalFunctions")
		.def_readonly("m_sName", &NativeReg::sName)
		.def_readonly("m_bValid", &NativeReg::bValid)
		.def_readwrite("m_bHasCallLayout", &NativeReg::bHasCallLayout)
		.def_readwrite("m_sCallLayout", &NativeReg::sCallLayout),

		luabind::class_<NativeReg_AdditionalFunctions, NativeReg>("CNativeReg")
		.def("__tostring", &NativeReg_AdditionalFunctions::__tostring)
		.def("__type", &NativeReg_AdditionalFunctions::__type)
	];

	// native table
	luabind::globals(lua->State())["natives"] = luabind::newtable(lua->State());

	// Loop category
	for (int i = 0; i < _NATIVE_ENUM_SIZE; i++)
	{
		const char* sCategoryName = CategoryNames[i];
		luabind::globals(lua->State())["natives"][sCategoryName] = luabind::newtable(lua->State());

		// Iterate natives
		for (vector<NativeReg*>::iterator it = Registered[i].begin(); it != Registered[i].end(); ++it)
		{
			// register natives.category.name = NativeReg
			NativeReg_AdditionalFunctions* reg = (NativeReg_AdditionalFunctions*)*it;
			luabind::object obj(lua->State(), reg);
			luabind::globals(lua->State())["natives"][sCategoryName][reg->sName] = obj;
		}
	}
}