#include <windows.h>
#include <COMMCTRL.H>
#include "main.h"
#include "create.h"   //创建关于窗体的
#include "resource.h"   
#include "myprocess.h"  //处理进程
#include "rightmenu.h" //处理右键菜单
#include "OpenMyFile.h"

HINSTANCE hInst;

BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch(uMsg)
    {
    	case WM_INITDIALOG:
				//加载函数
				return InitDiaLog(hWnd,uMsg,wParam,lParam);
   		case WM_COMMAND:
			{
				//消息处理函数
   				CommandMg(LOWORD(wParam),hWnd,wParam,lParam);
		    }
   			break;
		case WM_CLOSE:
			{
				//关闭处理
				CloseMg(hWnd,uMsg,wParam,lParam);
			}
			break;
		case WM_LBUTTONDBLCLK:
			{
				//MessageBox(NULL,"","",MB_OK);
			}
			break;
		case WM_CONTEXTMENU:  //添加右键菜单
			{
				ListBoxAddMenu(hWnd,hInst,wParam,lParam);	
			
				//MessageBox(NULL,"","",MB_OK);
			}
			break;
		case WM_SYSCOMMAND:
			{
				//CommandMg(LOWORD(wParam),hWnd,wParam,lParam);

			
			//	MessageBox(NULL,"SSS","SSS",MB_OK);
		
			}
			break;
		case WM_NOTIFY: //处理点击listview
			{
				CommandMgLive(((LPNMHDR)lParam)->code,hWnd,wParam,lParam);
			}
			break;
	
    }

	return FALSE;
}

/**  调用线程 **/
DWORD WINAPI ThreadProc( LPVOID lpParameter)
{

	HWND hwnd = (HWND)lpParameter;
	
	while(1)
	{

		//ListView_DeleteAllItems(GetDlgItem(hwnd,IDC_LIST3));
		EnumMyProcess(hwnd,2);
	
		Sleep(3000);
	}
	return 0;
}
/**  调用线程 **/
DWORD WINAPI ThreadProc1( LPVOID lpParameter)
{

	HWND hwnd = (HWND)lpParameter;
	
	while(1)
	{
		ListAddOrSub(hwnd);
		Sleep(3000);
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////
///////加载函数
//////////////////////////////////////////////////////////////////////////
BOOL InitDiaLog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
		HICON incon;
		DWORD dwThreadId,dwThreadId1;
		HWND list1 = GetDlgItem(hWnd,IDC_LIST2);
		
		//获得窗口消息
		hInst = (HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE);			
	
		//ListView_InsertColumn(list,0,&lvc);
		
		//ListView_SubItemHitTest(list,lp);
		CreateMyListView(hWnd);
		EnumMyProcess(hWnd,1);
		CreateThread(NULL,0,ThreadProc,(LPVOID)hWnd,0,&dwThreadId);
		CreateThread(NULL,0,ThreadProc1,(LPVOID)hWnd,0,&dwThreadId);
		
	 //注册热键 
		  //  RegisterHotKey(hWnd,100,/**MOD_ALT*/ NULL,VK_HOME ); //VK_HOME 
		
    		/* Set app icons 
		
		   	SendMessage(list1,LB_ADDSTRING,1,(LPARAM)"标题1");
		SendMessage(list1,LB_ADDSTRING,0,(LPARAM)"标题");
		*/
		    //hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICONAPP));
		    //SendMessage(hWnd, WM_SETICON, TRUE,  (LPARAM)hIcon);
		    //SendMessage(hWnd, WM_SETICON, FALSE, (LPARAM)hIcon);
		 
			/*
		    * Add initializing code here
		    */
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
///////消息处理函数
//////////////////////////////////////////////////////////////////////////
void CommandMg(int id,HWND hwnd, WPARAM wParam, LPARAM lParam)
{

	switch(id)
	{
		
	case IDC_LOAD:
		{
		
			
			//MessageBox(NULL,"","",MB_OK);
			OpenMyFile open;
			open.lpMystrFilter = TEXT("dll链接库\0*.dll\0\0");
			open.lpMystrTitle = TEXT("打开DLL");
			open.OpenFileDlls(hwnd,hInst,IDC_FILEPATH);  //打开程序
		}
		break;
	case IDC_ZHURU:
		{
		
			InDll(hwnd);
		}
		break;
	case ID_MENU_DLL:  //点击菜单
		{
			//卸载
			CallUndll(hwnd);
		}
		break;
    case ID_MENU_COPY:  //复制一行
		{
			CallCopyRow(hwnd);
		}
		break;
	case ID_MENUALLCOPY: //复制全部
		{
			CallCopyAllRow(hwnd);
		}
		break;
	case ID_MENU_1:  //复制
		{
			CallCopyById(hwnd,0);
		}
		break;
	case ID_MENU_2: //复制父进程
		{
			CallCopyById(hwnd,1);
		}
		break;
	case ID_MENU_3: //复制进程名
		{
			CallCopyById(hwnd,2);
		}
		break;	
	case ID_MENU_4: //复制每行
		{
			CallCopyByRow(hwnd);
		}
		break;
	case ID_MENU_5: //复制全部
		{
			CallCopyByAllRow(hwnd);
		}
		break;
	case ID_MENU_6: //结束进程
		{
		
			TCHAR szFile[125] = {0},szPath[MAX_PATH] = {0};
			


			HWND hwnd1 = GetDlgItem(hwnd,IDC_LIST3);
			int num = ListView_GetSelectionMark(hwnd1);
			if(num == -1)
			{
				MessageBox(NULL,"请选择需要操作的对象!","提示",MB_OK);

				return;
			}

			ListView_GetItemText(hwnd1,num,2,szFile,sizeof(szFile)+1);
	
			if(MessageBox(NULL,"确认要结束该进程么？","提示",MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				//ExitProcess(atoi(szFile));
				
				HANDLE hAndle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, atoi(szFile));
				TerminateProcess(hAndle,0);
				CloseHandle(hAndle);				

				
			}

			

		}
	break;
	default:
		
			break;
	}
}


//////////////////////////////////////////////////////////////////////////
///////消息处理函数
//////////////////////////////////////////////////////////////////////////
void CommandMgLive(int id,HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch(id)
	{
	case NM_DBLCLK:
		{
			switch(LOWORD(wParam))
			{
				case IDC_LIST3:  //点击listview
					{
						GetProMoudle(hwnd);
					}
					break;
			}
			
		}			
		break;
		
	default:
		
			break;
	}
}





void CloseMg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//PostQuitMessage(0);
	EndDialog(hWnd,0);
}