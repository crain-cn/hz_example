// ReadPE.h: interface for the ReadPE class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READPE_H__6BF00952_D126_4450_805A_66A66EF24676__INCLUDED_)
#define AFX_READPE_H__6BF00952_D126_4450_805A_66A66EF24676__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <winnt.h>
#include "pe.h"

class ReadPE  
{
public:
	ReadPE()
	{
	};
	virtual ~ReadPE();
	BOOL Init();    //初始化数据
	BOOL SetPE();
	void Full();
	PEHeader *m_pe_header;
	NTOptionalHeader  *m_nt_header;
	DataDirectory  *m_directories;
	Section *m_sections;
	char *filename; //文件名称
private:

	unsigned char *u_addr_file;
	long m_size;	
};

#endif // !defined(AFX_READPE_H__6BF00952_D126_4450_805A_66A66EF24676__INCLUDED_)
