// DerverLoad.cpp: implementation of the DerverLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "DerverLoad.h"
#include <windows.h>
#include "resource.h"
#include "OpenMyFile.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DerverLoad::DerverLoad()
{

}

DerverLoad::~DerverLoad()
{

}
//////////////////////////////////////////////////////////////////////////
////用于创建服务
//////////////////////////////////////////////////////////////////////////
BOOL CreateSys(HWND hwnd)
{
	
	TCHAR szPath[MAX_PATH] = {0};
	
	GetDlgItemText(hwnd,IDC_SYSFILEPATH,szPath,sizeof(MAX_PATH));
	
	BOOL bRet = FALSE;
	
	SC_HANDLE hServiceMgr=NULL;//SCM管理器的句柄
	SC_HANDLE hServiceDDK=NULL;//NT驱动程序的服务句柄
	
	//打开服务控制管理器
	hServiceMgr = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
	
	if( hServiceMgr == NULL )  
	{
		//OpenSCManager失败
		MessageBox(NULL,"OpenSCManager() Faild  ! \n","OpenSCManager() Faild %d ! \n",MB_OK);
		bRet = FALSE;

	}
	else
	{
		////OpenSCManager成功
		bRet = TRUE;

	}
	
	//创建驱动所对应的服务
	hServiceDDK = CreateService( hServiceMgr,
		"rain", //驱动程序的在注册表中的名字  
		"rain", // 注册表驱动程序的 DisplayName 值  
		SERVICE_ALL_ACCESS, // 加载驱动程序的访问权限  
		SERVICE_KERNEL_DRIVER,// 表示加载的服务是驱动程序  
		SERVICE_DEMAND_START, // 注册表驱动程序的 Start 值  
		SERVICE_ERROR_IGNORE, // 注册表驱动程序的 ErrorControl 值  
		szPath, // 注册表驱动程序的 ImagePath 值  
		NULL,  
		NULL,  
		NULL,  
		NULL, NULL);  
	
	DWORD dwRtn;
	//判断服务是否失败
	if( hServiceDDK == NULL )  
	{  
		dwRtn = GetLastError();
		if( dwRtn != ERROR_IO_PENDING && dwRtn != ERROR_SERVICE_EXISTS )  
		{  
			//由于其他原因创建服务失败
			MessageBox(NULL,"创建失败 ! \n","提示",MB_OK);
			bRet = FALSE;
		}  
		else  
		{
			//服务创建失败，是由于服务已经创立过
			MessageBox(NULL,"已经创建过 ! \n","提示",MB_OK);
			bRet = TRUE;
		}
	} 
	else
	{
		bRet = TRUE;
		MessageBox(NULL,"创建成功！","提示",MB_OK);
	}

	if(hServiceDDK)
	{
		CloseServiceHandle(hServiceDDK);
	}
	
	if(hServiceMgr>0)
	{
		CloseServiceHandle(hServiceMgr);
	}

	return bRet;
}


VOID Start(HWND hwnd)
{
	SC_HANDLE hService=NULL;//NT驱动程序的服务句柄
	BOOL bRet;
	SC_HANDLE hSCM=NULL;//SCM管理器的句柄
	TCHAR szPath[MAX_PATH] = {0};
	
	GetDlgItemText(hwnd,IDC_SYSFILEPATH,szPath,sizeof(MAX_PATH));
	
	//打开服务控制管理器
	hSCM = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
	
	//打开对应的服务
	hService = OpenService( hSCM, "rain", SERVICE_ALL_ACCESS );  
	
	
	//开启此项服务
	bRet= StartService( hService, NULL, NULL );  
	if( !bRet )  //开启服务不成功
	{  
		MessageBox(NULL,"服务可能已经开启  ! \n","提示\n",MB_OK);
	}
	else
	{
		MessageBox(NULL,"开启成功 ! \n","提示",MB_OK);
	}

	if(hService)
	{
		CloseServiceHandle(hService);
	}

	if(hSCM>0)
	{
		CloseServiceHandle(hSCM);
	}
}

BOOL CloseSys( char * szSvrName)
{
	//一定义所用到的变量
	BOOL bRet = FALSE;
	SC_HANDLE hSCM=NULL;//SCM管理器的句柄,用来存放OpenSCManager的返回值
	SC_HANDLE hService=NULL;//NT驱动程序的服务句柄，用来存放OpenService的返回值
	SERVICE_STATUS SvrSta;
	//二打开SCM管理器
	hSCM = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );  
	if( hSCM == NULL )  
	{
		//带开SCM管理器失败
		bRet = FALSE;
		goto BeforeLeave;
	}  
	//三打开驱动所对应的服务
	hService = OpenService( hSCM, szSvrName, SERVICE_ALL_ACCESS );  
	
	if( hService == NULL )  
	{
		bRet = FALSE;
		goto BeforeLeave;
	}  

	//四停止驱动程序，如果停止失败，只有重新启动才能，再动态加载。  
	if( !ControlService( hService, SERVICE_CONTROL_STOP , &SvrSta ) )  
	{  
		MessageBox(NULL,"停止服务失败!","提示",MB_OK);
	}  
	else  
	{
		//停止驱动程序成功
		MessageBox(NULL,"停止服务成功!","提示",MB_OK);
	}  
	
	bRet = TRUE;
	//六 离开前关闭打开的句柄
