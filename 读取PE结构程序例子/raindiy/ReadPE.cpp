// ReadPE.cpp: implementation of the ReadPE class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReadPE.h"
#include <stdio.h>
#include "pe.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ReadPE::~ReadPE()
{
	delete u_addr_file;
	u_addr_file = 0;
}
//初始化数据
BOOL ReadPE::Init()
{
	FILE *f;
	f = fopen(filename,"rb");

	fseek(f, 0, SEEK_END);
	m_size = ftell(f);
	fseek(f, 0, SEEK_SET);

	if (u_addr_file)
	{
		delete u_addr_file;
		u_addr_file = 0;
	}
	
	u_addr_file = new unsigned char[m_size];

	if (fread(u_addr_file, sizeof(unsigned char), m_size, f) != (size_t)m_size)
	{
	
		fclose(f);

		if (u_addr_file)
		{
			delete u_addr_file;
			u_addr_file = 0;
		}
		return FALSE;
	}
	fclose (f);
	

	return TRUE;
}

BOOL ReadPE::SetPE()
{
	unsigned int	i;
	unsigned short	dos_stub;
	unsigned int	pe_offset, pe_signature;
	unsigned int	current_pos;

	dos_stub = ((unsigned short*)u_addr_file)[0];
	if (dos_stub != 0x5a4d)
	{
		MessageBox(NULL, "不是windows的可执行文件!", "提示", 0);
		return FALSE;
	}
	
	pe_offset = *((unsigned int*)(u_addr_file + 0x3c));
	//检查是否是可执行文件
	pe_signature = *((unsigned int*)(u_addr_file + pe_offset));

	if (pe_signature != 0x00004550)
	{
		MessageBox(NULL, "不是一个可执行的PE文件", "提示", 0);
		return FALSE;
	}
	current_pos = pe_offset + 4;
	
	m_pe_header = (PEHeader*)(u_addr_file + current_pos);
	current_pos += sizeof(PEHeader);
	
	m_nt_header = (NTOptionalHeader*)(u_addr_file + current_pos);
	current_pos += sizeof(NTOptionalHeader);

	m_directories = (DataDirectory*)(u_addr_file + current_pos);
	current_pos += sizeof(DataDirectory) * m_nt_header->numDataDirectories;

	m_sections = (Section*)(u_addr_file + current_pos);
	current_pos += sizeof(Section) * m_pe_header->numSections; 

	for (i=0; i<m_pe_header->numSections; i++)
	{
		m_sections[i].dataOffset = m_sections[i].RVA;
		m_sections[i].dataAlignSize = m_sections[i].misc.virtualSize;
	}


	return TRUE;
}

void ReadPE::Full()
{

	delete u_addr_file;
	u_addr_file = 0;
}