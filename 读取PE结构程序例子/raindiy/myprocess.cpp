#include <windows.h>
#include <tlhelp32.h>
#include <COMMCTRL.H>
#include "myprocess.h"
#include "resource.h"
#include <locale.h>   //改变字符集
#include <tlhelp32.h> 
#include <Psapi.h> //列举进程信息要包含的头文件
#pragma	comment	(lib, "psapi.lib")  
//////////////////////////////////////////////////////////////////////////
/////////列举windows进程
//////////////////////////////////////////////////////////////////////////
VOID EnumMyProcess(HWND hwnd,int type)
{
 int i = 0;
 BOOL bRet; 
 HANDLE hProcessSnap;
 unsigned long ProcessID = -1;
 PROCESSENTRY32 pe;
 ////----------------------------
 LVITEM lv1,lv2;


 lv1.iSubItem = 0;
 lv1.mask = LVCF_FMT | LVCF_TEXT | LVCF_IMAGE ; //  |
 
 
//---------------------------

 pe.dwSize = sizeof(pe);
 hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

 bRet = Process32First(hProcessSnap, &pe);
 
 while(bRet)
 { 
	 TCHAR Pid[125] = {0},PrentPid[125] = {0},Size[125] = {0};
	 lv1.iItem = i;
	 //设置进程名称
	 lv1.pszText = pe.szExeFile;
	  lv1.cchTextMax = strlen(pe.szExeFile) + 1;
	  if(type == 1)
	  {
		 SendMessage(GetDlgItem(hwnd,IDC_LIST3),LVM_INSERTITEM,0,(LPARAM)&lv1);
		 itoa(pe.th32ParentProcessID,PrentPid,10); //父进程
		 itoa(pe.th32ProcessID,Pid,10);  //进程ID
		 itoa(pe.cntThreads,Size,10);
		 
		 ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,1,PrentPid);
		 ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,2,Pid);
		 ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,3,Size);
 	  }
	  else if(type == 2)
	  {
		  
	
		 itoa(pe.th32ParentProcessID,PrentPid,10); //父进程
		 itoa(pe.th32ProcessID,Pid,10);  //进程ID
		 itoa(pe.cntThreads,Size,10);
	
		// ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,1,PrentPid);
		// ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,2,Pid);
		 ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,3,Size);
		 
	  }
	

	 

	
	 //SendMessage(GetDlgItem(hwnd,IDC_LIST3),LVM_INSERTITEM,0,(LPARAM)&lv2);
	 //ListView_InsertItem(GetDlgItem(hwnd,IDC_LIST3),&lv2);
     //ListView_SetItem(GetDlgItem(hwnd,IDC_LIST3),&lv2);
	 //ListView_SetItem()
	

   bRet = Process32Next(hProcessSnap, &pe);
	i++;
 }
 CloseHandle(hProcessSnap);
}

//////////////////////////////////////////////////////////////////////////
////判断DLL是否存在
//////////////////////////////////////////////////////////////////////////
int IsDLLInfo(HWND hWnd,char *szDll)
{
	TCHAR szFile[MAX_PATH] = {0};
	HWND list = GetDlgItem(hWnd,IDC_LIST3);
	int count = ListView_GetItemCount(list);
	for (int i= 0;i < count;i++)
	{
		ZeroMemory(szFile,sizeof(szFile));
		ListView_GetItemText(list,i,0,szFile,sizeof(szFile));
		if(strcmp(szDll,szFile) == 0)
		{
			return i;
		}
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////////
////添加进程
//////////////////////////////////////////////////////////////////////////
VOID EnumMyProcessAdd(HWND hwnd)
{
 int i = 0;
 BOOL bRet; 
 HANDLE hProcessSnap;
 unsigned long ProcessID = -1;
 PROCESSENTRY32 pe;
 ////----------------------------
 LVITEM lv1,lv2;


 lv1.iSubItem = 0;
 lv1.mask = LVCF_FMT | LVCF_TEXT | LVCF_IMAGE ; //  |
 
//---------------------------

 pe.dwSize = sizeof(pe);
 hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

 bRet = Process32First(hProcessSnap, &pe);
 
 while(bRet)
 { 
	 TCHAR Pid[125] = {0},PrentPid[125] = {0},Size[125] = {0};
	
		
		if(IsDLLInfo(hwnd,pe.szExeFile) == -1)
		{
		 lv1.iItem = i;
		 //设置进程名称
		 lv1.pszText = pe.szExeFile;
		 lv1.cchTextMax = strlen(pe.szExeFile) + 1;
		 SendMessage(GetDlgItem(hwnd,IDC_LIST3),LVM_INSERTITEM,0,(LPARAM)&lv1);
		 itoa(pe.th32ParentProcessID,PrentPid,10); //父进程
		 itoa(pe.th32ProcessID,Pid,10);  //进程ID
		 itoa(pe.cntThreads,Size,10);
		// MessageBox(NULL,pe.szExeFile,pe.szExeFile,MB_OK);
		 ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,1,PrentPid);
		 ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,2,Pid);
		 ListView_SetItemText(GetDlgItem(hwnd,IDC_LIST3),i,3,Size);
		}
		

   bRet = Process32Next(hProcessSnap, &pe);
	i++;
 }
 CloseHandle(hProcessSnap);
}

