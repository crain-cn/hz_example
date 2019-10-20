// demo1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"   
#include <windows.h> 
#include <conio.h>

//阳光基地址
#define SUNNY_NUMBER_ADDR	0x006A9EC0

//金币基地址
#define MONEY_NUMBER_ADDR	0x006A9EC0

/**
* 修改阳光方法
*/
void change_sunny_number(HANDLE hProcess)
{
	DWORD sunny; 
	
	DWORD baseAddr = SUNNY_NUMBER_ADDR;
	DWORD stackAddr;
	DWORD dataAdrr;

	////阳光基址读取读基地址
	ReadProcessMemory (hProcess,(void *)baseAddr,&stackAddr,4,0);      	
	printf("\n一级偏移基地址： 0x%x\n",stackAddr);

	//阳光基址 + 一级偏移 = 一级基址
	stackAddr = stackAddr + 0x768 ;
	printf("\n一级基地址： 0x%x\n",stackAddr);

	//读二级偏移基地址
	ReadProcessMemory(hProcess,(void *)stackAddr,&dataAdrr,4,0);		
	printf("\n一级偏移基地址： 0x%x\n",dataAdrr);

	//二级偏移 + 二级偏移 = 阳光地址
	dataAdrr = dataAdrr + 0x5560 ;
	printf("\n二级基地址： 0x%x\n",dataAdrr);

	//写入阳光
	printf("\n您需要多少阳光？：");
	scanf_s("%d",&sunny);
	DWORD res = WriteProcessMemory(hProcess, (void *)dataAdrr, &sunny, 4, 0);	

	if ( res == NULL )
	{
		printf("\n修改失败\n");
	}
	else
	{
		printf("\n修改成功\n");	
	}
	
}

/**
*  修改金币
*/
void change_money_number(HANDLE hProcess)
{
	DWORD money;
	DWORD baseAddr =  MONEY_NUMBER_ADDR,stackAddr,dataAdrr;
	
	//金币基址读取基地址
	ReadProcessMemory (hProcess,(void *)baseAddr,&stackAddr,4,0);


	//一级偏移82C地址读取二级偏移基地址
	stackAddr = stackAddr + 0x82C ;
	ReadProcessMemory(hProcess,(void *)stackAddr,&dataAdrr,4,0); 



	//写入金币内存
	printf("\n您需要多少金币？：");
	scanf_s("%ld",&money); 
	dataAdrr = dataAdrr + 0x28 ; 
	DWORD res = WriteProcessMemory(hProcess,(void *)dataAdrr,&money,4,0); 

	if ( res == NULL )
	{
		printf("\n修改失败\n");
	}		
	else
	{
		printf("\n修改成功\n");
	} 

}


int main(void)
{
	
	DWORD Pid;			//进程PID
	HANDLE hProcess=0;  //进程句柄

	 //获得窗口句柄
	HWND hWnd = ::FindWindow(NULL,TEXT("植物大战僵尸中文版"));   
	if( hWnd == NULL )	
	{
		printf("\n未发现游戏进程 请先运行游戏\n");
	}
	else if ( hWnd !=  NULL )
	{
		//获得进程pid
		GetWindowThreadProcessId(hWnd,&Pid);									 
		
		//打开进程 获取所有操作权限
		hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,Pid);
		if ( hProcess == NULL )
		{	
			printf("\n打开游戏进程失败\n");
			_getch();
			return -1;
		}
		else
		{
			printf("\n成功打开游戏进程,窗口句柄：0x%x,进程PID：%d\n",hWnd,Pid);
		}
		
		
		change_sunny_number(hProcess);	//修改阳光

		change_money_number(hProcess);	//修改金币

    }
	_getch();
	return 0;
}
