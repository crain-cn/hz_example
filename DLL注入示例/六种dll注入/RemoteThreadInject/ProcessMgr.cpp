#include "ProcessMgr.h"
#include "DbgInfo.h"

//
//通过进程名返回进程ID
//
DWORD GetTargetProcessIdFromProcname(LPCTSTR lpProcessName)
{
   PROCESSENTRY32 pe; 
   HANDLE thSnapshot; 
   const char   *pPName = NULL;
   BOOL retval, bFind = false; 
   
   PRT(("[!] GetTargetProcessIdFromProcname Enter...\n")); 

   thSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
   if(thSnapshot == INVALID_HANDLE_VALUE) 
   { 
	 PRT(("[-] CreateToolhelp32Snapshot :unable to create toolhelp snapshot!\n")); 
     goto Exit; 
   } 
  
   if((pPName = strrchr(lpProcessName, '\\')) != NULL)
	     pPName++;
   else
         pPName = lpProcessName;
   pe.dwSize = sizeof(PROCESSENTRY32); 
   retval = Process32First(thSnapshot, &pe); 
   while(retval) 
   { 
     if(StrCmpI(pe.szExeFile, pPName) == 0) //StrStrI从字符串末尾向前搜索字串
      { 
        bFind = true; 
         break; 
      } 
     retval = Process32Next(thSnapshot,&pe); 
     pe.dwSize = sizeof(PROCESSENTRY32); 
   } 
   PRT(("[!] GetTargetProcessIdFromProcname Exit...\n")); 

bFind = true;
Exit:
  if(thSnapshot)
   CloseHandle(thSnapshot);
 if(!bFind)
	 return -1;
 return pe.th32ProcessID; 
}

//
//提升进程特权
//
bool AdjustProcessPrivileges(HANDLE hProcess, LPCTSTR PrivilegeName)
{
   
   HANDLE hToken;
   bool bRet = false;
   TOKEN_PRIVILEGES tkp = {0};

   PRT(("[!] AdjustProcessPrivileges Enter...\n"));
   //
   //得到进程的令牌句柄；
   //
   if (!OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
   {
     PRT(("[!] OpenProcessToken failed!"));
	 goto Exit;

   }
   //
   ////获得本地机唯一的标识，查询权限
   //
   LookupPrivilegeValue(NULL, PrivilegeName,&tkp.Privileges[0].Luid); 
   tkp.PrivilegeCount = 1;
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
   AdjustTokenPrivileges(hToken, FALSE, &tkp,sizeof(tkp),(PTOKEN_PRIVILEGES) NULL, 0); //调整获得的权限

   PRT(("[!] AdjustProcessPrivileges Exit...\n"));
  bRet = true;
Exit:
   return bRet;
}

//
//get thread ID from process name
//
unsigned long GetTargetThreadIdFromProcname(LPCTSTR procName) 
{ 
  PROCESSENTRY32 pe; 
  THREADENTRY32  te;
   const char   *pPName = NULL;
  HANDLE thPSnapshot = NULL,thTSnapshot = NULL; 
  BOOL retval, ProcFound = false; 
  unsigned long pTID, threadID = -1; 
  PRT(("[!] GetTargetThreadIdFromProcname Enter...\n"));
  
   if((pPName = strrchr(procName, '\\')) != NULL)
	     pPName++;
   else
         pPName = procName;
  //
  //get system all processes snapshot
  //
  thPSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
  if(thPSnapshot == INVALID_HANDLE_VALUE) 
  { 
     PRT(("[-] Error: unable to create toolhelp snapshot", "Loader")); 
     goto Exit; 
  } 

  pe.dwSize = sizeof(PROCESSENTRY32); 
  retval = Process32First(thPSnapshot, &pe); 
  while(retval) 
  { 
    if(StrCmpI(pe.szExeFile, pPName) == 0) 
      { 
        ProcFound = true; 
        break; 
      } 
     retval = Process32Next(thPSnapshot,&pe); 
     pe.dwSize = sizeof(PROCESSENTRY32); 
   } 
  // CloseHandle(thSnapshot); 
   if(!ProcFound)
	   goto Exit;

   //
   //get system all threads snapshot
   //
  thTSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); 
  if(thTSnapshot == INVALID_HANDLE_VALUE) 
  { 
     PRT(("[-] Error: unable to create toolhelp snapshot", "Loader")); 
     goto Exit; 
  } 
  te.dwSize = sizeof(THREADENTRY32); 
  retval = Thread32First(thTSnapshot, &te); 
  while(retval)
  {
     if(te.th32OwnerProcessID == pe.th32ProcessID)
	 {
	   threadID = te.th32ThreadID;
	   break;
	 }
	 retval = Thread32Next(thTSnapshot, &te);
	 te.dwSize = sizeof(THREADENTRY32); 
   }
 // CloseHandle(thTSnapshot);

  
 /* _asm { 
   mov eax, fs:[0x18] 
   add eax, 36 
   mov [pTID], eax 
  } 

  hProcess = OpenProcess(PROCESS_VM_READ, false, pe.th32ProcessID); 
  if(!hProcess)
  {  
	 ProcFound = false;
	 goto Exit;
  }
  ReadProcessMemory(hProcess, (const void *)pTID, &threadID, 4, NULL); 
  CloseHandle(hProcess); */
  PRT(("[!] GetTargetThreadIdFromProcname Exit...\n"));
 
Exit:
  if(thTSnapshot)
	  CloseHandle(thTSnapshot);
  if(thPSnapshot)
	  CloseHandle(thPSnapshot);
  return threadID;
  
}

