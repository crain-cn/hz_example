#include "rainmain.h"
#include "rainpe.h"
#include <windows.h>
#include "resource.h"
#include "OpenMyFile.h"
#include "ReadPE.h"
#include <stdio.h>
ReadPE pe;
BOOL WINAPI RainPe::RainMain_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
		switch(uMsg)
		{
    		case WM_INITDIALOG:
					//加载函数
				return InitDiaLog(hWnd,uMsg,wParam,lParam);
   			case WM_COMMAND:
				{	
					CommandMg(LOWORD(wParam),hWnd,wParam,lParam);
				}
   				break;
	
			case WM_CLOSE:
				{
					pe.Full();
					EndDialog(hWnd,0);	
				}
				break;
		}

	return FALSE;	
}

BOOL RainPe::InitDiaLog(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	return TRUE;
}

/**  调用线程 **/
DWORD WINAPI ThreadProcPe( LPVOID lpParameter)
{
		
	HWND hwnd = (HWND)lpParameter;
		OpenMyFile open;
		open.lpMystrFilter = TEXT("EXE可执行文件\0*.exe\0DLL文件\0*.dll\0\0");
		open.lpMystrTitle = TEXT("打开文件");
		BOOL fal = open.OpenFileDlls(hwnd,(HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),IDC_ET_PE);  //打开程序	
		
		if(fal)
		{
			TCHAR filename[MAX_PATH] = {0};
			TCHAR pe_name[MAX_PATH] = {0};

			GetDlgItemText(hwnd,IDC_ET_PE,filename,sizeof(filename));
			
			pe.filename = filename; 
			if(pe.Init() == TRUE)
			{
				if(pe.SetPE())
				{
					
					//入口点
					itoa(pe.m_nt_header->entryPoint,pe_name,16);
					SetDlgItemText(hwnd,IDC_ENTRY,pe_name);
					
					//大小
					ZeroMemory(pe_name,sizeof(pe_name));		
					itoa(pe.m_nt_header->imageSize,pe_name,16);
					SetDlgItemText(hwnd,IDC_PE_SIZE,pe_name);
    
					//程序基地址
					ZeroMemory(pe_name,sizeof(pe_name));			
					itoa(pe.m_nt_header->imageBase,pe_name,16);
					SetDlgItemText(hwnd,IDC_PE_BASE,pe_name);

					ZeroMemory(pe_name,sizeof(pe_name));			
					itoa(pe.m_nt_header->sectionAlign,pe_name,16);
					SetDlgItemText(hwnd,IDC_PE_SECION,pe_name);

					ZeroMemory(pe_name,sizeof(pe_name));			
					itoa(pe.m_nt_header->fileAlign,pe_name,16);
					SetDlgItemText(hwnd,IDC_PE_FILE,pe_name);

					ZeroMemory(pe_name,sizeof(pe_name));			
					itoa(pe.m_nt_header->checksum,pe_name,16);
					SetDlgItemText(hwnd,IDC_PE_CHECKENUM,pe_name);


						int i;
						char *buffer,*szFile,*b1; 
						int max = 0;

						TCHAR sz[125] = {0};
						
					
					
						for (i=0; i< pe.m_pe_header->numSections; i++)
						{
							max += 125;
							
							if(i == 0)
							{
								szFile =(char*)malloc(max);
								sprintf(szFile,"%x----%x\r\n",pe.m_sections[i].dataOffset,pe.m_sections[i].dataAlignSize);
							}
							else
							{

									b1 =(char*)malloc(sizeof(szFile));
									b1 = szFile;
									szFile =(char*)malloc(max);
									sprintf(szFile,"%s%x----%x\r\n",b1,pe.m_sections[i].dataOffset,pe.m_sections[i].dataAlignSize);
							}
					
						}

						SetDlgItemText(hwnd,IDC_DATA_SECTION,szFile);
				}

			}
		}

	return 0;
}

void RainPe::CommandMg(int id,HWND hwnd,WPARAM wParam,LPARAM lParam)
{

	switch(id)
	{
		case IDC_OPEN_PE:
			{
					DWORD dwThreadId;
					CreateThread(NULL,0,ThreadProcPe,(LPVOID)hwnd,0,&dwThreadId);

				
									
			}
		break;
	}
}