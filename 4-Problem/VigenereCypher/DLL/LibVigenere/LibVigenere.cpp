/* LibVigenere.cpp
 * @Author:         MrBanana
 * @Date:           2020/12/20
 * @Note:
 *   Implementation of Vigenere Cypher
 **/

#pragma once

#define BUILD_DLL

#include "LibVigenere.h"

LIBVIG_DLL BOOL do_VigenereCrypt(
    char* pOutFile, 
    char* pInFile, 
    UINT keyNum, 
    char* key,
    DWORD fileSize
) 
{

    CHAR* pIn = 0x0, * pOut = 0x0;
    size_t keyCount = 0;
    __try {
        pIn = pInFile;
        pOut = pOutFile;
        while (pIn < pInFile + fileSize) {
            // ignore newline and tab
            if (*pIn == '\r' || *pIn == '\n' || *pIn == '\t') {
                *pOut = *pIn;
                pIn++; pOut++;
            }
            else {
                *pOut = (*pIn + key[ (keyCount++)%keyNum ]) % 256;
                pIn++; pOut++;
            }
        }
    }
    __except (
        GetExceptionCode() == EXCEPTION_IN_PAGE_ERROR ?
        EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH
    ) 
    {
        WCHAR errNum[4] = { 0x0 };
        wsprintf(errNum, L"%d", ::GetLastError());
        ::MessageBoxW(NULL, L"加密过程出现错误", L"errNum", MB_OK);
        return FALSE;
    }
    return TRUE;
}

LIBVIG_DLL BOOL do_VigenereDecrypt(
    char* pOutFile, 
    char* pInFile, 
    UINT keyNum, 
    char* key,
    DWORD fileSize 
)
{
	CHAR* pIn = 0x0, * pOut = 0x0;
    size_t keyCount = 0;
    __try {
        pIn = pInFile;
        pOut = pOutFile;
        while (pIn < pInFile + fileSize) {
            // ignore newline and tab
            if (*pIn == '\r' || *pIn == '\n' || *pIn == '\t') {
                *pOut = *pIn;
                pIn++; pOut++;
            }
            else {
                *pOut = (*pIn - key[ (keyCount++)%keyNum ]) % 256;
                pIn++; pOut++;
            }
        }
    }
    __except (
        GetExceptionCode() == EXCEPTION_IN_PAGE_ERROR ?
        EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH
    ) 
    {
        WCHAR errNum[4] = { 0x0 };
        wsprintf(errNum, L"%d", ::GetLastError());
        ::MessageBoxW(NULL, L"解密过程出现错误", L"errNum", MB_OK);
        return FALSE;
    }
    return TRUE;
}

