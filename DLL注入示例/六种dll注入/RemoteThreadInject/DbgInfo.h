#ifndef _MYDBG_H_
#define _MYDBG_H_

#ifdef __cplusplus
extern "C" {
#endif
	
	//typedef BOOL           BOOL;
	typedef unsigned long  DWORD;
	typedef DWORD*         PDWORD;
	typedef unsigned long  ULONG;
	typedef unsigned short WORD;
	typedef unsigned char  BYTE;
	
	//
	//Windows版本
	//
#define WIN_ERROR 0x0
#define WIN_XP    0x00000001 
#define WIN_2K    0x00000010
#define WIN_OTHER 0x00000100
	
	//
	//调试选择
	//
#define _DEBUG_
#ifdef _DEBUG_
	
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdarg.h>
#include <ASSERT.H>
	
	void UsageHelpInfo(void);
	void SelectInjectMethod(void);
	
	void    MyDbgPrint(char *fmt, ...);
	
#define PRT(arg)     MyDbgPrint arg
#define ASSERT(arg)  assert(arg)    //This definition require no comma is in the expression
	
#else
	
#define PRT(arg)
#define ASSERT(arg)
	//#define DbgPrint(arg)
	
#endif
	
	//
	//返回Windows版本
	//
	ULONG GetWindowsVersion();
	
	
#ifdef __cplusplus
}
#endif

#endif 
