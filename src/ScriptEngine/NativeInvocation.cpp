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
	printf("pre dtor\n");
	delete m_pArguments;
	delete m_pReturnValues;
	printf("post dtor\n");
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

		if (m_hHash == 0xAF35D0D2583051B0)
		{
			printf("changed hash\n");
			
			SetArgument<UINT>(0, 0xC703DB5F);
			SetArgument<float>(1, -13.34f);
			SetArgument<float>(2, -1456.75f);
			SetArgument<float>(3, 30.51f);
			SetArgument<float>(4, 0.0f);
			SetArgument<bool>(5, 1);
			SetArgument<bool>(6, 1);

			printf("0x%X %f %f %f %f %i %i\n", GetArgument<UINT>(0), GetArgument<float>(1), GetArgument<float>(2), GetArgument<float>(3), GetArgument<float>(4), GetArgument<int>(5), GetArgument<int>(6));
		}

		// Copy arguments / return values
		memcpy(&pCallContext[0][0], m_pReturnValues, 8 * 8);
		memcpy(&pCallContext[2][0], m_pArguments, 16 * 8);

		// Call native
		printf("precall\n");
		pNative(pCallContext);
		printf("postcall\n");

		// copy return values back
		memcpy(m_pReturnValues, &pCallContext[0][0], 8 * 8);

		// dump arguments
		if (m_hHash == 0xAF35D0D2583051B0)
		{
			printf("dump\n");
			printf("0x%X %f %f %f %f %i %i\n", GetArgument<UINT>(0), GetArgument<float>(1), GetArgument<float>(2), GetArgument<float>(3), GetArgument<float>(4), GetArgument<int>(5), GetArgument<int>(6));
		}

		// Cleanup
		printf("preclean\n");
		delete[] pCallContext;
		printf("postclean\n");
		return true;
	}

	// Native not found!
	return false;
}