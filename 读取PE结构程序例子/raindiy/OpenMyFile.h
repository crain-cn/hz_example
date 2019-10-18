// OpenMyFile.h: interface for the OpenMyFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENMYFILE_H__501079B8_1C4B_4765_8F8E_C16111073EE6__INCLUDED_)
#define AFX_OPENMYFILE_H__501079B8_1C4B_4765_8F8E_C16111073EE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>
class OpenMyFile  
{
public:
	OpenMyFile();
	virtual ~OpenMyFile();
	BOOL OpenFileDlls(HWND hWnd,HINSTANCE hInst,int id);
	LPCSTR lpMystrFilter;  //设置文件打开
	LPCSTR lpMystrTitle;  //设置标题
};

#endif // !defined(AFX_OPENMYFILE_H__501079B8_1C4B_4765_8F8E_C16111073EE6__INCLUDED_)
