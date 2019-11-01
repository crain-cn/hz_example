#ifndef _PROCESS_MGR_
#define _PROCESS_MGR_

#ifdef __cplusplus
extern "C" {
#endif
#include <windows.h>
#include <shlwapi.h>
#include <Tlhelp32.h>
	//
	//通过进程名返回进程ID
	//
	DWORD GetTargetProcessIdFromProcname(LPCTSTR lpProcessName);
	
	DWORD GetTargetThreadIdFromProcname(LPCTSTR  lpProcessName);
	
	//
	//提升进程特权
	//
	bool AdjustProcessPrivileges(HANDLE hProcess, LPCTSTR PrivilegeName);
	
#ifdef __cplusplus
}
#endif

#endif 
