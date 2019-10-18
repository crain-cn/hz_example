#include <windows.h>
#include "resource.h"
#include "myprocess.h"
#include "rightmenu.h"
#include <COMMCTRL.H>
#include <stdio.h>
#ifdef  UNICODE
#define MY_COPY CF_UNICODETEXT
#else
#define MY_COPY CF_TEXT
#endif

LPTSTR lpData = NULL;
HANDLE heap;
//////////////////////////////////////////////////////////////////////////
///获得当前的DLL
//////////////////////////////////////////////////////////////////////////
VOID CallUndll(HWND hWnd)
{
	TCHAR szDll[MAX_PATH] = {0},szFile[MAX_PATH] = {0};
	BOOL fal;
	HWND list1 = GetDlgItem(hWnd,IDC_LIST2);
	
	if(MessageBox(NULL,"确定要卸载DLL？","提示",MB_YESNO | MB_ICONQUESTION) != IDYES)
	{

		
		return;
	}


	int num = SendMessage(list1,LB_GETCURSEL,0,0);
	

	if(num == -1)
	{
		MessageBox(NULL,"请选择需要操作的对象!","提示",MB_OK);

		return;
	}
	//获得DLL
	SendMessage(list1,LB_GETTEXT,num,(LPARAM)szDll);
	ListView_GetItemText(GetDlgItem(hWnd,IDC_LIST3),ListView_GetSelectionMark(GetDlgItem(hWnd,IDC_LIST3)),2,szFile,sizeof(szFile)+1);

	fal = UnloadDll(atoi(szFile),szDll);
	if(fal)
	{
		MessageBox(NULL,"卸载DLL成功!","提示",MB_OK);
		SendMessage(list1,LB_DELETESTRING,num,0);
	}
	else
	{
		MessageBox(NULL,"卸载DLL失败!","提示",MB_OK);
	}

}
//////////////////////////////////////////////////////////////////////////
///复制当前行
//////////////////////////////////////////////////////////////////////////
VOID CallCopyRow(HWND hWnd)
{

	HGLOBAL buffer1;
	char *buffer;
	TCHAR szDll[MAX_PATH] ={0};
	HWND list1 = GetDlgItem(hWnd,IDC_LIST2);
	
	int num = SendMessage(list1,LB_GETCURSEL,0,0);
	

	if(num == -1)
	{
		MessageBox(NULL,"请选择需要操作的对象!","提示",MB_OK);

		return;
	}
	
	buffer1 = GlobalAlloc(GMEM_DDESHARE,MAX_PATH+1);
		
	buffer = (char*)GlobalLock(buffer1);
	
	SendMessage(list1,LB_GETTEXT,num,(LPARAM)szDll);
	
	//sprintf(szDll,"%s - By、Rain",szDll);
	strcpy(buffer,szDll);
	//获得DLL
	GlobalUnlock(buffer1);
	
	//lstrcpy(lpData,szDll);
	//打开剪切板
	if(OpenClipboard(NULL))
	{
		//设置剪切板内容
		EmptyClipboard();
	//	MessageBox(NULL,szDll,szDll,MB_OK);
		SetClipboardData(MY_COPY,buffer1);
		
	}
	CloseClipboard();
	/***
		if(OpenClipboard(NULL))
	{
		LPTSTR t1 =  GetClipboardData(MY_COPY);
		MessageBox(NULL,t1,t1,MB_OK);
	}
	CloseClipboard();
	***/
}

//////////////////////////////////////////////////////////////////////////
///复制当前全部行
//////////////////////////////////////////////////////////////////////////
VOID CallCopyAllRow(HWND hWnd)
{

	HGLOBAL buffer1;
	char *buffer,*b,*b1; 

	TCHAR szDll[MAX_PATH] ={0},szFile[8000]={0};
	int max = 0;
	HWND list1 = GetDlgItem(hWnd,IDC_LIST2);
	int i = 0;
	//获得全部行数
	int count = SendMessage(list1,LB_GETCOUNT,0,0);
	
	for (;i < count;i++)
	{
		max += MAX_PATH;
	

		ZeroMemory(szDll,sizeof(szDll));	
		SendMessage(list1,LB_GETTEXT,i,(LPARAM)szDll);
		if(i == 0)
		{
			b1 =(char*)malloc(max);
			sprintf(b1,"%s",szDll);
		}
		else
		{
			
			b = (char*)malloc(sizeof(b1));
			b = b1;
			b1 =(char*)malloc(max);
			
			sprintf(b1,"%s\r\n%s",b,szDll);
		}
		
	}

	
	buffer1 = GlobalAlloc(GMEM_DDESHARE,max+1);
		
	buffer = (char*)GlobalLock(buffer1);
	
	
	
	strcpy(buffer,b1);
	//获得DLL
	GlobalUnlock(buffer1);
	
	//打开剪切板
	if(OpenClipboard(NULL))
	{
		//设置剪切板内容
		EmptyClipboard();
		SetClipboardData(MY_COPY,buffer1);
		
	}
	CloseClipboard();

}

