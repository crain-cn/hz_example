#include <stdio.h>
#include <windows.h>
#define DSTKEY "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Windows"
bool RegInject(CHAR  *pstrDllPath);

void main(void)
{
	CHAR strDllPath[MAX_PATH] = {0};
	printf("please input inject Dll path: ");
	scanf("%s", strDllPath);
	bool bSuccess = RegInject(strDllPath);
	if (bSuccess)
	{
		printf("/n Registry inject success!\n");
	}
	else
	{
		printf("/n Registry inject fail!\n");
	}
}

//
//利用AppInit_Dlls键值会被user32.dll调用LoadLibrary所加载
//
bool RegInject(CHAR  *pstrDllPath)
{
 
	bool bSuccess = false; 
    HKEY hKey = NULL;
    LONG nReg;
	BYTE cDllPath[MAX_PATH] = {0};
 
 
    OutputDebugString("[!] RegInject Enter...");
    nReg = RegOpenKeyEx(
	       HKEY_LOCAL_MACHINE, 
		   DSTKEY, 
		   0, 
		   KEY_ALL_ACCESS,
		   &hKey);
 
	if(nReg != ERROR_SUCCESS)
     {
       OutputDebugString("[-] RegOpenKeyEx Error!\n");
	   goto Exit;
     }

    memcpy((void*)cDllPath, pstrDllPath, strlen(pstrDllPath)+1);

	nReg = RegSetValueEx(
		hKey,
		"AppInit_DLLs",
		0,
		REG_SZ,
		cDllPath,
		strlen((char*)cDllPath)+1
	    );

	if(nReg != ERROR_SUCCESS)
      {
         OutputDebugString("[-] RegSetKeyValue Error!\n");
		 goto Exit;
      }

 OutputDebugString("[!] RegInject Exit...");
 bSuccess = true;
Exit:
 if(hKey)
	 RegCloseKey(hKey);
 return bSuccess;

}