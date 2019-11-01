// ImeInjectControl.cpp : Defines the entry point for the console application.

#include "stdio.h"
#include "pipe.h"
//#pragma comment(lib, "ImeDllLoader.lib")

HANDLE g_hEvent = NULL;
HANDLE g_hNotifyEvent = NULL;

BOOL SetupIME(LPCTSTR lpImePath,LPCTSTR lpInjectDll);
DWORD WINAPI PipeServerThread(	LPVOID lpThreadID);
int main(int argc, char* argv[])
{
	CHAR szImeBuf[MAX_PATH] = {0};
	CHAR szInjectDll[MAX_PATH] = {0};
	CHAR szSetup[5]={0};
	CHAR szSelect[5]={0};


	printf("是否已经安装外挂输入法:\"YES\" or \"NO\" :");
	scanf("%s", szSetup);

	if (stricmp(szSetup, "no") == 0)
	{
		printf("输入ime文件的路径:");
		scanf("%s", szImeBuf);
	}

	printf("输入待注入dll文件的路径:");
	scanf("%s", szInjectDll);
	
	
	g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if ( g_hEvent == NULL)
	{
		printf("main CreateEvent fail! \n");
		return -1;
	}

	g_hNotifyEvent = CreateEvent(NULL, FALSE, FALSE, "WinsunEvent");
	if (g_hNotifyEvent == NULL)
	{
		OutputDebugStr ("main Failed to create named event");
		return -1;
	}
		
	
	//创建管道服务器线程
	HANDLE	hNewThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)PipeServerThread, NULL, NULL, NULL);
	if ( !hNewThread )
	{
             OutputDebugStr("[!] SetupIME CreateThread error\n");
			 return FALSE;
	}

	if (stricmp(szSetup, "no") == 0)
	{
		SetupIME(szImeBuf,szInjectDll);
	}
	


	while (TRUE)
	{
		printf("\n卸载或加载注入的dll,\"uload\" or \"load\" : ");
		scanf("%s", szSelect);
		if(stricmp(szSelect, "uload") == 0)
		{
			//通知输入法加载器卸载注入的dll
			//初始化管道需要传递的信息
			PIPE_COMMUNICATION stPipeInfo = {0};
			stPipeInfo.Cmd = 2;
			SetPipeInfo(&stPipeInfo);
			SetEvent(g_hEvent);
		}
		else if(stricmp(szSelect, "load") == 0)
		{
			//初始化管道需要传递的信息
			PIPE_COMMUNICATION stPipeInfo = {0};
			stPipeInfo.Cmd = 1;
			strcpy(stPipeInfo.DLLString, szInjectDll);
			SetPipeInfo(&stPipeInfo);
			SetEvent(g_hEvent);
		}
		else
		{
			//初始化管道需要传递的信息
			PIPE_COMMUNICATION stPipeInfo = {0};
			stPipeInfo.Cmd = 3;
			SetPipeInfo(&stPipeInfo);
			SetEvent(g_hEvent);
		}
	}

	return 0;
}

BOOL SetupIME(LPCTSTR lpImePath, LPCTSTR lpInjectDll)
{
	BOOL bSuccess = FALSE;
	LPSTR lpPosition = NULL;
	CHAR strSystemDir[MAX_PATH] = {0};
	CHAR strImeSetupPath[MAX_PATH] = {0};
	GetSystemDirectory(strSystemDir, MAX_PATH);

	if (lpImePath == NULL || lpInjectDll == NULL)
	{
		return bSuccess;
	}

	lpPosition = strrchr(lpImePath, '\\');
	strcat(strSystemDir, "\\");
	strcat(strSystemDir, ++lpPosition);

		

	//ime输入法文件放入系统目录下
//	printf("copy %s, %s\n", lpImePath, strSystemDir);	
	BOOL bCopySuccess = CopyFile(lpImePath,strSystemDir,false);
	if(!bCopySuccess)
	{
		printf("copy fail \n");
		return bSuccess;
	}

	//初始化管道需要传递的信息
// 	PIPE_COMMUNICATION stPipeInfo = {0};
// 	stPipeInfo.Cmd = 1;
// 	strcpy(stPipeInfo.DLLString,lpInjectDll); 
// 	SetPipeInfo(&stPipeInfo);


	
		
	//安装ime输入法文件
	HKL hImeFile = ImmInstallIME(strSystemDir, "外挂输入法");
	if( ImmIsIME(hImeFile) )
	{
		//安装成功
		bSuccess = true;
		printf("输入法安装成功");
	}
	else
	{
		//安装失败
		//MessageBox(NULL, "安装失败", "安装输入法", MB_OKCANCEL);
		
		printf("输入法安装失败 %d",GetLastError());
	}
	return bSuccess;
}

DWORD WINAPI PipeServerThread(
						LPVOID lpThreadID
					)
{

	PipeServer("\\\\.\\pipe\\winsun_ime_load_dll",g_hEvent);
	return 1;
}
