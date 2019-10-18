#ifndef _MAIN_H_3
#define _MAIN_H_3
#include <windows.h>
VOID CallUndll(HWND hWnd);
VOID CallCopyRow(HWND hWnd); //复制listbox
VOID CallCopyAllRow(HWND hWnd); //复制全部listbox
VOID CallCopyById(HWND hWnd,int id); //复制listview
VOID CallCopyByRow(HWND hWnd);   //复制listview
VOID CallCopyByAllRow(HWND hWnd);   //复制全部listview
#endif