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
	m_pArguments = (int*)malloc(16 * 8);
	memset(m_pArguments, 0, 16 * 8);
	m_pReturnValues = (int*)malloc(8 * 8);
	memset(m_pReturnValues, 0, 8 * 8);
	m_hHash = reg->hHash;
}
InvokeNative::InvokeNative(DWORD64 hHash)
{
	m_iArgCount = 0;
	m_pArguments = (int*)malloc(16 * 8);
	memset(m_pArguments, 0, 16 * 8);
	m_pReturnValues = (int*)malloc(8 * 8);
	memset(m_pReturnValues, 0, 8 * 8);
	m_hHash = hHash;
}
InvokeNative::~InvokeNative()
{
	delete m_pArguments;
	delete m_pReturnValues;
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
		// TODO: Change this shitty code
		// Alloc
		int** pCallContext = (int**) malloc(24);
		pCallContext[0] = (int*)malloc(8 * 8);
		pCallContext[2] = (int*)malloc(16 * 8);

		// Copy arguments / return values
		memcpy(&pCallContext[0][0], m_pReturnValues, 8 * 8);
		memcpy(&pCallContext[2][0], m_pArguments, 16 * 8);

		// Call native
		pNative(pCallContext);

		// copy return values back
		memcpy(m_pReturnValues, &pCallContext[0][0], 8 * 8);

		// Cleanup
		delete[] pCallContext;
		return true;
	}

	// Native not found!
	return false;
}