// reateListView.h: interface for the CreateListView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REATELISTVIEW_H__495D3F5F_C2F4_4DF5_B32E_B764FEC0029F__INCLUDED_)
#define AFX_REATELISTVIEW_H__495D3F5F_C2F4_4DF5_B32E_B764FEC0029F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CreateListView  
{
public:
	CreateListView();
	virtual ~CreateListView();
	VOID CreateSSDTListView(HWND hWnd,int id,LPSTR colName[]);


};

#endif // !defined(AFX_REATELISTVIEW_H__495D3F5F_C2F4_4DF5_B32E_B764FEC0029F__INCLUDED_)
