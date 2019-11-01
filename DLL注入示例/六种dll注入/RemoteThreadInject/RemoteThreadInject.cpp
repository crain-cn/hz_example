#include "RemoteThreadInject.h"
#include "DbgInfo.h"
#include "ProcessMgr.h"



void main(void)
{
	CHAR szBuf[MAX_PATH] = {0};
	CHAR szDll[MAX_PATH] = {0};
	INJECT_PARAM stInjectParam = {0};
	printf("please input injected process name: ");
	scanf("%s", szBuf);
	printf("please input injected Dll name: ");
	scanf("%s", szDll);

	
	
	//配置注入参数
	stInjectParam.bInjectCode = FALSE;
	stInjectParam.bProcessName = TRUE;
	strncpy(stInjectParam.strProcessName, szBuf, MAX_PATH);

	ZeroMemory(szBuf, MAX_PATH);
	GetCurrentDirectory(MAX_PATH, szBuf);
	strcat(szBuf, "\\");
	strcat(szBuf, szDll);
	OutputDebugString(szBuf);
	strncpy(stInjectParam.strDllPath, szBuf, MAX_PATH);

	RemoteThreadInject(&stInjectParam);

}

__declspec(naked) void loadDll(void) 
{ 
	_asm{ 
		// Placeholder for the return address 
		push 0xDEADBEEF 
			
			// Save the flags and registers 
			pushfd 
			pushad 
			
			// Placeholder for the string address and LoadLibrary 
			push 0xDEADBEEF 
			mov eax, 0xDEADBEEF 
			
			// Call LoadLibrary with the string parameter 
			call eax 
			
			// Restore the registers and flags 
			popad 
			popfd 
			
			// Return control to the hijacked thread 
			ret 
			NOP
			NOP
	} 
} 

__declspec(naked) void loadDll_end(void) 
{ 
} 

//
//利用CreateRemoteThread+WriteProcessMemroy注入DLL或code
//
bool  RemoteThreadInject(PINJECT_PARAM pInjectParam)
{
   bool bSuccess;
   PVOID stub;
   ULONG uCodeLenth = 0;
   CONTEXT ctx; 
   PDWORD  pfLoadDllAddr = NULL, pDllStr =NULL, pRetAddr = NULL;
   PUCHAR  pInjectCode = NULL;
   unsigned long uPID, threadID, stubLen, oldIP, oldprot, loadLibAddy; 
   HANDLE hProcess = NULL, hThread = NULL;
   HMODULE hMod = NULL;
   DWORD dwTid = 0, dwWrite;;
   LPSTR  lpRemoteString = NULL, dllString = NULL;
   LPCTSTR lpDllString = NULL, lpProcessName = NULL;
   PTHREAD_START_ROUTINE pfnThreadRtn = NULL;

   lpDllString    = pInjectParam->strDllPath;
   lpProcessName  = pInjectParam->strProcessName;
   bSuccess       = false;
   
   
   PRT(("[!] RemoteThreadInject Enter...\n")); 

   //
   //提升进程特权
   //
     if(!AdjustProcessPrivileges(GetCurrentProcess(), "SeDebugPrivilege"))
	 {
	    PRT(("[-] AdjustProcessPrivileges ret false!\n"));
		goto Exit;
	 }
   //
   //获取LoadLibraryA地址
   //
      pfnThreadRtn = (PTHREAD_START_ROUTINE) GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	  loadLibAddy   = (ULONG)pfnThreadRtn;
	  if (pfnThreadRtn == NULL)
	  {
		  PRT(("[-] GetProcAddress Failed:%d\n",GetLastError()));
		  goto Exit;
	  }
    
     uPID = GetTargetProcessIdFromProcname(pInjectParam->strProcessName); 
     if(uPID == -1)
     { 
		 PRT(("[-] GetTargetProcessIdFromProcname Failed!\n"));
		 goto Exit;
     }

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, uPID); //CREATE_THREAD_ACCESS
    if(!hProcess)
	{
	   	 PRT(("[-] OpenProcess Failed!\n"));
		 goto Exit;
	}

   if(!pInjectParam->bInjectCode)
   {
     //
	 //inject by CreateRemoteThread & LoadLibraryA
     //
       lpRemoteString = (LPSTR)VirtualAllocEx(hProcess, NULL, strlen(lpDllString)+1, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE); 

       WriteProcessMemory(hProcess, (LPVOID)lpRemoteString, (LPVOID)lpDllString,strlen(lpDllString), NULL); 

       hThread = CreateRemoteThread(hProcess, NULL, NULL, pfnThreadRtn, lpRemoteString, NULL, &dwTid); 

       if(hThread)
         WaitForSingleObject( hThread, INFINITE );

       VirtualFreeEx( hProcess, lpRemoteString, strlen(lpDllString), MEM_DECOMMIT );   
       if(hThread)
         CloseHandle( hThread ); 
       if(hProcess)  
         CloseHandle(hProcess); 
   }
   //注入代码
