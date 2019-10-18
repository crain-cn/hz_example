//file:SDTShadowRestore.h

#ifndef SDTSHADOWRESTORE_H

#define SDTSHADOWRESTORE_H

#include <windows.h>
#include <Tchar.h>

typedef struct _SYSTEM_SERVICE_TABLE 
{ 
   PVOID   ServiceTableBase; 
   PULONG   ServiceCounterTableBase; 
   ULONG   NumberOfService; 
   ULONG   ParamTableBase; 
}SYSTEM_SERVICE_TABLE,*PSYSTEM_SERVICE_TABLE;

typedef struct _SERVICE_DESCRIPTOR_TABLE
{
  PVOID KiServiceTabe;
  PVOID W32pServiceTable;
  PVOID Reserved_1;
  PVOID Reserved_2;
}SERVICE_DESCRIPTOR_TABLE,*PSERVICE_DESCRIPTOR_TABLE;


class SDTShadowRestore
{
public:
  SDTShadowRestore(void)
  {
    m_dwWin32kBase = 0;
    m_dwW32pServiceTable = 0;
    m_KeServiceDescriptorTableShadow = 0;
    //this->Init();
  }
  ~SDTShadowRestore(void)
  {
    if(m_pKernelName)
    {
      ::GlobalFree(m_pKernelName);
    }
  }

  void SetListShowSys(HWND hwnd);           //设置list的值，用于获取驱动和内核对象
private:
  void AnsiToPTSTR(PTSTR DesStr, char *SourceStr, DWORD cbDesStr);
  
private:
  PIMAGE_OPTIONAL_HEADER m_pWin32kOptionalHeader;           //可选头的地址，非RVA
  HMODULE m_hWin32kModule;              //自己加载的Win32k.sys内核模块的模块句柄
  LPTSTR m_pKernelName;           //内核核心模块名
  HMODULE m_hKernelModule;            //内核核心模块ntoskrnl.exe或者ntkrnlpa.exe
  DWORD m_dwKernelBase;         //内核基址
  DWORD m_dwWin32kBase;         //Win32k.sys基址
  PSERVICE_DESCRIPTOR_TABLE m_KeServiceDescriptorTableShadow;         //内核中SSDT Shadow的真实内存地址
  DWORD m_dwW32pServiceTable;      //原始W32pServiceTaable表真实地址
};

#endif   
