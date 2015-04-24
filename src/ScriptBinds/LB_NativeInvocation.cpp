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
using namespace rage;
void ScriptBinds::NativeInvocation::Bind()
{
	// Rage
	// rage::CVector
	luabind::module(lua->State())
	[
		luabind::class_<CVector>("Vector")
		.def(luabind::constructor<float, float, float>())
		.def(luabind::constructor<>())
		.def_readwrite("x", &CVector::x)
		.def_readwrite("y", &CVector::y)
		.def_readwrite("z", &CVector::z)
		.def("__tostring", &LuaVectorWrapper::__tostring)
		.def("__type", &LuaVectorWrapper::__type)
	];

	// Invoke Native
	luabind::module(lua->State())
	[
		luabind::class_<ScriptNativeCallContext>("CScriptNativeCallContext")
		.def("PushNumber", &ScriptNativeCallContext::PushArgument<int>)
		.def("PushFloat", &ScriptNativeCallContext::PushArgument<float>)
		.def("PushVector", &ScriptNativeCallContext::PushVector)
		.def("PushBool", &ScriptNativeCallContext::PushArgument<bool>)
		.def("GetArgumentNumber", &ScriptNativeCallContext::GetArgument<int>)
		.def("GetArgumentFloat", &ScriptNativeCallContext::GetArgument<float>)
		.def("GetArgumentVector", &ScriptNativeCallContext::GetArgument<CVector>)
		.def("GetArgumentBool", &ScriptNativeCallContext::GetArgument<bool>)
		.def("GetResultNumber", &ScriptNativeCallContext::GetResult<int>)
		.def("GetResultFloat", &ScriptNativeCallContext::GetResult<float>)
		.def("GetResultVector", &ScriptNativeCallContext::GetResult<CVector>)
		.def("GetResultBool", &ScriptNativeCallContext::GetResult<bool>),

		luabind::class_<InvokeNative, ScriptNativeCallContext>("CInvokeNative")
		.def(luabind::constructor<Natives::NativeReg*>())
		.def("Call", &InvokeNative::Call)
	];
}