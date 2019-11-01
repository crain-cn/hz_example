#ifndef _REMOTE_THREAD_INJECT_H_
#define _REMOTE_THREAD_INJECT_H_

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdarg.h>


#ifdef _cplusplus
extern "C"{
#endif


	//
	//各种注入方法接收的注入参数
	//
	typedef struct _INJECT_PARAM{
		
		TCHAR  strDllPath[MAX_PATH]; //injected Dll Path
		bool   bProcessName;         //bProcessName为假，则strProcess存放被注入进程的路径；否则相反。 
		TCHAR  strProcessName[MAX_PATH]; 
		bool   bInjectCode;           //bInjectCode = true,表示注入的是code，且放入cExtend中。
		DWORD  dwSize;               //该结构体的大小。
		DWORD  dwExtendLength;       //指出cExtend数组的长度
		char   cExtend[1];           //存放扩展信息，比如code等。
		
	}INJECT_PARAM, *PINJECT_PARAM;

	//
	//利用远线程注入
	//
	bool RemoteThreadInject(PINJECT_PARAM);
	
	
	
#ifdef _cplusplus
}
#endif
#endif