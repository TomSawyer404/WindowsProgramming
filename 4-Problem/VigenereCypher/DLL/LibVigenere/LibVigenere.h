/* LibVigenere.h
 * @Author:         MrBanana
 * @Date:           2020/12/20
 * @Note:
 *   Implementation of Vigenere Cypher
 **/

#pragma once
//#pragma comment(lib, "LibVigenere.lib")

#ifndef LIBVIG_H
#define LIBVIG_H

#ifdef BUILD_DLL
	#define LIBVIG_DLL extern "C" __declspec(dllexport)
#else
	#define LIBVIG_DLL extern "C" __declspec(dllimport)
#endif


#include <windows.h>

LIBVIG_DLL BOOL do_VigenereCrypt(
	char* dst, 
	char* src, 
	UINT keyNum, 
	char* key,
	DWORD fileSize
);

LIBVIG_DLL BOOL do_VigenereDecrypt(
	char* dst, 
	char* src, 
	UINT keyNum, 
	char* key, 
	DWORD fileSize
);

#endif