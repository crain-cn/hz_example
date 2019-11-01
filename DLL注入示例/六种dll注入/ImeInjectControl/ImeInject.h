#ifdef	__INJECT_H_INCLUDE
#define __INJECT_H_INCLUDE

#ifdef __cplusplus

#define  DLLCOM extern "C" __declspec(dllexport)

#else 


#define  DLLCOM  __declspec(dllexport)

#endif


 int WINAPI IMESetPubString(LPCTSTR tmpStr,DWORD UnloadDLL,DWORD loadNextIme,DWORD DllData1,DWORD DllData2,DWORD DllData3);
 int WINAPI IMEClearPubString();

#endif