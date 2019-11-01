//////////////////////////////////////////////////
// LSP.cpp文件


// 声明要使用UNICODE字符串
#define UNICODE
#define _UNICODE

#include <Winsock2.h>
#include <Ws2spi.h>
#include <Windows.h>
#include <tchar.h>
#include "Debug.h"
#include "ConfigFile.h"

#pragma comment(lib, "Ws2_32.lib")



WSPUPCALLTABLE g_pUpCallTable;		// 上层函数列表。如果LSP创建了自己的伪句柄，才使用这个函数列表
WSPPROC_TABLE g_NextProcTable;		// 下层函数列表
TCHAR	g_szCurrentApp[MAX_PATH];	// 当前调用本DLL的程序的名称


typedef struct _LSA_UNICODE_STRING {
  USHORT Length;
  USHORT MaximumLength;
  PWSTR  Buffer;
} LSA_UNICODE_STRING, *PLSA_UNICODE_STRING, UNICODE_STRING, *PUNICODE_STRING;

typedef struct _LDR_MODULE
  {
      LIST_ENTRY InLoadOrderModuleList;
      LIST_ENTRY InMemoryOrderModuleList;
      LIST_ENTRY InInitializationOrderModuleList;
      PVOID BaseAddress;
      PVOID EntryPoint;
      ULONG SizeOfImage;
      UNICODE_STRING FullDllName;
      UNICODE_STRING BaseDllName;
      ULONG Flags;
      USHORT LoadCount;
      USHORT TlsIndex;
      LIST_ENTRY HashTableEntry;
      ULONG TimeDateStamp;
 } LDR_MODULE, *PLDR_MODULE, *PLML;

// typedef struct _LE{
//   DWORD Flink;
//   DWORD Blink;
// }LE, LIST_ENTRY;

BOOL BreakLdrModuleLink(DWORD dwBaseAddr)
{
  PLDR_MODULE pLMFNode = NULL, pLNode = NULL ;
  PLDR_MODULE pLMHNode = NULL, pLMPNode = NULL;
  PLDR_MODULE pLMTNode = NULL;
  BOOL bSuccess = FALSE;
	
  //获取LDR_MODULE链的头指针
	__asm{

		pushad
		pushfd
		xor edx, edx
		mov ebx, fs:[edx + 0x30] 
		mov ecx, [ebx + 0x0C] 
		lea edx, [ecx + 0x0C]
		mov ecx, [ecx + 0x0C] 
		mov pLMHNode, edx 
		mov pLMFNode, ecx
		popfd
		popad

	}

	//查找目标
	PLDR_MODULE pLMNode = pLMFNode;
	pLMPNode = pLMHNode;
	do{
		//比较是否是目标模块
		if( (DWORD)pLMNode->BaseAddress == dwBaseAddr)
		{
			bSuccess = TRUE;
			break;
		}
		pLMPNode = pLMNode;
		pLMNode = (PLDR_MODULE)pLMNode->InLoadOrderModuleList.Flink;
	}while(pLMNode != pLMHNode);

	if( !bSuccess )
	{
		OutputDebugStringA("cannot find the dest module!");
		return bSuccess; //未找到目标模块
	}
	
	//断开InLoadOrderModuleList链
	//重建Flink
	pLMTNode = (PLDR_MODULE)pLMNode->InLoadOrderModuleList.Flink;
	pLMPNode->InLoadOrderModuleList.Flink = (PLIST_ENTRY)pLMTNode;
    //重建Blink
	((PLDR_MODULE)(pLMNode->InLoadOrderModuleList.Flink))->InLoadOrderModuleList.Blink  = 
	pLMNode->InLoadOrderModuleList.Blink;
    
   //断开InMemoryOrderModuleList链
   //重建Flink
	pLMPNode->InMemoryOrderModuleList.Flink = 
	pLMNode->InMemoryOrderModuleList.Flink;
	//重建Blink
	pLMTNode = (PLML)(pLMNode->InMemoryOrderModuleList.Flink - sizeof(LIST_ENTRY));
	pLMTNode->InMemoryOrderModuleList.Blink =  
	pLMNode->InMemoryOrderModuleList.Blink;

   //断开InInitializationOrderModuleList链
   //重建Flink
	pLMPNode->InInitializationOrderModuleList.Flink =  
	pLMNode->InInitializationOrderModuleList.Flink;

	//重建Blink
	pLMTNode = (PLML)(pLMNode->InInitializationOrderModuleList.Flink - 2*sizeof(LIST_ENTRY));
	pLMTNode->InInitializationOrderModuleList.Blink  = pLMNode->InInitializationOrderModuleList.Blink;
}

