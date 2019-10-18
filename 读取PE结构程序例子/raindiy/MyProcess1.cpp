// MyProcess1.cpp: implementation of the MyProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyProcess1.h"
#include <windows.h>
#include <stdio.h>
#include "resource.h"
#include <commctrl.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define BUFSIZE 1024  

MyProcess::MyProcess()
{

}

MyProcess::~MyProcess()
{

}
void MyProcess::AddDriverInfo(HWND list)
{
	/***
	
	TCHAR szLogicalDriveStrings[BUFSIZE];  
	PCHAR szDrive;  
	TCHAR szD[30] = {0};
    ZeroMemory(szLogicalDriveStrings,BUFSIZE);  
	// 获取逻辑驱动器卷标名  
    GetLogicalDriveStrings(BUFSIZE - 1,szLogicalDriveStrings);    
    szDrive = (PCHAR)szLogicalDriveStrings;  
    // 循环处理每个卷  
    do  
    {  
		SendMessage(list,CB_ADDSTRING,0,(LPARAM)szDrive);

		szDrive += (lstrlen(szDrive)+1);  
	}  
    while(*szDrive!='/x00');
	*/  
	char dc = 'A';
	DWORD dw = GetLogicalDrives();
	TCHAR szD[30] = {0};
	
	while(dw != 0)
	 {
		if((dw&1) != 0)
		{
			sprintf(szD,"%c:\\",dc);
			SendMessage(list,CB_ADDSTRING,0,(LPARAM)szD);
		}
		dc++;
		dw >>= 1;
	 }
}

void MyProcess::SetDeiverTextInfo(HWND ltext,LPSTR lpName)
{
	 
	    UINT DType = GetDriveType(lpName);
		unsigned _int64 i64FreeBytesToCaller;
		unsigned _int64 i64TotalBytes;
		unsigned _int64 i64FreeBytes;
		
		TCHAR info[1024]= {0},type[30] = {0};
         //GetDriveType函数，可以获取驱动器类型，参数为驱动器的根目录
        if(DType == DRIVE_FIXED)
        {
			sprintf(type,"硬盘");
        }
        else if(DType == DRIVE_CDROM)
        {
			sprintf(type,"光驱");
        }
        else if(DType == DRIVE_REMOVABLE)
        {
			sprintf(type,"可移动式磁盘");
        }
        else if(DType == DRIVE_REMOTE)
        {
			sprintf(type,"网络磁盘");
        }
        else if(DType == DRIVE_RAMDISK)
        {
			sprintf(type,"虚拟RAM磁盘");
        }
        else if (DType == DRIVE_UNKNOWN)
        {
			sprintf(type,"未知设备");
        }
	 
		//GetDiskFreeSpaceEx函数，可以获取驱动器磁盘的空间状态,函数返回的是个BOOL类型数据

		 BOOL fResult = GetDiskFreeSpaceEx (

                               lpName,

                               (PULARGE_INTEGER)&i64FreeBytesToCaller,

                               (PULARGE_INTEGER)&i64TotalBytes,

                               (PULARGE_INTEGER)&i64FreeBytes);

     

        if(fResult)//通过返回的BOOL数据判断驱动器是否在工作状态

        {
			sprintf(info,"磁盘类型：%s\r\t磁盘大小：%d MB\r\t已使用：%d MB",type,((__int64)i64TotalBytes/1024/1024),((__int64)i64FreeBytesToCaller /1024/1024));
		} 
		else
		{

		}
		SetWindowText(ltext,info);

}

int dir,int sum;

void MyProcess::findFile(char filePath[],HWND lhwnd)//这个是你要的函数
{
char szFind[MAX_PATH] = {0};//这是要找的
WIN32_FIND_DATA FindFileData;
HANDLE hFind;
char szFile[3000]={0};
TCHAR lFile[MAX_PATH] = {0};
TCHAR info[MAX_PATH] = {0};
strcpy(szFind,filePath);
strcat(szFind,"//*.*");//应用通配符找这个目录下的所以文件，包括目录

hFind=FindFirstFile(szFind,&FindFileData);
if(INVALID_HANDLE_VALUE == hFind) return;

while(TRUE)
{

	if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//这是目录
	{
		if(FindFileData.cFileName[0]!='.')//.表示当前目录，由于每个目录下面都有两个默许目录就是..和.分别表示上一级目录和当前目录
		{
			strcpy(szFile,filePath);
			strcat(szFile,"//");
			strcat(szFile,FindFileData.cFileName);
			findFile(szFile,lhwnd);//寻觅这个目录下面的文件
		}
		dir++;
	}
	else
	{
		fprintf(stdout,"%s//%s/n",filePath,FindFileData.cFileName);//打印出目录下的文件的途径和称号
		sprintf(lFile,"%s//%s",filePath,FindFileData.cFileName);
		SetWindowText(lhwnd,lFile);
		sum++;
	
	}
	SendMessage(GetDlgItem(GetParent(lhwnd),IDC_PROGRESS1),PBM_SETSTEP,1,0);
				
	SendMessage(GetDlgItem(GetParent(lhwnd),IDC_PROGRESS1),PBM_STEPIT,0,0);
	sprintf(info,"文件总数：%d   文件夹：%d    文件: %d ",(dir+sum),dir,sum);
	SetWindowText(GetDlgItem(GetParent(lhwnd),IDC_FILE_SUM),info);

	
if(!FindNextFile(hFind,&FindFileData))//寻觅下一个文件
{
	break;
}


}
FindClose(hFind);//关闭句柄
}
