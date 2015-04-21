// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "Memory/Memory.h"

// =================================================================================
// Init 
// =================================================================================
GTALua::GTALua()
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
	printf("Console allocated and attached!\n");

	// Prepare Game Memory
	GameMemory::Init();
}