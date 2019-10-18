// SDTShadowRestore.cpp: implementation of the SDTShadowRestore class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SDTShadowRestore.h"

typedef struct _SYSTEM_MODULE_INFORMATION  // Information Class 11
{
  ULONG  Reserved[2];  //+0
  PVOID  Base;         //+08h
  ULONG  Size;         //+0ch
  ULONG  Flags;        //+10h
  USHORT Index;        //+14h
  USHORT Unknown;      //+16h
  USHORT LoadCount;    //+18h
  USHORT ModuleNameOffset; //+1Ah
  CHAR   ImageName[256];   //+1Ch
} SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;



typedef struct _tagSysModuleList 
{
  ULONG ulCount;
  SYSTEM_MODULE_INFORMATION smi;
} SYSMODULELIST, *PSYSMODULELIST;


typedef DWORD SYSTEM_INFORMATION_CLASS;

#define   STATUS_INFO_LEN_MISMATCH   0xc0000004

typedef LONG (_stdcall *pFnZwQuerySystemInformation ) 
( IN SYSTEM_INFORMATION_CLASS SystemInformationClass, 
 IN OUT PVOID SystemInformation, 
 IN ULONG SystemInformationLength, 
 OUT PULONG ReturnLength  );

void SDTShadowRestore::AnsiToPTSTR(PTSTR DesStr, char *SourceStr, DWORD cbDesStr)
{
#ifndef _UNICODE
  lstrcpy(DesStr, SourceStr);
#else
  MultiByteToWideChar(CP_ACP, 0, SourceStr, -1, DesStr, cbDesStr);
#endif
}
//////////////////////////////////////////////////////////////////////////
/// 用于遍历所有内核信息
///  hwnd  listbox的
//////////////////////////////////////////////////////////////////////////
void SDTShadowRestore::SetListShowSys(HWND hwnd)
{
  pFnZwQuerySystemInformation ZwQuerySystemInformation = (pFnZwQuerySystemInformation)GetProcAddress(LoadLibrary("ntdll.dll"), "ZwQuerySystemInformation");
  PSYSMODULELIST pSysModuleList = NULL;
  DWORD ReturnLength = 0, dwRet = 0;
  TCHAR ModuleName[MAX_PATH];
  dwRet = ZwQuerySystemInformation(11, (PVOID)pSysModuleList, 0, &ReturnLength);
  if(dwRet == STATUS_INFO_LEN_MISMATCH)
  {
    pSysModuleList = (PSYSMODULELIST)GlobalAlloc(GPTR, ReturnLength);
    ZwQuerySystemInformation(11, (PVOID)pSysModuleList, ReturnLength, NULL);            //获取系统加载模块信息
    PSYSTEM_MODULE_INFORMATION pSystemModuleInformation = &(pSysModuleList->smi);
 
    for(DWORD index = 0; index < pSysModuleList->ulCount; index++)               //通过循环获取所有加载的内核信息
    {
		SendMessage(hwnd,LB_ADDSTRING,0,(LPARAM)(pSystemModuleInformation->ImageName));
		pSystemModuleInformation++;
    }
    if(pSysModuleList)
    {
      GlobalFree(pSysModuleList);
    }	
  }
}
