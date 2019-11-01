// MsgInject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <Tlhelp32.h>

unsigned long GetTargetThreadIdFromProcname(char *procName) 
{ 
	PROCESSENTRY32 pe; 
	HANDLE thSnapshot, hProcess; 
	BOOL retval, ProcFound = false; 
	unsigned long pTID, threadID; 

	thSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 

	if(thSnapshot == INVALID_HANDLE_VALUE) 
	{ 
		MessageBox(NULL, "Error: unable to create toolhelp snapshot", "Loader", NULL); 
		return false; 
	} 

	pe.dwSize = sizeof(PROCESSENTRY32); 

	retval = Process32First(thSnapshot, &pe); 

	while(retval) 
	{ 
		if(stricmp(pe.szExeFile, procName) == 0) 
		{ 
			ProcFound = true; 
			break; 
		} 

		retval = Process32Next(thSnapshot,&pe); 
		pe.dwSize = sizeof(PROCESSENTRY32); 
		} 

		CloseHandle(thSnapshot); 

		_asm { 
		mov eax, fs:[0x18] 
		add eax, 36 
		mov [pTID], eax 
	} 

	hProcess = OpenProcess(PROCESS_VM_READ, false, pe.th32ProcessID); 
	ReadProcessMemory(hProcess, (const void *)pTID, &threadID, 4, NULL); 
	CloseHandle(hProcess); 

	return threadID; 
}


//
//利用Windows API SetWindowsHookEx实现注入DLL
//
BOOL SetWinHKInject(char * pszDllPath, char * pszProcess)
{
    HMODULE hMod = NULL;
	bool    bSuccess = false;
	DWORD  lpFunc = NULL;
	DWORD  dwThreadId;
	HHOOK  g_hhook = NULL;
    PVOID  pShareM = NULL;
	
    OutputDebugString("[+] SetWinHKInject Enter!\n");


    hMod = LoadLibrary(pszDllPath);
	if(!hMod)
	{
		OutputDebugString("[+] LoadLibrary error!\n");
		goto Exit;
	}


    lpFunc = (DWORD)GetProcAddress(hMod, "MyMessageProc");
	if(!lpFunc)
	{
		OutputDebugString("[+] GetProcAddress error!\n");
		goto Exit;
	}
	 
    
	dwThreadId = GetTargetThreadIdFromProcname(pszProcess);
	if(!dwThreadId)
	 goto Exit;


	g_hhook = SetWindowsHookEx(
		         WH_GETMESSAGE,//WH_KEYBOARD,//WH_CALLWNDPROC,
		         (HOOKPROC)lpFunc,
		         hMod,
                 dwThreadId
		       );

	if(!g_hhook)
	{
	   OutputDebugString("[-] SetWindowsHookEx error !\n");
	   goto Exit;
	}
   



	OutputDebugString("[!] SetWinHKInject Exit!\n");
    bSuccess = true;
Exit:
   if(hMod)
	   FreeLibrary(hMod);
	return bSuccess;

}

int main(int argc, char* argv[])
{
	char szPath[MAX_PATH] = {0};
	char szProcessName[32] = {0};
	printf("inject dll path: \n");
	scanf("%s",szPath);
	
	printf("inject process name: \n");
	scanf("%s",szProcessName);

	SetWinHKInject(szPath, szProcessName);
	return 0;
}

