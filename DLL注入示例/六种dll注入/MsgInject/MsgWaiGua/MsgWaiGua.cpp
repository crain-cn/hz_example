#include <windows.h>

#pragma data_seg(SHARD_SEG_NAME)
static HHOOK g_hhook;
#pragma data_seg()



BOOL  _stdcall DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved )
{
  if( ul_reason_for_call == DLL_PROCESS_ATTACH )
	{
	//
	//加入你想在目标进程空间HOOK的代码
	//
	  MessageBox(NULL, "SetWindowsHookEx inject success", "dll inject", MB_OK);
	}    
    return TRUE;
}

__declspec(dllexport)LRESULT MyMessageProc(int code, WPARAM wParam, LPARAM lParam)
{
  //
  //你自己对消息的处理
  //
  return CallNextHookEx(g_hhook, code, wParam, lParam);
}
