// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"
#include "../Lua.h"

// ====================================================================================================
// Get*
// ====================================================================================================
void   LuaManager::GetGlobal(char* sName) { lua_getglobal(m_pState, sName); }
void   LuaManager::GetEvent(char* sName) { GetGlobal("event"); GetField("Call"); PushString(sName); }
char*  LuaManager::GetString(int iStackIndex) { return const_cast<char*>(lua_tostring(m_pState, iStackIndex)); }
double LuaManager::GetNumber(int iStackIndex) { return lua_tonumber(m_pState, iStackIndex); }
bool   LuaManager::GetBool(int iStackIndex) { return lua_toboolean(m_pState, iStackIndex); }
void   LuaManager::GetTypeName(int iStackIndex) { luaL_typename(m_pState, iStackIndex); }

// ====================================================================================================
// Is*
// ====================================================================================================
bool LuaManager::IsNil(int iStackIndex) { return lua_isnil(m_pState, iStackIndex); }
bool LuaManager::IsString(int iStackIndex) { return lua_isstring(m_pState, iStackIndex); }
bool LuaManager::IsNumber(int iStackIndex) { return lua_isnumber(m_pState, iStackIndex); }
bool LuaManager::IsBool(int iStackIndex) { return lua_isboolean(m_pState, iStackIndex); }
bool LuaManager::IsTable(int iStackIndex) { return lua_istable(m_pState, iStackIndex); }
bool LuaManager::IsUserData(int iStackIndex) { return lua_isuserdata(m_pState, iStackIndex); }

// ====================================================================================================
// Push*
// ====================================================================================================
void LuaManager::PushString(char* sString) { lua_pushstring(m_pState, sString); }
void LuaManager::PushNil() { lua_pushnil(m_pState); }
void LuaManager::PushNumber(double iNumber) { lua_pushnumber(m_pState, iNumber); }
void LuaManager::PushBool(bool bBool) { lua_pushboolean(m_pState, bBool); }
void LuaManager::PushValue(int iStackIndex) { lua_pushvalue(m_pState, iStackIndex); }

// ====================================================================================================
// Table
// ====================================================================================================
bool LuaManager::GetField(char *sKey, int iStackIndex)
{
	lua_getfield(m_pState, iStackIndex, sKey);
	return !IsNil();
}
void LuaManager::SetField(char *sKey, int iStackIndex) { lua_setfield(m_pState, iStackIndex, sKey); }

// ====================================================================================================
// Stack Operations
// ====================================================================================================
int  LuaManager::Top() { return lua_gettop(m_pState); }
void LuaManager::SetTop(int iStackIndex) { lua_settop(m_pState, iStackIndex); }
void LuaManager::Pop(int iStackIndex) { lua_pop(m_pState, iStackIndex); }
void LuaManager::Remove(int iStackIndex) { lua_remove(m_pState, iStackIndex); }