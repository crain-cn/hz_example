// InjectDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
   
	switch(ul_reason_for_call)
    {
      case DLL_PROCESS_ATTACH:
		  MessageBox(NULL ,  "成功注入DLL", "输入法注入Dll", MB_OKCANCEL);
		 
		  break;
	  case DLL_THREAD_ATTACH:
		 break;

	  case DLL_THREAD_DETACH:
		 break;

      case DLL_PROCESS_DETACH:
		  MessageBox(NULL,"成功卸载DLL" ,"输入法注入Dll", MB_OKCANCEL);

        break;


      default:
        break;
    }
	return TRUE;
}

