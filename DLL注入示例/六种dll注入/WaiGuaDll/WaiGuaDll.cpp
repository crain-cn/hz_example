// WaiGuaDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#ifdef __cplusplus
extern "C"
{
#endif	

__declspec (dllexport) void InjectFunc(void);

#ifdef __cplusplus
}
#endif
 void InjectFunc(void)
 {
	  MessageBoxA(NULL, "Dll Inject Success", "Dll Inject", MB_OKCANCEL);
 }
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
		   MessageBoxA(NULL, "inject success", "Dll Inject", MB_OKCANCEL);
			
		}
		break;
	}
	return TRUE;

}

