/* libFileMapping.cpp
 * @Author:     MrBanana
 * @Date:       2020/12/18
 * @Note:
 *    DLL implementation.
 */

#define BUILD_DLL

#include "LibFileMapping.h"
#include <stdio.h>

static HANDLE hFile = INVALID_HANDLE_VALUE;
static HANDLE hFileMap = INVALID_HANDLE_VALUE;
static CHAR* ret = nullptr;



EXPORT CHAR* FileMapping(WCHAR* szFilePath, int flag, DWORD* fileSize) {
	/* Create a file */
    if (flag) {      // File already exists
        hFile = ::CreateFileW(
            szFilePath,
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );
    }
    else {        // File doesn't exist, we create a new one
        hFile = ::CreateFileW(
            szFilePath,
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );
    }
    if (INVALID_HANDLE_VALUE == hFile) {
        ::MessageBoxW(NULL, L"打开文件失败", L"文件创建过程", MB_OK);  // 链接时无法解析外部符号
        //fprintf(stderr, "%ld, 打开文件失败\n", ::GetLastError());
        return nullptr;
    }

    /* Compute file size */
    if (flag == 0x1 && *fileSize == 0) {  // Read mode, we don't know file size yet
        *fileSize = ::GetFileSize(hFile, 0);
        if (INVALID_FILE_SIZE == *fileSize) {
            ::MessageBoxW(NULL, L"获取文件大小失败!", L"文件创建过程", MB_OK);
            return nullptr;
        }
    }

    /* Create a file mapping */
    if (flag) {
        hFileMap = ::CreateFileMappingW(
            hFile,
            NULL,
            PAGE_READWRITE,
            0,
            0,
            L"hInMap"
        );
    }
    else {
        hFileMap = ::CreateFileMappingW(
            hFile,
            NULL,
            PAGE_READWRITE,
            0,
            *fileSize,
            L"hOutMap"
        );
    }
    if (nullptr == hFileMap) {
        ::MessageBoxW(NULL, L"创建文件映射失败", L"文件映射过程", MB_OK);
        //fprintf(stderr, "%ld, 创建文件映射失败!\n", ::GetLastError());
        return nullptr;
    }

    /* Get the veiw of mapping area */
    if (flag) {
        ret = (CHAR*)::MapViewOfFile(
            hFileMap,
            FILE_MAP_ALL_ACCESS,
            0x0,
            0x0,
            0x0
        );
    }
    else {
        ret = (CHAR*)::MapViewOfFile(
            hFileMap,
            FILE_MAP_ALL_ACCESS,
            0x0,
            0x0,
            *fileSize
        );
    }
    if (nullptr == ret) {
        ::MessageBoxW(NULL, L"获取映射视图失败", L"获取映射视图", MB_OK);
        //fprintf(stderr, "%ld, 获取映射视图失败\n", ::GetLastError());
        return nullptr;
    }

    /* Close handle */
    ::CloseHandle(hFile);
    ::CloseHandle(hFileMap);
    return ret;
}
