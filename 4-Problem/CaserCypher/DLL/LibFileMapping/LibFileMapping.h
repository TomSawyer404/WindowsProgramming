/* libFileMapping.h
 * @Author:     MrBanana
 * @Date:       2020/12/18
 * @Note:
 *    Head file for dll using file
 *    mappning.
 */

#pragma once
//#pragma comment(lib, "LibFileMapping.lib")

#ifndef LIB_FILEMAPPING
#define LIB_FILEMAPPING

#ifdef BUILD_DLL
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT extern "C" __declspec(dllimport)
#endif


#include <windows.h>
#include <wchar.h>

 /* CHAR* FileMapping(WCHAR* szFilePath)
  * @Note:
  *   1.Given a path in wchar, we creat a
  *     file mapping for it;
  *   2.If flag == 1, we assume the file already exists;
  *     otherwise the file need to be created.
  *   3.Return nullptr if we fail, otherwise
  *     return a CHAR* pointer.
  **/
EXPORT CHAR* FileMapping(WCHAR* szFilePath, int flag, DWORD* fileSize);

#endif

