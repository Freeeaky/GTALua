// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds.h"

// =================================================================================
// Additional Functions 
// =================================================================================
struct NativeReg_AdditionalFunctions : Natives::NativeReg
{
	static char* _t;

	const char* __tostring() {
		return _t;
	}
	const char* __type() {
		return  _t;
	}
};
char* NativeReg_AdditionalFunctions::_t = "CNativeReg";

// =================================================================================
// Bind 
// =================================================================================
void ScriptBinds::NativesWrapper::Bind()
{
	// Register NativeReg struct
	luabind::module(lua->State())
	[
		/*luabind::class_<NativeReg_AdditionalFunctions>("CNativeReg_AdditionalFunctions")
		.def("__tostring", &NativeReg_AdditionalFunctions::__tostring)
		.def("__type", &NativeReg_AdditionalFunctions::__type),*/

		luabind::class_<Natives::NativeReg/*, NativeReg_AdditionalFunctions*/>("CNativeReg")
		.def_readonly("sName", &Natives::NativeReg::sName)
		.def_readonly("bValid", &Natives::NativeReg::bValid)
	];

	// native table
	luabind::globals(lua->State())["natives"] = luabind::newtable(lua->State());

	// Loop category
	for (int i = 0; i < Natives::_NATIVE_ENUM_SIZE; i++)
	{
		const char* sCategoryName = Natives::CategoryNames[i];
		luabind::globals(lua->State())["natives"][sCategoryName] = luabind::newtable(lua->State());

		// Iterate natives
		for (vector<Natives::NativeReg*>::iterator it = Natives::Registered[i].begin(); it != Natives::Registered[i].end(); ++it)
		{
			// register natives.category.name = NativeReg
			Natives::NativeReg* reg = *it;
			luabind::object obj(lua->State(), reg);
			luabind::globals(lua->State())["natives"][sCategoryName][reg->sName] = obj;
		}
	}
}