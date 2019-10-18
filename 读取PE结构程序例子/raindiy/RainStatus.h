// RainStatus.h: interface for the RainStatus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RAINSTATUS_H__3F6107E1_9EF3_46F2_BF08_C5889DAB525A__INCLUDED_)
#define AFX_RAINSTATUS_H__3F6107E1_9EF3_46F2_BF08_C5889DAB525A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class RainStatus  
{
public:
	RainStatus();
	virtual ~RainStatus();
	static BOOL WINAPI RainStatusMain_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void CommandMg(int id,HWND hwnd, WPARAM wParam, LPARAM lParam);
	static BOOL InitDiaLog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif // !defined(AFX_RAINSTATUS_H__3F6107E1_9EF3_46F2_BF08_C5889DAB525A__INCLUDED_)
