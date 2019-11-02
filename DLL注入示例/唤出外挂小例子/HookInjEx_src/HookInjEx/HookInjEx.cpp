/***************************************************************
Module name: HookInjEx.cpp
Copyright (c) 2003 Robert Kuster

Notice:	If this code works, it was written by Robert Kuster.
		Else, I don't know who wrote it.

		Use it on your own risk. No responsibilities for
		possible damages of even functionality can be taken.
***************************************************************/

#include <windows.h>

#include "resource2.h"
#include "..\HookInjEx_DLL\HookInjEx_DLL.h"
#pragma comment(lib,"HookInjEx.lib")
//-----------------------------------------------
// global variables & forward declarations
//
HWND hStart;		// handle to start button

BOOL CALLBACK MainDlgProc (HWND,UINT,WPARAM,LPARAM);


//-----------------------------------------------
// WinMain
//
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	hStart = ::FindWindow (NULL,"植物大战僵尸中文版");			// get HWND of taskbar first
	
	if(hStart == NULL)
	{
		MessageBox(NULL,TEXT("请运行游戏"),TEXT("请运行游戏"),MB_OK);
		return NULL;
	}
	// display main dialog 
	::DialogBoxParam (hInstance, MAKEINTRESOURCE (IDD_WININFO), NULL, MainDlgProc, NULL);

	return 0;
}


//-----------------------------------------------
// MainDlgProc
// Notice: dialog procedure
//
BOOL CALLBACK MainDlgProc (HWND hDlg,	// handle to dialog box
						   UINT uMsg,      // message
						   WPARAM wParam,  // first message parameter
						   LPARAM lParam ) // second message parameter
{
	static int bChecked = false;

	switch (uMsg) {

	case WM_INITDIALOG:
		::SetTimer( hDlg, 101, 300, NULL );
		return true;

	// if running more instances of HookInjEx, 
	// keep their interface consistent
	case WM_TIMER:
		bChecked = (IsDlgButtonChecked( hDlg, IDC_BUTTON ) == BST_CHECKED);
		if( g_bSubclassed && !bChecked) {
			::CheckDlgButton( hDlg, IDC_BUTTON, BST_CHECKED );
			::SetDlgItemText( hDlg, IDC_BUTTON, "卸载" );
		}
		else if (!g_bSubclassed && bChecked) {
			::CheckDlgButton( hDlg, IDC_BUTTON, BST_UNCHECKED );
			::SetDlgItemText( hDlg, IDC_BUTTON, "插入" );
		}
		break;		

	case WM_COMMAND:
		if( !g_bSubclassed) {
			InjectDll( hStart );
			if( g_bSubclassed ) 
				::SetDlgItemText( hDlg, IDC_BUTTON, "卸载" );
		}
		else {
			UnmapDll();
			if( !g_bSubclassed ) 
				::SetDlgItemText( hDlg, IDC_BUTTON, "插入" );
		}
		break;

	case WM_CLOSE:
		if( g_bSubclassed ) 
			UnmapDll();

		::EndDialog (hDlg, 0);
		break;		
	}

	return false;
}

