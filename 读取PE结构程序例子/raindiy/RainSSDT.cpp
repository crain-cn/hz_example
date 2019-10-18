// RainSSDT.cpp: implementation of the RainSSDT class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RainSSDT.h"
#include "reateListView.h"
#include "resource.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RainSSDT::RainSSDT()
{

}

RainSSDT::~RainSSDT()
{

}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//主窗体
//////////////////////////////////////////////////////////////////////////
BOOL WINAPI RainSSDT::RainMain_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
		{
    		case WM_INITDIALOG:
					//加载函数
				return InitDiaLog(hWnd,uMsg,wParam,lParam);
   			case WM_COMMAND:
				{	
					CommandMg(LOWORD(wParam),hWnd,wParam,lParam);
				}
   				break;
		
			case WM_CLOSE:
				{
					EndDialog(hWnd,0);
				}
				break;
		}

	return FALSE;	
}

BOOL RainSSDT::InitDiaLog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CreateListView clist;
	LPSTR szTile[] = {"ID","函数名","当前地址","原始地址"};
	clist.CreateSSDTListView(hWnd,IDC_SSDT_LIST,szTile);
	return TRUE;
}

void RainSSDT::CommandMg(int id,HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	
	
}