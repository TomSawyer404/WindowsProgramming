/* LibCaser.h
 * @Author:     MrBanana
 * @Date:       2020/12/19
 * @Note:
 *    A implementation of Caser Crypher
 */

#pragma once
//#pragma comment(lib, "LibCaser.lib")

#ifndef LIB_CASER
#define LIB_CASER

#ifdef BUILD_DLL
    #define EXPORT extern "C" __declspec(dllexport)
#else
    #define EXPORT extern "C" __declspec(dllimport)
#endif

#include <windows.h>
#include <wchar.h>

EXPORT BOOL do_CaserCrypt(
    char* pOutFile, 
    char* pInFile, 
    UINT m_uiKey, 
    DWORD fileSize
);

EXPORT BOOL do_CaserDecrypt(
    char* pOutFile, 
    char* pInFile, 
    UINT m_uiKey, 
    DWORD fileSize
);

#endif