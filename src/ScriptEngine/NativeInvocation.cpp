// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "ScriptEngine.h"
#include "Memory/Memory.h"

// =================================================================================
// Invoke Native
// =================================================================================
InvokeNative::InvokeNative(Natives::NativeReg* reg)
{
	m_iArgCount = 0;
	m_pArguments = (int*)malloc(8 * 8);
	memset(m_pArguments, 0, 8 * 8);
	m_pReturnValues = NULL;
	m_hHash = reg->hHash;
}
InvokeNative::~InvokeNative()
{
	delete m_pArguments;
}

// =================================================================================
// Arguments 
// =================================================================================
bool InvokeNative::Call()
{
	// Find Address
	Native_t pNative = ScriptEngine::GetNativeAddress(m_hHash);

	// Call Native
	if (pNative)
	{
		// this is shitty, i know
		// TODO: be less stupid
		int** pCallContext = (int**) malloc(24);
		pCallContext[2] = (int*)malloc(8 * 8);
		memcpy(&pCallContext[2][0], m_pArguments, 8 * 8);
		pNative(pCallContext);
		delete[] pCallContext;

		return true;
	}

	// Native not found!
	return false;
}