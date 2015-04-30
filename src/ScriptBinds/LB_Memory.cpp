// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds.h"
#include "thirdparty/ScriptHookV/ScriptHookV.h"

DWORD d;

using namespace ScriptBinds::Memory;

// =================================================================================
// Memory 
// =================================================================================
MemoryBlock::MemoryBlock(int iSize)
{
	m_iSize = iSize;
	m_pMemory = (int*)malloc(iSize);
	memset(m_pMemory, 0, iSize);
	printf("MemoryBlock::MemoryBlock\n");
}
MemoryBlock::~MemoryBlock()
{
	if (m_iSize > 0 && m_pMemory != NULL)
	{
		delete m_pMemory;
		m_pMemory = NULL;
	}
	m_iSize = 0;
	printf("MemoryBlock::~MemoryBlock\n");
}
void MemoryBlock::Release()
{
	delete this;
}

// =================================================================================
// Bind
// =================================================================================
void ScriptBinds::Memory::Bind()
{
	luabind::module(lua->State())
	[
		luabind::class_<MemoryBlock>("CMemoryBlock")
		.def(luabind::constructor<int>())
		.def("Release", &MemoryBlock::Release)
		.def("WriteInt64", &MemoryBlock::Write<int>)
		.def("WriteInt32", &MemoryBlock::Write<__int32>)
		.def("WriteFloat", &MemoryBlock::Write<int>)
		.def("WriteDWORD32", &MemoryBlock::Write<DWORD>)
		.def("ReadInt64", &MemoryBlock::Read<int>)
		.def("ReadInt32", &MemoryBlock::Read<__int32>)
		.def("ReadFloat", &MemoryBlock::Read<float>)
		.def("ReadDWORD32", &MemoryBlock::Read<DWORD>)
	];
}