BOOL EnumMyProcessCmp(HWND hwnd,char *file)
{
 BOOL bRet; 
 HANDLE hProcessSnap;
 unsigned long ProcessID = -1;
 PROCESSENTRY32 pe;

 pe.dwSize = sizeof(pe);
 hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

   bRet = Process32First(hProcessSnap, &pe);
 
	 while(bRet)
	 { 
    	 //设置进程名称
		 if(strcmp(file,pe.szExeFile) == 0)
		 {
			return TRUE;
		 }		 
	

		  bRet = Process32Next(hProcessSnap, &pe);
	}
		
 CloseHandle(hProcessSnap);
 return FALSE;
}

VOID EnumMyProcessSub(HWND hWnd)
{
	TCHAR szFile[MAX_PATH] = {0};
	HWND list = GetDlgItem(hWnd,IDC_LIST3);
	int count = ListView_GetItemCount(list);
	for (int i= 0;i < count;i++)
	{
		ZeroMemory(szFile,sizeof(szFile));
		ListView_GetItemText(list,i,0,szFile,sizeof(szFile));
		if(EnumMyProcessCmp(hWnd,szFile) == FALSE)
		{
			//MessageBox(NULL,szFile,szFile,MB_OK);
			ListView_DeleteItem(list,i);
		}
	}
}

VOID ListAddOrSub(HWND hwnd)
{
	TCHAR num[MAX_PATH] = {0};
	EnumMyProcessAdd(hwnd); //检查进程假如有就添加
	EnumMyProcessSub(hwnd); //查看进程判断没有就减去
	
	int number = ListView_GetItemCount(GetDlgItem(hwnd,IDC_LIST3));
	
	itoa(number,num,10);

	SendMessage(GetDlgItem(hwnd,IDC_NUM),WM_SETTEXT,sizeof(num),(LPARAM)num);
}
//////////////////////////////////////////////////////////////////////////
////获得DLL
//////////////////////////////////////////////////////////////////////////
VOID ListProcessModules1(DWORD dwPID,HWND hwnd)
{
	HMODULE hMods[1024];
	HANDLE hProcess;
	DWORD cbNeeded;
	unsigned int i;

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,dwPID);
	if(NULL==hProcess)return ;

	//调用EnumProcessModules
	if(EnumProcessModules(hProcess,hMods,sizeof(hMods),&cbNeeded))
	{
		for(i=1;i<(cbNeeded/sizeof(HMODULE));i++)
		{
			TCHAR szModName[MAX_PATH];
			if(GetModuleFileNameEx(hProcess,hMods[i],szModName,sizeof(szModName)/sizeof(TCHAR)))
			{
				SendMessage(GetDlgItem(hwnd,IDC_LIST2),LB_ADDSTRING,0,(LPARAM)szModName);
			}
		}
	}
	CloseHandle(hProcess);
}

