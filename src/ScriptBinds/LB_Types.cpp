// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds.h"

// =================================================================================
// Vector 
// =================================================================================
struct LuaVectorWrapper : public rage::CVector
{
	static string __tostring(rage::CVector* pVec) {
		char buf[256];
		sprintf(buf, "[Vector %f %f %f]", pVec->x, pVec->y, pVec->z);
		return string(buf);
	}
	static string __type(rage::CVector* pVec) {
		return "Vector";
	}
};

// =================================================================================
// Bind
// =================================================================================
void ScriptBinds::Types::Bind()
{
	// Rage
	// rage::CVector
	luabind::module(lua->State())
	[
		luabind::class_<rage::CVector>("Vector")
		.def(luabind::constructor<float, float, float>())
		.def(luabind::constructor<>())
		.def_readwrite("x", &rage::CVector::x)
		.def_readwrite("y", &rage::CVector::y)
		.def_readwrite("z", &rage::CVector::z)
		.def("__tostring", &LuaVectorWrapper::__tostring)
		.def("__type", &LuaVectorWrapper::__type)
	];
}