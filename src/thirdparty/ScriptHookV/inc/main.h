/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com			
			(C) Alexander Blade 2015
*/

#pragma once

#include <windows.h>
#ifndef GTA_LUA_TEST_EXE
#pragma comment(lib, "src/thirdparty/ScriptHookV/lib/ScriptHookV.lib")
#define IMPORT __declspec(dllimport)
#else
#define IMPORT
#endif

//namespace ScriptHook
//{

	IMPORT void scriptWait(DWORD time);
	IMPORT void scriptRegister(HMODULE module, void(*LP_SCRIPT_MAIN)());
	IMPORT void scriptUnregister(void(*LP_SCRIPT_MAIN)());

	typedef void(*KeyboardHandler)(DWORD, WORD, BYTE, BOOL, BOOL, BOOL, BOOL);

	IMPORT void keyboardHandlerRegister(KeyboardHandler handler);
	IMPORT void keyboardHandlerUnregister(KeyboardHandler handler);

	IMPORT void nativeInit(UINT64 hash);
	IMPORT void nativePush64(UINT64 val);
	IMPORT PUINT64 nativeCall();

	//static void WAIT(DWORD time) { scriptWait(time); }
	//static void TERMINATE() { WAIT(MAXDWORD); }
//}