//     else
//    {
//      //
//      //inject code method 
//      //
//  
// 	   //
// 	   //在目标进程中，分配待注入代码的空间
// 	   //
//        stub = VirtualAllocEx(hProcess, NULL, pInjectParam->dwExtendLength, MEM_COMMIT, PAGE_EXECUTE_READWRITE); 
// 	   if(!stub)
// 	   {
//            PRT(("[-] VirtualAllocEx Failed!\n"));
// 		   goto Exit;
// 	   }
// 
// 
// 	   ////
// 	   ////将dll的名称写入目标进程中
// 	   //// 
// 	   //
// 	   //获取目标进程的线程ID，打开并悬挂该线程
// 	   //
// 	   threadID = GetTargetThreadIdFromProcname(lpProcessName); 
//        hThread = OpenThread((THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME), false, threadID); 
//        SuspendThread(hThread);
//        
// 	   //
// 	   //获取该线程的上下文环境
// 	   //
// 	   ctx.ContextFlags = CONTEXT_CONTROL; 
//        GetThreadContext(hThread, &ctx); 
// 
// 	   //
// 	   //获取上下文环境中待执行的下条指令地址
// 	   //
//        oldIP = ctx.Eip; 
// 
// 	   //
// 	   //替换上下文环境中下条指令地址，使其指向我们的注入代码stub
// 	   //
//        ctx.Eip = (DWORD)stub; 
//        ctx.ContextFlags = CONTEXT_CONTROL; 
// 
// 
// 	   pRetAddr       =  (DWORD *)(pInjectParam->cExtend + 1);
// 	   *pRetAddr      =  oldIP;
// 
// 	   pDllStr        =  (DWORD *)(pInjectParam->cExtend + 9);
// 	   *pDllStr       =   ((DWORD)stub + 24);
// 
// 	   
// 	   pfLoadDllAddr  =  (DWORD *)(pInjectParam->cExtend + 15);
// 	   *pfLoadDllAddr =   loadLibAddy;
//        
// 	   ////
// 	   ////改变待注入函数的保护属性，并动态改写其中数据
// 	   ////
// 	   //
// 	   //将待注入代码写入目标进程中
// 	   //
//           bSuccess = WriteProcessMemory(hProcess, stub, pInjectParam->cExtend, pInjectParam->dwExtendLength, &dwWrite); 
// 		  if(!bSuccess || (dwWrite != pInjectParam->dwExtendLength))
// 		  {
// 		     PRT(("[-] VirtualAllocEx Failed!\n"));
// 		     goto Exit;
// 		  }
// 
// 
// 	   //
// 	   //重新设置线程上下文
// 	   //
//        SetThreadContext(hThread, &ctx); 
//        
// 	   //
// 	   //恢复该线程的执行
// 	   //
//        ResumeThread(hThread); 
// 
//        Sleep(5000); 
// 
//        VirtualFreeEx(hProcess, stub, pInjectParam->dwExtendLength, MEM_DECOMMIT); 
// 	   CloseHandle(hThread);
//        CloseHandle(hProcess); 
//    
//    }

  PRT(("[!] RemoteThreadInject Exit...\n")); 
  bSuccess = true;
Exit:
   return bSuccess;
}
