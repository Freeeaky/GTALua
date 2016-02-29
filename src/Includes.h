// =================================================================================
// Remove Warnings 
// =================================================================================
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4244)
#pragma warning(disable: 4251) // luabind related

// =================================================================================
// Windows Includes 
// =================================================================================
#include <Windows.h>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

// =================================================================================
// Libraries 
// =================================================================================
#pragma comment(lib, "version.lib") // GameMemory Version Fetch
#pragma comment(lib, "shlwapi.lib") // AutoRefresh

// =================================================================================
// Configuration 
// =================================================================================
// Allow building as exe
// This prevents memory operations so the exe doesnt crash
// Used for testing lua related things
//#define GTA_LUA_TEST_EXE