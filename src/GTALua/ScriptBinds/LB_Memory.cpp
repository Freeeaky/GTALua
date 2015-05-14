// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds.h"
#include "thirdparty/ScriptHookV/ScriptHookV.h"

using namespace ScriptBinds::Memory;

// =================================================================================
// Memory 
// =================================================================================
MemoryBlock::MemoryBlock(int iSize)
{
	m_iSize = iSize;
	m_pMemory = (int*)malloc(iSize);
	if (m_pMemory != NULL)
		memset(m_pMemory, 0, iSize);
}
MemoryBlock::~MemoryBlock()
{
	Release();
}
void MemoryBlock::Release()
{
	if (m_iSize > 0 && m_pMemory != NULL)
	{
		delete m_pMemory;
		m_pMemory = NULL;
	}
	m_iSize = 0;
}

// =================================================================================
// Valid-Check 
// =================================================================================
bool MemoryBlock::IsValid()
{
	return m_iSize > 0 && m_pMemory != NULL;
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
		.def("IsValid", &MemoryBlock::IsValid)
		.def("WriteInt64", &MemoryBlock::Write<int>)
		.def("WriteInt32", &MemoryBlock::Write<__int32>)
		.def("WriteFloat", &MemoryBlock::Write<float>)
		.def("WriteDWORD32", &MemoryBlock::Write<DWORD>)
		.def("ReadInt64", &MemoryBlock::Read<int>)
		.def("ReadInt32", &MemoryBlock::Read<__int32>)
		.def("ReadFloat", &MemoryBlock::Read<float>)
		.def("ReadDWORD32", &MemoryBlock::Read<DWORD>)
	];
}