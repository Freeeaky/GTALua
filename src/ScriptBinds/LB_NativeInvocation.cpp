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
	luabind::module(lua->State())
	[
		luabind::class_<ScriptNativeCallContext>("CScriptNativeCallContext")
		.def("PushArgument", &ScriptNativeCallContext::PushArgument<int>),

		luabind::class_<InvokeNative, ScriptNativeCallContext>("CInvokeNative")
		.def(luabind::constructor<Natives::NativeReg*>())
		.def("Call", &InvokeNative::Call)
	];
}