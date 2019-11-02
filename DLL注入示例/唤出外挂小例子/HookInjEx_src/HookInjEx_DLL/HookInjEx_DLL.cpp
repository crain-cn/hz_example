/***************************************************************
Module name: HookInjEx_DLL.cpp
Copyright (c) 2003 Robert Kuster

Notice:	If this code works, it was written by Robert Kuster.
		Else, I don't know who wrote it.

		Use it on your own risk. No responsibilities for
		possible damages of even functionality can be taken.
***************************************************************/

#include <windows.h>
#include "HookInjEx_DLL.h"
#include "..\HookInjEx\resource.h"
#include <process.h>
#include <stdio.h>
#include "..\HookInjEx\code.h"

#define RENWU 0x1E982E0
//-------------------------------------------------------------
// shared data 
// Notice:	seen by both: the instance of "HookInjEx.dll" mapped
//			into "explorer.exe" as well as by the instance
//			of "HookInjEx.dll" mapped into our "HookInjEx.exe"
#pragma data_seg (".shared")
int		g_bSubclassed = 0;	// START button subclassed?
UINT	WM_HOOKEX = 0;
HWND	g_hWnd	= 0;		// handle of START button
HHOOK	g_hHook = 0;
#pragma data_seg ()

#pragma comment(linker,"/SECTION:.shared,RWS")


//-------------------------------------------------------------
// global variables (unshared!)
//
HINSTANCE	hDll;

// New & old window procedure of the subclassed START button
WNDPROC				OldProc = NULL;	
LRESULT CALLBACK	NewProc( HWND,UINT,WPARAM,LPARAM );


//-------------------------------------------------------------
// DllMain
//
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	if( ul_reason_for_call == DLL_PROCESS_ATTACH ) 
	{
		hDll = (HINSTANCE) hModule;	
		::DisableThreadLibraryCalls( hDll );

		if( WM_HOOKEX==NULL )
			WM_HOOKEX = ::RegisterWindowMessage( "WM_HOOKEX_RK" );			
    }
	
    return TRUE;
}

#define pCW ((CWPSTRUCT*)lParam)



/**
* 修改阳光
*/
void ChangeSunny(HWND hwnd)
{
	HWND wgHwnd =  ::FindWindow(NULL,TEXT("植物大战僵尸中文版"));
	if (wgHwnd ==NULL)
	{			
		return ;
	}

	DWORD procid;
	::GetWindowThreadProcessId(wgHwnd,&procid);//获得进程ID
	


	HANDLE prochandle = ::OpenProcess(PROCESS_ALL_ACCESS,false,procid);//打开进程
	
	DWORD sunny; 
	
	DWORD baseAddr = SUNNY_NUMBER_ADDR;
	DWORD stackAddr;
	DWORD dataAdrr;

	////阳光基址读取读基地址
	ReadProcessMemory (prochandle,(void *)baseAddr,&stackAddr,4,0);      	

	//阳光基址 + 一级偏移 = 一级基址
	stackAddr = stackAddr + 0x768 ;


	//读二级偏移基地址
	ReadProcessMemory(prochandle,(void *)stackAddr,&dataAdrr,4,0);		


	//二级偏移 + 二级偏移 = 阳光地址
	dataAdrr = dataAdrr + 0x5560 ;

	//获取文本框输入
	TCHAR szText1[MAX_PATH] = {0};
	GetDlgItemText(hwnd,IDC_EDIT1,szText1,MAX_PATH);
	sunny = (DWORD)atoi(szText1);
	
	//写入数据
	WriteProcessMemory(prochandle, (void *)dataAdrr, &sunny, 4, 0);	

	CloseHandle(prochandle);
}

/**
* 读取金币方法
*/
void ReadMoney(HWND hwnd)
{
			
	HWND wgHwnd =  ::FindWindow(NULL,TEXT("植物大战僵尸中文版"));

	if (wgHwnd ==NULL)
	{			
		return ;
	}
	DWORD procid;
	::GetWindowThreadProcessId(wgHwnd,&procid);//获得进程ID


	HANDLE prochandle=::OpenProcess(PROCESS_ALL_ACCESS,false,procid);//打开进程
					
	DWORD sunny; 
	
	DWORD baseAddr = SUNNY_NUMBER_ADDR;
	DWORD stackAddr;
	DWORD dataAdrr;

	////阳光基址读取读基地址
	ReadProcessMemory (prochandle,(void *)baseAddr,&stackAddr,4,0);      	

	//阳光基址 + 一级偏移 = 一级基址
	stackAddr = stackAddr + 0x768 ;


	//读二级偏移基地址
	ReadProcessMemory(prochandle,(void *)stackAddr,&dataAdrr,4,0);		


	//二级偏移 + 二级偏移 = 阳光地址
	dataAdrr = dataAdrr + 0x5560 ;


	//读取阳光数据
	ReadProcessMemory(prochandle,(void *)dataAdrr,&sunny,4,0);	


	TCHAR szText1[MAX_PATH] = {0};
	sprintf(szText1,TEXT("%d"),sunny);
	SetDlgItemText(hwnd,IDC_EDIT1,szText1);
				

	::CloseHandle(prochandle);

}



