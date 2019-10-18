// MyProcess1.h: interface for the MyProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPROCESS1_H__A570EC55_8BF5_4103_A74B_5C4CF9D5813C__INCLUDED_)
#define AFX_MYPROCESS1_H__A570EC55_8BF5_4103_A74B_5C4CF9D5813C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>

class MyProcess  
{
public:
	MyProcess();
	virtual ~MyProcess();
	void AddDriverInfo(HWND list);  //ÃÌº”¥≈≈Ã–≈œ¢	
	void SetDeiverTextInfo(HWND ltext,LPSTR lpName);
	void findFile(char filePath[],HWND lhwnd);
};

#endif // !defined(AFX_MYPROCESS1_H__A570EC55_8BF5_4103_A74B_5C4CF9D5813C__INCLUDED_)