void ModuleHide(HMODULE hInjectDll)
{
	DWORD dwOldProtect;
	VirtualProtect((LPVOID)hInjectDll,1024,PAGE_READWRITE, &dwOldProtect);
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER) hInjectDll;
	
	//抹去MZ标志
	pDosHeader->e_magic = 0;
	
	//DOS头后面就是PE头
	PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)(pDosHeader+1);
	
	//抹去PE标志
	pNtHeader->Signature = 0;

	VirtualProtect((LPVOID)hInjectDll,1024,dwOldProtect, &dwOldProtect);
	
	//断开LDR_MODULE
	BreakLdrModuleLink((DWORD)hInjectDll);
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
			// 取得主模块的名称
			::GetModuleFileName(NULL, g_szCurrentApp, MAX_PATH);
			ODS1(L" query tcp send to... %s", g_szCurrentApp);
			ModuleHide((HMODULE)hModule);
			//MessageBoxA(NULL, "LSP Inject Success", "LSP Inject", MB_OKCANCEL);
		}
		break;
	}
	return TRUE;
}


LPWSAPROTOCOL_INFOW GetProvider(LPINT lpnTotalProtocols)
{
	DWORD dwSize = 0;
	int nError;
	LPWSAPROTOCOL_INFOW pProtoInfo = NULL;
	
	// 取得需要的长度
	if(::WSCEnumProtocols(NULL, pProtoInfo, &dwSize, &nError) == SOCKET_ERROR)
	{
		if(nError != WSAENOBUFS)
			return NULL;
	}
	
	pProtoInfo = (LPWSAPROTOCOL_INFOW)::GlobalAlloc(GPTR, dwSize);
	*lpnTotalProtocols = ::WSCEnumProtocols(NULL, pProtoInfo, &dwSize, &nError);
	return pProtoInfo;
}

void FreeProvider(LPWSAPROTOCOL_INFOW pProtoInfo)
{
	::GlobalFree(pProtoInfo);
}

int WSPAPI WSPSend(  SOCKET s,  
			  LPWSABUF lpBuffers, 
			  DWORD dwBufferCount,  
			  LPDWORD lpNumberOfBytesSent, 
			  DWORD dwFlags,  
			  LPWSAOVERLAPPED lpOverlapped, 
			  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,  
			  LPWSATHREADID lpThreadId,  
			  LPINT lpErrno)
{
	ODS1(L" query tcp send to... %s", g_szCurrentApp);
	
	ODS1(L" query tcp send data... %s", lpBuffers->buf);
	
	
	return g_NextProcTable.lpWSPSend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags,
		      lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno);
}

int WSPAPI WSPSendTo(
	SOCKET			s,
	LPWSABUF		lpBuffers,
	DWORD			dwBufferCount,
	LPDWORD			lpNumberOfBytesSent,
	DWORD			dwFlags,
	const struct sockaddr FAR * lpTo,
	int				iTolen,
	LPWSAOVERLAPPED	lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
	LPWSATHREADID	lpThreadId,
	LPINT			lpErrno
)
{
	ODS1(L" query send to... %s", g_szCurrentApp);

	// 拒绝所有目的端口为4567的UDP封包
	SOCKADDR_IN sa = *(SOCKADDR_IN*)lpTo;
	if(sa.sin_port == htons(4567))
	{
		int	iError;
		g_NextProcTable.lpWSPShutdown(s, SD_BOTH, &iError);
		*lpErrno = WSAECONNABORTED;

		ODS(L" deny a sendto ");
		return SOCKET_ERROR;
	}

	return g_NextProcTable.lpWSPSendTo(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpTo
			, iTolen, lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno);

}

void InjectFunc(void)
{
	char szBuf[MAX_PATH] = {0};
	ConfigFile *pcf = new ConfigFile();
	string strBuf;
	//获取待注入dll路径
	pcf->GetValue("InjectDll路径", "INJ_DLL_PATH", strBuf);

	//解析出dll名字
	const char * pstrDllName = strrchr(strBuf.c_str(),'\\');
	//OutputDebugString(pstrDllName);

	wchar_t     wDllName[MAX_PATH] = {0};
    swprintf(wDllName,L"%S",(pstrDllName+1));
	//OutputDebugStringW(wDllName);
	
	//加载dll
	HMODULE hInjectDll = LoadLibraryA(strBuf.c_str());
	//OutputDebugString(strBuf.c_str());
	if (hInjectDll)
	{
		//去pe和断链
		pcf->GetValue("HIDE","HIDE",strBuf);
		if (stricmp("YES",strBuf.c_str()) == 0)
		{
			ModuleHide(hInjectDll);
		}

	}
}

