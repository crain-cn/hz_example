// reateListView.cpp: implementation of the CreateListView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "reateListView.h"
#include <COMMCTRL.H>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CreateListView::CreateListView()
{

}

CreateListView::~CreateListView()
{

}

//////////////////////////////////////////////////////////////////////////
///  hwnd 窗口句柄
///  id   控件ID
///  colName[] 添加的列信息
//////////////////////////////////////////////////////////////////////////
VOID CreateListView::CreateSSDTListView(HWND hWnd,int id,LPSTR colName[])
{
	
		//LVIF_DI_SETITEM 
		int i;
		HWND list = GetDlgItem(hWnd,id);
		LVCOLUMN lvc;

		memset(&lvc,0,sizeof(lvc));
		
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCFMT_CENTER | LVCF_SUBITEM ; //
		lvc.cx = 100;
		lvc.iImage = 1;
		lvc.fmt = LVCFMT_LEFT;	
		SetWindowLong( GetDlgItem(hWnd,id),GWL_STYLE,  WS_EX_NOPARENTNOTIFY|
			WS_VISIBLE |WS_VSCROLL |LVS_REPORT |WS_EX_RIGHTSCROLLBAR | WS_TABSTOP  |WS_CHILDWINDOW |WS_EX_LEFT );
		//|   WS_EX_CLIENTEDGE    BS_GROUPBOX LVS_SHAREIMAGELISTS  WS_EX_LTRREADING | LVS_EX_FULLROWSELECT
		
		for(i = 0;i < (sizeof(colName));i++)
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
}