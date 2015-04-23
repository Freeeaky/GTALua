// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds.h"

// =================================================================================
// Vector: Lua Binds
// =================================================================================
struct Lua_Vector : rage::CVector
{
	string __tostring() {
		char buf[256];
		sprintf(buf, "[Vector %f %f %f]", x, y, z);
		return string(buf);
	}
	string __type() {
		return "Vector";
	}
};

// =================================================================================
// Bind
// =================================================================================
void ScriptBinds::NativeInvocation::Bind()
{
	// Invoke Native
	luabind::module(lua->State())
	[
		luabind::class_<ScriptNativeCallContext>("CScriptNativeCallContext")
		.def("PushNumber", &ScriptNativeCallContext::PushArgument<int>)
		.def("PushFloat", &ScriptNativeCallContext::PushArgument<float>)
		.def("PushVector", &ScriptNativeCallContext::PushArgument<rage::CVector>)
		.def("GetResultNumber", &ScriptNativeCallContext::GetResult<int>)
		.def("GetResultFloat", &ScriptNativeCallContext::GetResult<float>)
		.def("GetResultVector", &ScriptNativeCallContext::GetResult<rage::CVector>),

		luabind::class_<InvokeNative, ScriptNativeCallContext>("CInvokeNative")
		.def(luabind::constructor<Natives::NativeReg*>())
		.def("Call", &InvokeNative::Call)
	];

	// Rage
	luabind::module(lua->State())
	[
		luabind::class_<Lua_Vector>("CLuaVectorBinds")
		.def("__tostring", &Lua_Vector::__tostring)
		.def("__type", &Lua_Vector::__type),

		luabind::class_<rage::CVector, Lua_Vector>("Vector")
		.def_readwrite("x", &rage::CVector::x)
		.def_readwrite("y", &rage::CVector::y)
		.def_readwrite("z", &rage::CVector::z)
	];
}