/************ DBG提权 *****************/
BOOL BDebugProcess2(HANDLE hProcess, LPCTSTR PrivilegeName)
{
HANDLE hToken; 
   TOKEN_PRIVILEGES tkp; 

 
   if (!OpenProcessToken(hProcess, 
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
      return( FALSE ); 
 
  
 
   LookupPrivilegeValue(NULL,PrivilegeName, 
        &tkp.Privileges[0].Luid); 
 
   tkp.PrivilegeCount = 1;  // one privilege to set    
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
 

 
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
        (PTOKEN_PRIVILEGES)NULL, 0); 


	if(GetLastError()!=ERROR_SUCCESS)
	{
		MessageBox(NULL,"所申请的权限全部成功","成功",MB_OK);
		return FALSE;
	} 
	
	return TRUE;
}



//////////////////////////////////////////////////////////////////////////
//////查找全部模板
//////////////////////////////////////////////////////////////////////////
VOID GetProMoudle(HWND hwnd)
{
	//LVITEM lv1;
	int i;
	TCHAR szFile[125] = {0};
	HWND hwnd1 = GetDlgItem(hwnd,IDC_LIST3);
	//SendMessage(hwnd1,LVM_GETITEM,0,(LPARAM)&lv1);
	
	ListView_GetItemText(hwnd1,ListView_GetSelectionMark(hwnd1),2,szFile,sizeof(szFile)+1);
	//ListView_GetItemText(hwnd1,lv1.iItem,2,szFile,sizeof(szFile)+1);
	//ListView_GetEditControl

	for (i = SendMessage(GetDlgItem(hwnd,IDC_LIST2),LB_GETCOUNT,0,0);i >= 0;i--)
	{
		SendMessage(GetDlgItem(hwnd,IDC_LIST2),LB_DELETESTRING,i,0);
	}
	
	//进程模板
	ListProcessModules1(atoi(szFile),hwnd);			
}

//////////////////////////////////////////////////////////////////////////
///DBUG提权
//////////////////////////////////////////////////////////////////////////
BOOL EnableDebugPriv(const char * name)
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tp;
    LUID luid;
	tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    tp.Privileges[0].Luid = luid;
    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken)) return FALSE;
    //获得进程本地唯一ID
    if(!LookupPrivilegeValue(NULL, name, &luid)) return FALSE;
    
    //调整进程权限
    if(!AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) return FALSE;
    
    return TRUE;
}

DWORD GetProcessPid(char *szProcName) {     
	DWORD retPid = -1;  
	BOOL hMore;
	HANDLE hProcSnap;
	PROCESSENTRY32 pe32;   //用来存放快照进程信息的一个结构体;     
	pe32.dwSize = sizeof(pe32);   //设置大小;     
	//创建所有进程的快照;     
	hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);     
	if(hProcSnap == INVALID_HANDLE_VALUE)     
	{         
	
		return -1;     
	}     //遍历进程快照，获得进行信息;     
	hMore = Process32First(hProcSnap, &pe32);     
	while(hMore)     
	{            
		if(strcmp(pe32.szExeFile, szProcName)==0)             
		{                 
			retPid = pe32.th32ProcessID;                 
			break;             
		}         
		hMore = Process32Next(hProcSnap,&pe32) ;  //后的下个进程信息;     
	}     
	if(retPid == -1) NULL;          
	CloseHandle(hProcSnap);     
	return retPid; 
} 
//////////////////////////////////////////////////////////////////////////
////////加载DLL
//////////////////////////////////////////////////////////////////////////
BOOL DllInject(WCHAR* szDllName,DWORD dwRemoteProcessId) 
{     
	void *pszLibFileRemote = NULL;        
	HANDLE hRemoteThread;   
	HANDLE hRemoteProcess;
	PTHREAD_START_ROUTINE pfnStartAddr;
	int cbdll;
    EnableDebugPriv(SE_DEBUG_NAME);
	hRemoteProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwRemoteProcessId);  //打开远程进程;     
	//计算dll路径名字符串所需要的内存空间;     
	cbdll = sizeof(WCHAR) * lstrlenW(szDllName) + 1;     //使用virtualallocEx 函数在远程进程的地址空间分配dll文件名缓冲区;     
	pszLibFileRemote = (TCHAR *)VirtualAllocEx( hRemoteProcess, NULL, cbdll, MEM_COMMIT, PAGE_READWRITE);     
	if( WriteProcessMemory(hRemoteProcess,pszLibFileRemote,(PVOID)szDllName, cbdll, NULL)==FALSE)     
	{         
	     
		return FALSE;     
	}     
	//计算LoadLibraryW的入口地址;     
	pfnStartAddr = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("Kernel32.dll")), "LoadLibraryW");     
	hRemoteThread = CreateRemoteThread( hRemoteProcess, NULL, 0,pfnStartAddr, pszLibFileRemote, 0, NULL);     
	if(hRemoteThread == NULL)         
	{               
		return FALSE;         
	}     
	WaitForSingleObject(hRemoteThread,INFINITE);  //等待线程结束     
	VirtualFreeEx(hRemoteProcess,pszLibFileRemote, 0 ,MEM_RELEASE);  //释放申请的空间     
	CloseHandle(hRemoteThread);  //关闭句柄     
	CloseHandle(hRemoteProcess);     
	return TRUE; 
}   

