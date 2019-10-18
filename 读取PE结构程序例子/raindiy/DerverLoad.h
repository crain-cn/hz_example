// DerverLoad.h: interface for the DerverLoad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DERVERLOAD_H__7F048EF8_DD90_4FFF_8F95_8C06F062326A__INCLUDED_)
#define AFX_DERVERLOAD_H__7F048EF8_DD90_4FFF_8F95_8C06F062326A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>
class DerverLoad  
{
public:
	DerverLoad();
	virtual ~DerverLoad();
	static BOOL WINAPI RainSysMain_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void CommandMg(int id,HWND hwnd, WPARAM wParam, LPARAM lParam);
};

#endif // !defined(AFX_DERVERLOAD_H__7F048EF8_DD90_4FFF_8F95_8C06F062326A__INCLUDED_)
