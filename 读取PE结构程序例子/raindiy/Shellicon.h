// Shellicon.h: interface for the Shellicon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHELLICON_H__F02795E6_DAEE_4C75_B763_97304B410753__INCLUDED_)
#define AFX_SHELLICON_H__F02795E6_DAEE_4C75_B763_97304B410753__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "StdAfx.h"

class Shellicon  
{
public:
	Shellicon();
	virtual ~Shellicon();
	VOID CreateShellIcon(int id,HWND hwnd,LPSTR name,int msg);
	VOID DelShellIcon(int id,HWND hwnd,LPSTR name,int msg);
	NOTIFYICONDATA nid;
	
};

#endif // !defined(AFX_SHELLICON_H__F02795E6_DAEE_4C75_B763_97304B410753__INCLUDED_)
