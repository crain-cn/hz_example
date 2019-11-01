#include "DbgInfo.h"

void UsageHelpInfo(void)
{
	printf("                     Welcome to use the tool!\n");
	printf("*****************Usage Help Information By winsunxu*****************\n");
	
	
}
void SelectInjectMethod(void)
{
	printf("Have 6 Inject Methods as follows: \n ");
    printf("1. Registry Inject.\n2. SetWindowsHookEx Inject.\n3. Remote Thread Inject.\n4. SetThreadContext Inject\n5. APC + LoadLibrary.\n6. APC + ShellCode + LoadLibrary.\n");
	
}

#define DBG_BUFFER_SIZE 512
#ifdef _DEBUG_
void MyDbgPrint(char *fmt, ...)
{
	va_list	ap;
	char	sz[DBG_BUFFER_SIZE];
	
	va_start(ap, fmt);
	vsprintf(sz, fmt, ap);
	OutputDebugStringA(sz);
	va_end(ap);
}
#endif

ULONG GetWindowsVersion()
{
	ULONG uVer;
	OSVERSIONINFO  OsVer;
	PRT(("[!] GetWindowsVersion Enter..."));
	OsVer.dwOSVersionInfoSize  = sizeof(OSVERSIONINFO);
	if(!GetVersionEx(&OsVer))
	{
		uVer = 0;
		goto Exit;
	}
	else
	{
		if(5 == OsVer.dwMajorVersion && 0 == OsVer.dwMinorVersion)
		{
			uVer = WIN_2K;
			goto Exit;
		}
		else if(5 == OsVer.dwMajorVersion && 1 == OsVer.dwMinorVersion)
		{
			uVer = WIN_XP;
			goto Exit;
		} 
		else
		{
			uVer = WIN_OTHER;
			goto Exit;
		}
		
	}
Exit:
	PRT(("[!] GetWindowsVersion Exit..."));
	return uVer;
}