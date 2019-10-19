// example1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include "conio.h"	
#include <Windows.h>	//windows api 头

//枚举字窗口
BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam) 
{ 

    int i, idChild; 
    idChild = ::GetWindowLong(hwndChild, GWL_ID);
	printf("子窗口句柄：0x%x ,idChild: %d \n",hwndChild,idChild);
	
	::ShowWindow(hwndChild,SW_HIDE);

    return TRUE;
}



int main(int argc, _TCHAR* argv[])
{
	//查找窗口句柄
	HWND hWnd = ::FindWindow(NULL,_TEXT("计算器"));
	
	if (hWnd != 0) 
	{
		printf("主窗口句柄: 0x%x \n",hWnd);

		//枚举字窗口
		EnumChildWindows(hWnd, EnumChildProc, NULL); 

		//::CloseWindow(hWnd);
	} else {
		printf("没有找到窗口句柄\n");
	}
	

	getchar();
	return 0;
}

