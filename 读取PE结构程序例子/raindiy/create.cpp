#include <windows.h>
#include "resource.h"
#include <COMMCTRL.H>
#include "create.h"
//////////////////////////////////////////////////////////////////////////
/////用于创建Liew控件
//////////////////////////////////////////////////////////////////////////
VOID CreateMyListView(HWND hWnd)
{
	
		//LVIF_DI_SETITEM 
		int i;
		HWND list = GetDlgItem(hWnd,IDC_LIST3);
		LVCOLUMN lvc;
		LPSTR colName[] = {"进程名称","父进程","进程ID","线程数"};

		memset(&lvc,0,sizeof(lvc));
		
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCFMT_CENTER | LVCF_SUBITEM ; //
		lvc.cx = 100;
		lvc.iImage = 1;
		lvc.fmt = LVCFMT_LEFT;	
		SetWindowLong( GetDlgItem(hWnd,IDC_LIST3),GWL_STYLE,  WS_EX_NOPARENTNOTIFY|
			WS_VISIBLE |WS_VSCROLL |LVS_REPORT |WS_EX_RIGHTSCROLLBAR | WS_TABSTOP  |WS_CHILDWINDOW |WS_EX_LEFT );
		//|   WS_EX_CLIENTEDGE    BS_GROUPBOX LVS_SHAREIMAGELISTS  WS_EX_LTRREADING | LVS_EX_FULLROWSELECT
		
		for(i = 0;i < 5;i++)
		{
			lvc.pszText = colName[i];
			lvc.iSubItem = i;
			SendMessage(list,LVM_INSERTCOLUMN,i,(LPARAM)&lvc);
		}
		HFONT f = CreateFont(18,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"MS Sans Serif" );
		
		// 设置ListCtrl整行被选中
		DWORD dwStyle = ::SendMessage(list,LVM_GETEXTENDEDLISTVIEWSTYLE,0,0);
		
		dwStyle |= LVS_EX_FULLROWSELECT;
		SendMessage(list,LVM_SETEXTENDEDLISTVIEWSTYLE,0,dwStyle); 
		/////000000000000000000000000
		
		
		//ListView_SetHotItem(list,2);
		/***
		 LVITEM lvitem,lvitem1;
		 LVFINDINFO li;
		 lvitem.mask = LVIF_DI_SETITEM | LVIF_PARAM | LVIF_INDENT |LVIS_OVERLAYMASK;
		 
		 lvitem.cchTextMax = 256;
		 lvitem.iItem = 0;
		 lvitem.iSubItem = 0;
		 lvitem.pszText = "标题";
		 lvitem.state = 0;

		ListView_SetItem(list,&lvitem);
		ListView_SetItem(list,&lvitem1);	
		***/
		
}

//////////////////////
///////用于加载右键菜单
//////////////////
VOID ListBoxAddMenu(HWND hwnd,HINSTANCE hInst, WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu;
	HMENU pop;
	TCHAR szF[125] = {0};
	int dd;
	if((hMenu = LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU1))) == NULL)
	{
		return;
	}
	if(GetDlgItem(hwnd,IDC_LIST2) == (HWND)wParam)
	{
		pop = GetSubMenu(hMenu,0);
		
		TrackPopupMenu(pop,TPM_NONOTIFY |TPM_LEFTALIGN | TPM_RIGHTBUTTON,LOWORD(lParam) ,HIWORD(lParam),0,hwnd,NULL);
	
	}

	if(GetDlgItem(hwnd,IDC_LIST3) == (HWND)wParam)
	{
		pop = GetSubMenu(hMenu,1);
		//TPM_LEFTALIGN
		TrackPopupMenu(pop, TPM_RIGHTBUTTON,LOWORD(lParam) ,HIWORD(lParam),0,hwnd,NULL);
		//GetTraceEnableFlags(pop);
	}
	
	DestroyMenu(hMenu); //释放菜单

}
//////////////////////////////////////////////////////////////////////////
/////将窗口最小化到通知域
//////////////////////////////////////////////////////////////////////////
VOID MiniToTay(HWND hWnd)
{
	//RECT rect,recto;
	//GetWindowRect(hWnd,&rect);
	
}