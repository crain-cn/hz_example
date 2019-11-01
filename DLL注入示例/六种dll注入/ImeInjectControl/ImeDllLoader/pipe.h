#ifndef _PIPE_H_
#define _PIPE_H_
#include <windows.h>

void PipeServer(LPCSTR lpPipeName);
void PipeClient(LPCSTR lpPipeName);



typedef struct _PIPE_COMMUNICATION
{
	DWORD Cmd;             //==1,load;==2,unload; ==3,wait
	DWORD CallBackData1;
	DWORD CallBackData2;
	DWORD CallBackData3;
	DWORD OnloadDllWhenExit;    // 当输入法退出时是否卸载客户DLL  0-是，1-否
	DWORD LoadNextWhenActive;    // 当本输入法激活时，是否自动打开下一个输入法 0-否，1-是
	char  DLLString[256];

}PIPE_COMMUNICATION,*PPIPE_COMMUNICATION;

void SetPipeInfo(PPIPE_COMMUNICATION pstPipeInfo);
void GetPipeInfo(PPIPE_COMMUNICATION pstPipeInfo);

#endif