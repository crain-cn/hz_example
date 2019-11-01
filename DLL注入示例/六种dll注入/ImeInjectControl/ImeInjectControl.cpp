// ImeInjectControl.cpp : Defines the entry point for the console application.

#include "stdio.h"
#include "stdafx.h"
#pragma comment(lib, "ImeDllLoader.lib")

BOOL SetupIME(LPCTSTR lpImePath,LPCTSTR lpInjectDll);

int main(int argc, char* argv[])
{
	CHAR szImeBuf[MAX_PATH] = {0};
	CHAR szInjectDll[MAX_PATH] = {0};
	printf("输入ime文件的路径:");
	scanf("%s", szImeBuf);
	printf("输入待注入dll文件的路径:");
	scanf("%s", szInjectDll);
	SetupIME(szImeBuf,szInjectDll);
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
	printf("copy %s, %s\n", lpImePath, strSystemDir);	
	BOOL bCopySuccess = CopyFile(lpImePath,strSystemDir,false);
	if(!bCopySuccess)
	{
		printf("copy fail \n");
		return bSuccess;
	}

	
		
	//安装ime输入法文件
	HKL hImeFile = ImmInstallIME(strImeSetupPath, "winsun输入法");
	if( ImmIsIME(hImeFile) )
	{
		//安装成功
		bSuccess = true;
		printf("安装成功");
	}
	else
	{
		//安装失败
		//MessageBox(NULL, "安装失败", "安装输入法", MB_OKCANCEL);
		printf("安装失败");
	}
	return bSuccess;
}
