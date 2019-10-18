// RainSSDT.h: interface for the RainSSDT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RAINSSDT_H__6EC3DB68_5E48_4FD3_8E38_05FD2F1EFE28__INCLUDED_)
#define AFX_RAINSSDT_H__6EC3DB68_5E48_4FD3_8E38_05FD2F1EFE28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class RainSSDT  
{
public:
	RainSSDT();
	virtual ~RainSSDT();
	static BOOL WINAPI RainMain_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	private:
	static void CommandMg(int id,HWND hwnd, WPARAM wParam, LPARAM lParam);
	static BOOL InitDiaLog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif // !defined(AFX_RAINSSDT_H__6EC3DB68_5E48_4FD3_8E38_05FD2F1EFE28__INCLUDED_)
