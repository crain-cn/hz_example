#include "stdafx.h"
#include "Resource.h"
#include "main.h"


HINSTANCE hInst;



/**
*  改变窗口
*/
DWORD WINAPI FuncProc( LPVOID lpParameter)
{
    
	TCHAR  szText[1024],Tz[1024];

	
	PARANFUNC *lps = (PARANFUNC *)lpParameter;
	
	HWND pHwnd = lps->parentHwnd;
	
	HWND qq = lps->qqHwnd;
	
	RECT rect;
	
	::GetWindowRect(qq,&rect);
	
	//left边距+100 、 rigit边距+100，高和宽变为100
	::MoveWindow(qq,rect.left + 100,rect.right + 10,100,100,TRUE);
		
	return NULL;	
}

/**
*  
*   LPVOID lpParameter 句柄参数 
*/ 
DWORD WINAPI ThreadProc( LPVOID lpParameter)
{
	
	TCHAR  szText[1024],Tz[1024];
	int i;
	
	PARANFUNC *lps = (PARANFUNC *)(lpParameter);

	HWND pHwnd = lps->parentHwnd;
	HWND qq = lps->qqHwnd;
	HWND q1 = GetWindow(qq,GW_HWNDNEXT); 

	
	
	//获得数据 
	::SendDlgItemMessage(pHwnd,IDC_MSGTEXT,WM_GETTEXT,sizeof(szText),(LPARAM)szText);
	

	//模拟输入发送消息
	while(1)
	{
		::Sleep(1000);
		
		::SendMessage(qq,WM_SYSCOMMAND,SC_KEYMENU,(WPARAM)0x4c);

		for(i = 0;i < strlen(szText);i++)
		{
				//1 & 0 = 0  1 & 1=1R
			::SendMessage(qq, WM_CHAR, szText[i]& 0xFF , NULL);
		}
	
		::SendMessage(qq, WM_KEYDOWN, VK_RETURN , NULL);
		::SendMessage(qq, WM_CHAR, VK_RETURN , NULL);
		::SendMessage(qq, WM_KEYUP, VK_RETURN , NULL);
		
	}
	
	return NULL;
}



HWND getqq;
DWORD dwThreadId; 
HANDLE hThread;
HANDLE hThread1;
PARANFUNC lp;
BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	int id;
	HICON hIcon;
	
    switch(uMsg)
    {
    	case WM_INITDIALOG:
		{       
			//注册热键 
			::RegisterHotKey(hWnd,100,/**MOD_ALT*/ NULL,VK_HOME ); //VK_HOME 
			hInst = (HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE);
    		/* Set app icons */
			hIcon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICONAPP));
			::SendMessage(hWnd, WM_SETICON, TRUE,  (LPARAM)hIcon);
			::SendMessage(hWnd, WM_SETICON, FALSE, (LPARAM)hIcon);
		}
		    return TRUE;
		case WM_HOTKEY:		//hotkey全局消息接收事件
		{
			TCHAR szTitle[1024];
			//获取获取的置顶窗口名称，改变本窗口名称
			getqq	= GetForegroundWindow();
			::SendMessage(getqq,WM_GETTEXT,sizeof(szTitle),(LPARAM)szTitle);
			::SendMessage(hWnd,WM_SETTEXT,0,(LPARAM)szTitle);
		}
			break; 
   		case WM_COMMAND:	//处理控件消息
   			id = LOWORD(wParam);
   			switch( id )
		    {
		        case IDC_OK:		//开始发送消息
		         {
					 if (getqq > 0)
					 {
						 
						 lp.parentHwnd = hWnd;
						 lp.qqHwnd = getqq;
						 hThread = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProc,&lp,0,&dwThreadId);
						 if (hThread == INVALID_HANDLE_VALUE)
						 {
							 MessageBox(NULL,TEXT("线程创建失败"),TEXT("提示"),NULL);	
							 return -1;
						 }
						 //WaitForSingleObject(hThread,INFINITE); //等待线程退出
						 //CloseHandle(hThread); //关闭句柄
					 }
					 else 
					 {
						 MessageBox(NULL,TEXT("请选择窗口"),TEXT("提示"),NULL);	
					 }
				 } 
		        break;
		        case IDC_STOP:    //暂停发送消息
				{
					
					if(hThread)
					{
						 if(hThread)
						 {
	 						::TerminateThread(hThread,0);
						    ::CloseHandle(hThread);	
	 					 }
					  	 if(hThread1)
						 {
	 						TerminateThread(hThread1,0);
						    CloseHandle(hThread1);	
	 					 }

					}
					
				
				}
				break; 
				case IDC_CLICK:		//改变窗口
				{
					if (getqq > 0)
					{
						 lp.parentHwnd = hWnd;
						 lp.qqHwnd = getqq;
						 hThread1 = CreateThread(NULL,0,FuncProc,&lp,0,&dwThreadId);	
						 if (hThread1 == INVALID_HANDLE_VALUE)
						 {
							MessageBox(NULL,TEXT("线程创建失败"),TEXT("提示"),NULL);	
							return -1;
						 }
						
					}
					else
					{
						 MessageBox(NULL,TEXT("请选择窗口"),TEXT("提示"),NULL);	
					}
				}
				break;
				case IDC_CANCEL:	//关闭应用
		          
		            EndDialog(hWnd, id);
		        break;
		        default:
					break;
		    }
   			break;
		case WM_CLOSE:		//关闭窗口消息
		    ExitThread(0);
			//关闭热键 
			UnregisterHotKey(hWnd,100);
			EndDialog(hWnd, 0);
			break;
    }

    return FALSE;
}