BeforeLeave:
	if(hService>0)
	{
		CloseServiceHandle(hService);
	}
	if(hSCM>0)
	{
		CloseServiceHandle(hSCM);
	}
	return bRet;	
}

//卸载驱动程序  
BOOL UnLoadSys( char * szSvrName )  
{
	//一定义所用到的变量
	BOOL bRet = FALSE;
	SC_HANDLE hSCM=NULL;//SCM管理器的句柄,用来存放OpenSCManager的返回值
	SC_HANDLE hService=NULL;//NT驱动程序的服务句柄，用来存放OpenService的返回值
	SERVICE_STATUS SvrSta;
	//二打开SCM管理器
	hSCM = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );  
	if( hSCM == NULL )  
	{
		//带开SCM管理器失败
		bRet = FALSE;
		goto BeforeLeave;
	}  
	//三打开驱动所对应的服务
	hService = OpenService( hSCM, szSvrName, SERVICE_ALL_ACCESS );  
	
	if( hService == NULL )  
	{
		bRet = FALSE;
		goto BeforeLeave;
	}  
	else  
	{  
		//TRACE( "OpenService() ok ! \n" );  //打开驱动所对应的服务 成功
	}  
	//四停止驱动程序，如果停止失败，只有重新启动才能，再动态加载。  
	if( !ControlService( hService, SERVICE_CONTROL_STOP , &SvrSta ) )  
	{  
	
	}  
 
	//五动态卸载驱动服务。  
	if( !DeleteService( hService ) )  //TRUE//FALSE
	{
		//卸载失败
		MessageBox(NULL,"卸载服务失败!","提示",MB_OK);
	}  
	else  
	{  
		//卸载成功
		MessageBox(NULL,"卸载服务成功!","提示",MB_OK);
		
	}  
	bRet = TRUE;
	//六 离开前关闭打开的句柄
BeforeLeave:
	if(hService>0)
	{
		CloseServiceHandle(hService);
	}
	if(hSCM>0)
	{
		CloseServiceHandle(hSCM);
	}
	return bRet;	
} 


BOOL WINAPI DerverLoad::RainSysMain_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
		{
    		case WM_INITDIALOG:
					//加载函数
		
				return TRUE;
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
void DerverLoad::CommandMg(int id,HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch(id)
	{
		case IDC_SYS_BLOAD:
			{
				OpenMyFile open;
				open.lpMystrFilter = TEXT("SYS驱动\0*.sys\0\0");
				open.lpMystrTitle = TEXT("打开驱动");
				BOOL fal = open.OpenFileDlls(hwnd,(HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),IDC_SYSFILEPATH);  //打开程序	
				
				if(fal)
				{
					EnableWindow(GetDlgItem(hwnd,ID_SYS_LOAD),1);
				}
			
			
			}
			break;
		case ID_SYS_LOAD:
			{
				BOOL fal = CreateSys(hwnd);
				if(fal)
				{
					EnableWindow(GetDlgItem(hwnd,ID_SYS_LOAD),0);
					EnableWindow(GetDlgItem(hwnd,IDC_SYS_START),1);
					EnableWindow(GetDlgItem(hwnd,IDC_SYS_CLOSE),0);
					EnableWindow(GetDlgItem(hwnd,ID_SYS_UNLOAD),1);
				
				}
			}
			break;
		case IDC_SYS_START:
			{
				Start(hwnd);
				EnableWindow(GetDlgItem(hwnd,ID_SYS_LOAD),0);
				EnableWindow(GetDlgItem(hwnd,IDC_SYS_START),0);
				EnableWindow(GetDlgItem(hwnd,IDC_SYS_CLOSE),1);
				EnableWindow(GetDlgItem(hwnd,ID_SYS_UNLOAD),1);
			}
			break;
		case IDC_SYS_CLOSE:   //关闭服务
			{
				CloseSys("rain");
				EnableWindow(GetDlgItem(hwnd,ID_SYS_LOAD),1);
				EnableWindow(GetDlgItem(hwnd,IDC_SYS_START),1);
				EnableWindow(GetDlgItem(hwnd,IDC_SYS_CLOSE),0);
				EnableWindow(GetDlgItem(hwnd,ID_SYS_UNLOAD),1);
			}
			break;
		case ID_SYS_UNLOAD:
			{
				UnLoadSys("rain");
				EnableWindow(GetDlgItem(hwnd,ID_SYS_LOAD),0);
				EnableWindow(GetDlgItem(hwnd,IDC_SYS_START),0);
				EnableWindow(GetDlgItem(hwnd,IDC_SYS_CLOSE),0);
				EnableWindow(GetDlgItem(hwnd,ID_SYS_UNLOAD),0);
			}
			break;
	}
}