/************************************************************************/
/* 界面操作消息                                                                     */
/************************************************************************/
BOOL CALLBACK Proc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	int id;
	switch(uMsg)
	{
	case WM_CLOSE:
		{

			PostQuitMessage(0);
		}
		break;

	case WM_COMMAND:
		{
			id = LOWORD(wParam);
			switch(id)
			{
			case IDOK: //点击开始
				{
					ReadMoney(hwnd);
				}
				break;
			case IDCANCEL:  //关闭程序
				{
					PostQuitMessage(0);
				}
				break;
			case IDC_BUTTON2:   //全屏吸怪
				{
					ChangeSunny(hwnd);
				}
				break;
			}
		}
		break;

	case WM_INITDIALOG:
		{
	
		}
		break;

	}

	return FALSE;
}

unsigned __stdcall ReceivingThrd(void * pParam)
{

	DialogBox(hDll,MAKEINTRESOURCE(IDD_DIALOG1),NULL,Proc);
	return 0;
}

LRESULT HookProc (
  int code,       // hook code
  WPARAM wParam,  // virtual-key code
  LPARAM lParam   // keystroke-message information
)
{
	if( (pCW->message == WM_HOOKEX) && pCW->lParam ) 
	{
		::UnhookWindowsHookEx( g_hHook );

		if( g_bSubclassed ) 
			goto END;		// already subclassed?
		
		// Let's increase the reference count of the DLL (via LoadLibrary),
		// so it's NOT unmapped once the hook is removed;
		char lib_name[MAX_PATH]; 
		::GetModuleFileName( hDll, lib_name, MAX_PATH );
						
		if( !::LoadLibrary( lib_name ) )
			goto END;		

		// Subclass START button
		
			/**
				HANDLE hMutex = CreateMutex(NULL, false, "MyRainTest3");
				 if (GetLastError() == ERROR_ALREADY_EXISTS)
				 {
					CloseHandle(hMutex);
					
					return FALSE;
				 }
			*/
         
				HANDLE hThread;
				unsigned threadID;
				
				hThread = (HANDLE)_beginthreadex( NULL, 0, &ReceivingThrd, (LPVOID)NULL, 0, &threadID);

				if(hThread == NULL)
				{  

					return FALSE;
				}

				/**
				OldProc = (WNDPROC) 
			::SetWindowLong( g_hWnd, GWL_WNDPROC, (long)NewProc );
		if( OldProc==NULL )			// failed?
			::FreeLibrary( hDll );
		else {						// success -> leave "HookInjEx.dll"
			::MessageBeep(MB_OK);	// mapped into "explorer.exe"
		
		}
				*/
		g_bSubclassed = true;	
	}
	else if( pCW->message == WM_HOOKEX ) 
	{
		::UnhookWindowsHookEx( g_hHook );

		// Failed to restore old window procedure? => Don't unmap the
		// DLL either. Why? Because then "explorer.exe" would call our
		// "unmapped" NewProc and  crash!!
		/**
		if( !SetWindowLong( g_hWnd, GWL_WNDPROC, (long)OldProc ) )
			goto END;

		::FreeLibrary( hDll );

		::MessageBeep(MB_OK);
		*/

		g_bSubclassed = false;	
	}

END:
	return ::CallNextHookEx(g_hHook, code, wParam, lParam);
}


//-------------------------------------------------------------
// NewProc
// Notice:	- new window procedure for the START button;
//			- it just swaps the left & right muse clicks;
//	
LRESULT CALLBACK NewProc(
  HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
	switch (uMsg) 
	{
		case WM_LBUTTONDOWN:
			{
				
				
				uMsg = WM_RBUTTONDOWN; 
			} 
			break;
		case WM_LBUTTONUP:	 
			uMsg = WM_RBUTTONUP;	
			break;

		case WM_RBUTTONDOWN: uMsg = WM_LBUTTONDOWN; break;
		case WM_RBUTTONUP:   uMsg = WM_LBUTTONUP;	break;

		case WM_LBUTTONDBLCLK: uMsg = WM_RBUTTONDBLCLK; break;
		case WM_RBUTTONDBLCLK: uMsg = WM_LBUTTONDBLCLK; break;
	}
	
	return CallWindowProc( OldProc,hwnd,uMsg,wParam,lParam );
}


//-------------------------------------------------------------
// InjectDll
// Notice: 
//	- injects "HookInjEx.dll" into "explorer.exe" (via SetWindowsHookEx);
//	- subclasses the START button (see HookProc for more details);
//
//		Parameters: - hWnd = START button handle
//
//		Return value:	1 - success;
//						0 - failure;
//
int InjectDll( HWND hWnd )
{	
	g_hWnd = hWnd;

	// Hook "*.exe"
	g_hHook = SetWindowsHookEx( WH_CALLWNDPROC,(HOOKPROC)HookProc,
								hDll, GetWindowThreadProcessId(hWnd,NULL) );
	if( g_hHook==NULL )
		return 0;
	
	// By the time SendMessage returns, 
	// the START button has already been subclassed
	SendMessage( hWnd,WM_HOOKEX,0,1 );

	return g_bSubclassed;
}


//-------------------------------------------------------------
// UnmapDll
// Notice: 
//	- restores the old window procedure for the START button;
//	- unmapps the DLL from the remote process
//	  (see HookProc for more details);
//
//		Return value:	1 - success;
//						0 - failure;
//
int UnmapDll( )
{	
	g_hHook = SetWindowsHookEx( WH_CALLWNDPROC,(HOOKPROC)HookProc,
								hDll, GetWindowThreadProcessId(g_hWnd,NULL) );

	if( g_hHook==NULL )
		return 0;	
	
	SendMessage( g_hWnd,WM_HOOKEX,0,0 );

	return (g_bSubclassed == NULL);
}