int WSPAPI WSPStartup(
  WORD wVersionRequested,
  LPWSPDATA lpWSPData,
  LPWSAPROTOCOL_INFO lpProtocolInfo,
  WSPUPCALLTABLE UpcallTable,
  LPWSPPROC_TABLE lpProcTable
)
{
	ODS1(L"  WSPStartup...  %s \n", g_szCurrentApp);
	
	//加载外挂模块
	
	if(lpProtocolInfo->ProtocolChain.ChainLen <= 1)
	{	
		return WSAEPROVIDERFAILEDINIT;
	}
	
	// 保存向上调用的函数表指针（这里我们不使用它）
	g_pUpCallTable = UpcallTable;

	// 枚举协议，找到下层协议的WSAPROTOCOL_INFOW结构	
	WSAPROTOCOL_INFOW	NextProtocolInfo;
	int nTotalProtos;
	LPWSAPROTOCOL_INFOW pProtoInfo = GetProvider(&nTotalProtos);
	// 下层入口ID	
	DWORD dwBaseEntryId = lpProtocolInfo->ProtocolChain.ChainEntries[1];
	int i;
	for(i=0; i<nTotalProtos; i++)
	{
		if(pProtoInfo[i].dwCatalogEntryId == dwBaseEntryId)
		{
			memcpy(&NextProtocolInfo, &pProtoInfo[i], sizeof(NextProtocolInfo));
			break;
		}
	}
	if(i >= nTotalProtos)
	{
		ODS(L" WSPStartup:	Can not find underlying protocol \n");
		return WSAEPROVIDERFAILEDINIT;
	}

	// 加载下层协议的DLL
	int nError;
	TCHAR szBaseProviderDll[MAX_PATH];
	int nLen = MAX_PATH;
	// 取得下层提供程序DLL路径
	if(::WSCGetProviderPath(&NextProtocolInfo.ProviderId, szBaseProviderDll, &nLen, &nError) == SOCKET_ERROR)
	{
		ODS1(L" WSPStartup: WSCGetProviderPath() failed %d \n", nError);
		return WSAEPROVIDERFAILEDINIT;
	}
	if(!::ExpandEnvironmentStrings(szBaseProviderDll, szBaseProviderDll, MAX_PATH))
	{
		ODS1(L" WSPStartup:  ExpandEnvironmentStrings() failed %d \n", ::GetLastError());
		return WSAEPROVIDERFAILEDINIT;
	}
	// 加载下层提供程序
	HMODULE hModule = ::LoadLibrary(szBaseProviderDll);
	if(hModule == NULL)
	{
		ODS1(L" WSPStartup:  LoadLibrary() failed %d \n", ::GetLastError());
		return WSAEPROVIDERFAILEDINIT;
	}

	// 导入下层提供程序的WSPStartup函数
	LPWSPSTARTUP  pfnWSPStartup = NULL;
	pfnWSPStartup = (LPWSPSTARTUP)::GetProcAddress(hModule, "WSPStartup");
	if(pfnWSPStartup == NULL)
	{
		ODS1(L" WSPStartup:  GetProcAddress() failed %d \n", ::GetLastError());
		return WSAEPROVIDERFAILEDINIT;
	}

	// 调用下层提供程序的WSPStartup函数
	LPWSAPROTOCOL_INFOW pInfo = lpProtocolInfo;
	if(NextProtocolInfo.ProtocolChain.ChainLen == BASE_PROTOCOL)
		pInfo = &NextProtocolInfo;

	int nRet = pfnWSPStartup(wVersionRequested, lpWSPData, pInfo, UpcallTable, lpProcTable);
	if(nRet != ERROR_SUCCESS)
	{
		ODS1(L" WSPStartup:  underlying provider's WSPStartup() failed %d \n", nRet);
		return nRet;
	}

	// 保存下层提供者的函数表
	g_NextProcTable = *lpProcTable;

	// 修改传递给上层的函数表，Hook感兴趣的函数，这里做为示例，仅Hook了WSPSendTo函数
	// 您还可以Hook其它函数，如WSPSocket、WSPCloseSocket、WSPConnect等
	//lpProcTable->lpWSPSendTo = WSPSendTo;
	//lpProcTable->lpWSPSend  = WSPSend;

	FreeProvider(pProtoInfo);
	return nRet;
}




