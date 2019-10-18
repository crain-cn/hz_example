// RainStatus.cpp: implementation of the RainStatus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RainStatus.h"
#include "SDTShadowRestore.h"
#include "resource.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RainStatus::RainStatus()
{

}

RainStatus::~RainStatus()
{

}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//主窗体
//////////////////////////////////////////////////////////////////////////
BOOL WINAPI RainStatus::RainStatusMain_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
		{
    		case WM_INITDIALOG:
					//加载函数
				return InitDiaLog(hWnd, uMsg, wParam, lParam);
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

BOOL RainStatus::InitDiaLog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	SDTShadowRestore sys;

	HWND list = GetDlgItem(hWnd,IDC_SYS_STATUS_LIST);

	sys.SetListShowSys(list);
	return TRUE;
}
void RainStatus::CommandMg(int id,HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	

}