/**  调用线程 **/
DWORD WINAPI ThreadProc2( LPVOID lpParameter)
{
	BOOL fal;
	TCHAR szFile[125] = {0},szPath[MAX_PATH] = {0};
	WCHAR *szName; 
	HWND hwnd = (HWND)lpParameter;
	HWND hwnd1 = GetDlgItem(hwnd,IDC_LIST3);	
		
	
	ListView_GetItemText(hwnd1,ListView_GetSelectionMark(hwnd1),2,szFile,sizeof(szFile)+1);
	
	GetDlgItemTextA(hwnd,IDC_FILEPATH,szPath,sizeof(szPath));
	szName = (WCHAR*)malloc(MAX_PATH * 2 +1);
	
	setlocale(LC_ALL,"chs");
	mbstowcs(szName,szPath,sizeof(szPath));
///	mbsrtowcs(szName,szPath,sizeof(szPath));
	fal = DllInject(szName,atoi(szFile));
	setlocale(LC_ALL,"C");
	if(fal)
	{
		MessageBox(NULL,"注入成功","提示",MB_OK);
		SendMessage(GetDlgItem(hwnd,IDC_LIST2),LB_ADDSTRING,0,(LPARAM)szPath);
	}
	else
	{
		MessageBox(NULL,"失败","提示",MB_OK);
	}

	return 0;
}
//////////////////////////////////////////////////////////////////////////
//////加载DLL程序
//////////////////////////////////////////////////////////////////////////
VOID InDll(HWND hwnd)
{
	DWORD dwThreadId;

	CreateThread(NULL,0,ThreadProc2,(LPVOID)hwnd,0,&dwThreadId);
}
//////////////////////////////////////////////////////////////////////////
////远程卸载DLL
//////////////////////////////////////////////////////////////////////////
BOOL UnloadDll(DWORD dwPid, char *strDllName)
{
	LPVOID lpBuf; 
	LPVOID pFun;
	DWORD     dwSize = 0;
	DWORD     dwWritten = 0;
	DWORD     dwHandle = 0; 
    HANDLE hThread;
	HANDLE hProcess;
	 EnableDebugPriv(SE_DEBUG_NAME);
	//获取宿主进程的句柄，注意那几个参数，不然会出错
	hProcess = OpenProcess(PROCESS_CREATE_THREAD|PROCESS_VM_OPERATION|PROCESS_VM_WRITE,
				FALSE, dwPid);
	if(hProcess == NULL)
	{
		MessageBox(NULL, "无法获取进程句柄", "错误", MB_OK | MB_ICONERROR);
		return FALSE;
	}


	dwSize = strlen(strDllName)+ 1;//dll的全路径名的长度，待会分配内存要用到的

	//向宿主进程分配内存，返回一个指针
	lpBuf = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);

	//如果在宿主进程空间写失败就直接报错闪人
	if( !WriteProcessMemory(hProcess, lpBuf, (LPVOID)strDllName, dwSize, &dwWritten)){   
		VirtualFreeEx(hProcess, lpBuf, dwSize, MEM_DECOMMIT);
		CloseHandle(hProcess);
		MessageBox(NULL, "在目标进程中写入失败", "错误", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	//获取GetModuleHandleA函数地址
	pFun = GetProcAddress(GetModuleHandle("Kernel32"), "GetModuleHandleA");

	//在宿主进程中创建一个远程线程，线程函数为上面导出的GetModuleHandleA，参数为lpBuf指针，还
	//记得我们获取的dll全路径不
	hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pFun,
										lpBuf, 0, NULL);
	//如果创建线程失败，直接报错退出
	if(hThread == NULL){
	CloseHandle(hProcess);
	MessageBox(NULL, "在目标进程创建远程线程失败", "错误", MB_OK | MB_ICONERROR);
		  return FALSE;
	}

	//     等待GetModuleHandle运行完毕   
	WaitForSingleObject(hThread, INFINITE); 
	//     获得GetModuleHandle的返回值   
	GetExitCodeThread(hThread, &dwHandle);

	//     释放目标进程中申请的空间   
	VirtualFreeEx(hProcess, lpBuf, dwSize, MEM_DECOMMIT);
	CloseHandle(hThread);

	//     使目标进程调用FreeLibraryAndExit，卸载DLL,实际也可以用FreeLibrary，但是我发现前者好一点
	pFun = GetProcAddress(GetModuleHandle("Kernel32"), "FreeLibraryAndExitThread");
	hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pFun,
							 (LPVOID)dwHandle, 0, NULL);   
	// 等待FreeLibraryAndExitThread执行完毕   
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hProcess);

	return TRUE;    //操作成功
}
