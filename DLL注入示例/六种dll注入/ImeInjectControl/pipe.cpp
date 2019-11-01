
#include "pipe.h"
#include "stdafx.h"

PIPE_COMMUNICATION g_stPipeInfo = {0};

void PipeServer(LPCSTR lpPipeName)
{
		HANDLE hPipe = 0;
		DWORD dwWritedBytes = 0;
		PIPE_COMMUNICATION stPipeInfo = {0};
		hPipe = CreateNamedPipeA (lpPipeName, PIPE_ACCESS_DUPLEX,
			 PIPE_TYPE_MESSAGE|PIPE_WAIT, 2, 0, 0, 0, NULL);
		if (hPipe == INVALID_HANDLE_VALUE) 
		{
			 //printf ("Failed to create named pipe:\n %s\n",pszPipeName);
			 return;
		}
		 
		//wait for client to connect
		ConnectNamedPipe (hPipe, NULL);
        while(TRUE)
		{
			GetPipeInfo(&stPipeInfo); 
			if (stPipeInfo.Cmd == 3)
			{
				Sleep(100);
				continue;
			}
			 WriteFile(hPipe,&stPipeInfo, sizeof(stPipeInfo), &dwWritedBytes, NULL);
		}
}

void PipeClient(LPCSTR lpPipeName)
{
	HANDLE hPipeClient = 0;
	DWORD  dwReadBytes = 0;
	HMODULE hDll = NULL;
	PIPE_COMMUNICATION stPipeCom={0};
	if( WaitNamedPipe(lpPipeName, NMPWAIT_WAIT_FOREVER) )
		 {
			 hPipeClient = CreateFile(
				 lpPipeName, 
				 GENERIC_READ | GENERIC_WRITE, 
				 FILE_SHARE_READ | FILE_SHARE_WRITE, 
				 NULL,
				 OPEN_EXISTING,
				 FILE_ATTRIBUTE_ARCHIVE | FILE_FLAG_WRITE_THROUGH,
				 NULL
				 );
			 if( INVALID_HANDLE_VALUE == hPipeClient )
			 {
				 OutputDebugStr("[XL] PipeClient CreateFile fail!\n");
				 return ;
			 }

			 while(TRUE)
			 {
				 ReadFile(hPipeClient, &stPipeCom, sizeof(PIPE_COMMUNICATION), &dwReadBytes, NULL);
				 switch(stPipeCom.Cmd)
				 {
					case 1:
						hDll = LoadLibrary(stPipeCom.DLLString);
					break;

					case 2:
						FreeLibrary(hDll);
					break;
				 }
				 Sleep(100);
			 }

		 }
}

void SetPipeInfo(PPIPE_COMMUNICATION pstPipeInfo)
{
	memcpy(&g_stPipeInfo, pstPipeInfo, sizeof(PIPE_COMMUNICATION));
}

void GetPipeInfo(PPIPE_COMMUNICATION pstPipeInfo)
{
	memcpy(pstPipeInfo, &g_stPipeInfo, sizeof(PIPE_COMMUNICATION));
}