//////////////////////////////////////////////////////////////////////////
///复制Listview
//////////////////////////////////////////////////////////////////////////
VOID CallCopyById(HWND hWnd,int id)
{

	HGLOBAL buffer1;
	char *buffer;
	TCHAR szFile[125] = {0};
	HWND hwnd1 = GetDlgItem(hWnd,IDC_LIST3);
	int num = ListView_GetSelectionMark(hwnd1);
	
	if(num == -1)
	{
		MessageBox(NULL,"请选择需要操作的对象!","提示",MB_OK);

		return;
	}
	ListView_GetItemText(hwnd1,num,id,szFile,sizeof(szFile)+1);

	buffer1 = GlobalAlloc(GMEM_DDESHARE,MAX_PATH+1);	
	buffer = (char*)GlobalLock(buffer1);
	

	strcpy(buffer,szFile);

	GlobalUnlock(buffer1);
	

	//打开剪切板
	if(OpenClipboard(NULL))
	{
		//设置剪切板内容
		EmptyClipboard();

		SetClipboardData(MY_COPY,buffer1);
		
	}
	CloseClipboard();	
}

//////////////////////////////////////////////////////////////////////////
///复制Listview当前行
//////////////////////////////////////////////////////////////////////////
VOID CallCopyByRow(HWND hWnd)
{

	HGLOBAL buffer1;
	char *buffer; 
	TCHAR szFile[500]={0},s1[MAX_PATH] ={0},s2[MAX_PATH] ={0},s3[MAX_PATH] ={0},s4[MAX_PATH] ={0};

	HWND hwnd1 = GetDlgItem(hWnd,IDC_LIST3);
	int num = ListView_GetSelectionMark(hwnd1);
	if(num == -1)
	{
		MessageBox(NULL,"请选择需要操作的对象!","提示",MB_OK);

		return;
	}
	//获得当前行
	ListView_GetItemText(hwnd1,num,0,s1,sizeof(s1)+1);
	ListView_GetItemText(hwnd1,num,1,s2,sizeof(s2)+1);
	ListView_GetItemText(hwnd1,num,2,s3,sizeof(s3)+1);
	ListView_GetItemText(hwnd1,num,3,s4,sizeof(s4)+1);
	
	sprintf(szFile,"%s\t%s\t%s\t%s",s1,s2,s3,s4);

	buffer1 = GlobalAlloc(GMEM_DDESHARE,sizeof(szFile) + 1);
		
	buffer = (char*)GlobalLock(buffer1);
	
	
	
	strcpy(buffer,szFile);
	//获得DLL
	GlobalUnlock(buffer1);
	
	//打开剪切板
	if(OpenClipboard(NULL))
	{
		//设置剪切板内容
		EmptyClipboard();
		SetClipboardData(MY_COPY,buffer1);
		
	}
	CloseClipboard();

}

//////////////////////////////////////////////////////////////////////////
///复制Listview当前行
//////////////////////////////////////////////////////////////////////////
VOID CallCopyByAllRow(HWND hWnd)
{

	HGLOBAL buffer1;
	char *buffer,*szFile,*b1; 
	TCHAR s1[100] ={0},s2[100] ={0},s3[100] ={0},s4[100] ={0};

	int max = 0;
	int i = 0;
	HWND hwnd1 = GetDlgItem(hWnd,IDC_LIST3);
	
	//获得全部行数
	int count = ListView_GetItemCount(hwnd1);
	
	for (;i < count;i++)
	{
		max += (100 + 20)*4 ;
		ZeroMemory(s1,sizeof(s1));	
		ZeroMemory(s2,sizeof(s2));
		ZeroMemory(s3,sizeof(s3));
		ZeroMemory(s4,sizeof(s4));

		ListView_GetItemText(hwnd1,i,0,s1,sizeof(s1)+1);
		ListView_GetItemText(hwnd1,i,1,s2,sizeof(s2)+1);
		ListView_GetItemText(hwnd1,i,2,s3,sizeof(s3)+1);
		ListView_GetItemText(hwnd1,i,3,s4,sizeof(s4)+1);
	
		if(i == 0)
		{
			szFile =(char*)malloc(max);
			sprintf(szFile,"进程:%s\t父进程:%s\t进程ID:%s\t线程:%s",s1,s2,s3,s4);
		}
		else
		{
			b1 =(char*)malloc(sizeof(szFile));
			b1 = szFile;
			szFile =(char*)malloc(max);
			sprintf(szFile,"%s\r\n进程:%s\t父进程:%s\t进程ID:%s\t线程:%s",b1,s1,s2,s3,s4);
		}
		
	}

	
	buffer1 = GlobalAlloc(GMEM_DDESHARE,max+1);
		
	buffer = (char*)GlobalLock(buffer1);
	
	
	
	strcpy(buffer,szFile);
	//获得DLL
	GlobalUnlock(buffer1);
	
	//打开剪切板
	if(OpenClipboard(NULL))
	{
		//设置剪切板内容
		EmptyClipboard();
		SetClipboardData(MY_COPY,buffer1);
		
	}
	CloseClipboard();

}
