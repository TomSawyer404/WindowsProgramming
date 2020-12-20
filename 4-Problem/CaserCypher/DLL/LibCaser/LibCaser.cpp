/* LibCaser.cpp
 * @Author:     MrBanana
 * @Date:       2020/12/19
 * @Note:
 *    DLL implementation.
 */

#define BUILD_DLL

#include "LibCaser.h"

EXPORT BOOL do_CaserCrypt(
    char* pOutFile, 
    char* pInFile, 
    UINT m_uiKey, 
    DWORD fileSize) 
{
    CHAR *pIn = 0x0, *pOut = 0x0;
    __try {
        pIn = pInFile;
        pOut = pOutFile;
        while (pIn < pInFile + fileSize) {
            // ignore newline and tab
            if (*pIn == '\r' || *pIn == '\n' || *pIn == '\t') { 
                *pOut = *pIn;
                pIn++;
                pOut++;
            } else {
                *pOut = (*pIn + m_uiKey) % 256;
                pIn++;
                pOut++;
            }
        }
    }
    __except (
        GetExceptionCode() == EXCEPTION_IN_PAGE_ERROR ? 
        EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) 
    {
        WCHAR errNum[4] = {0x0};
        wsprintf(errNum, L"%d", ::GetLastError());
        ::MessageBoxW(NULL, L"加密过程出现错误", L"errNum", MB_OK);
        return FALSE;
    }
    return TRUE;
}

EXPORT BOOL do_CaserDecrypt(
    char* pOutFile, 
    char* pInFile, 
    UINT m_uiKey, 
    DWORD fileSize) 
{
    CHAR *pIn = 0x0, *pOut = 0x0;
    __try {
        pIn = pInFile;
        pOut = pOutFile;
        while (pIn < pInFile + fileSize) {
            // ignore newline and tab
            if (*pIn == '\r' || *pIn == '\n' || *pIn == '\t') { 
                *pOut = *pIn;
                pIn++;
                pOut++;
            } else {
                *pOut = (*pIn - m_uiKey) % 256;
                pIn++;
                pOut++;
            }
        }
    }
    __except (
        GetExceptionCode() == EXCEPTION_IN_PAGE_ERROR ? 
        EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) 
    {
        WCHAR errNum[4] = {0x0};
        wsprintf(errNum, L"%d", ::GetLastError());
        ::MessageBoxW(NULL, L"加密过程出现错误", L"errNum", MB_OK);
        return FALSE;
    }
    return TRUE;
}
