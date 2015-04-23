// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds.h"

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
		.def("GetResultNumber", &ScriptNativeCallContext::GetResult<int>)
		.def("GetResultFloat", &ScriptNativeCallContext::GetResult<float>),

		luabind::class_<InvokeNative, ScriptNativeCallContext>("CInvokeNative")
		.def(luabind::constructor<Natives::NativeReg*>())
		.def("Call", &InvokeNative::Call)
	];

	// Rage
	luabind::module(lua->State())
	[
		luabind::class_<rage::CVector>("Vector")
		.def_readwrite("x", &rage::CVector::x)
		.def_readwrite("y", &rage::CVector::y)
		.def_readwrite("z", &rage::CVector::z)
	];
}