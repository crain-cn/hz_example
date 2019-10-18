// Shellicon.cpp: implementation of the Shellicon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Shellicon.h"
#include "resource.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Shellicon::Shellicon()
{

}

Shellicon::~Shellicon()
{

}
//////////////////////////////////////////////////////////////////////////
///添加右键小图标
//////////////////////////////////////////////////////////////////////////
VOID Shellicon::CreateShellIcon(int id,HWND hWnd,LPSTR namem,int msg)
{

	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);// 结构的长度，用“位”来做单位。
	nid.hWnd = hWnd;	//消息传送的窗口句柄
	nid.uID = id;//在工程中定义的图标ID
	nid.uFlags = NIF_ICON | NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage = msg;//自定义的消息名称
	nid.hIcon=LoadIcon((HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),MAKEINTRESOURCE(id));
	strcpy(nid.szTip,namem);
	
	Shell_NotifyIcon(NIM_ADD,&nid);
}
//////////////////////////////////////////////////////////////////////////
///删除右键小图标
//////////////////////////////////////////////////////////////////////////
VOID Shellicon::DelShellIcon(int id,HWND hWnd,LPSTR namem,int msg)
{

	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);// 结构的长度，用“位”来做单位。
	nid.hWnd = hWnd;	//消息传送的窗口句柄
	nid.uID = id;//在工程中定义的图标ID
	nid.uFlags = NIF_ICON | NIF_MESSAGE|NIF_TIP;
	nid.uCallbackMessage = msg;//自定义的消息名称
	nid.hIcon=LoadIcon((HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),MAKEINTRESOURCE(id));
	strcpy(nid.szTip,namem);

	Shell_NotifyIcon(NIM_DELETE,&nid);
}





