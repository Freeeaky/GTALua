// =================================================================================
// Includes
// =================================================================================
#include "ScriptEngine.h"
#include "ScriptThread.h"
#include "Natives.h"
#include "Console.h"

// =================================================================================
// Script Binds 
// =================================================================================
namespace ScriptBinds
{
	void BindBlockedFunctions();

	namespace GeneralFunctions
	{
		void Bind();
	}
}