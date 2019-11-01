// ConfigFile.cpp: implementation of the ConfigFile class.
//
//////////////////////////////////////////////////////////////////////

#include "ConfigFile.h"

#include   <shlobj.h>   
#pragma   comment(lib,   "shell32.lib")   

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define  DEF_PROFILE_THRESHOLD 512
ConfigFile::ConfigFile()
{

	char szPath[MAX_PATH] = {0};
	//C:\Users\xianglong.xs\Documents
	SHGetSpecialFolderPath(GetDesktopWindow(), szPath ,5,false);
	//GetCurrentDirectory(MAX_PATH, szPath);
	strcat(szPath, "\\Winsun.ini");
	OutputDebugString(szPath);
    HANDLE hIniFile = CreateFile(szPath,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		 NULL );
	if (hIniFile == INVALID_HANDLE_VALUE)
	{
		//g_pAPKServerDlg->PrintOpStatus("创建ini文件失败!");
		m_sPath = "";
	}
	else
	{
		m_sPath = szPath;
	}

	

}

ConfigFile::ConfigFile( const char* sPath ):m_sPath(sPath)
{
	
}
ConfigFile::~ConfigFile()
{

}

void ConfigFile::LoadFile(const char* sPath )
{
	m_sPath = sPath;
}

void  ConfigFile::GetSectionNames( vector<string> &ar )
{
	const DWORD LEN = GetSectionNames(NULL, 0);
	if (LEN == 0)
		return;
	
	char* psz = new char[LEN + 1];

	GetSectionNames(psz, LEN);
    ParseString(psz, ar);

	delete [] psz;
}

DWORD ConfigFile::GetSectionNames(char* lpBuffer, DWORD dwBufSize)
{
	if (lpBuffer == NULL)
	{
		// just calculate the required buffer size
		DWORD dwLen = DEF_PROFILE_THRESHOLD;
		char* psz = new char[dwLen + 1];
		DWORD dwCopied = ::GetPrivateProfileSectionNames(psz, dwLen, m_sPath.c_str());
		while (dwCopied + 2 >= dwLen)
		{
			dwLen += DEF_PROFILE_THRESHOLD;
			delete [] psz;
			psz = new char[dwLen + 1];
			dwCopied = ::GetPrivateProfileSectionNames(psz, dwLen, m_sPath.c_str());
		}
		
		delete [] psz;
		return dwCopied + 2;
	}
	else
	{
		return ::GetPrivateProfileSectionNames(lpBuffer, dwBufSize, m_sPath.c_str()); 
	}
}

void ConfigFile::GetKey_Value(const char* lpSection/*段名*/, vector<string> &ar )
{
    DWORD Len = GetKey_Value(lpSection, NULL, 0);

	char* psz = new char[Len + 1];
	
	GetKey_Value(lpSection, psz, Len);
    ParseString(psz, ar);
	
	delete [] psz;
}

DWORD ConfigFile::GetKey_Value(const char* lpSection, char* lpBuffer, DWORD dwBufSize)
{	
	if (lpBuffer != NULL)
		*lpBuffer = '\0';
	
	if (lpSection == NULL)
		return 0;	
	
	if (lpBuffer == NULL)
	{
		// just calculate the required buffer size
		DWORD dwLen = DEF_PROFILE_THRESHOLD;
		char* psz = new char[dwLen + 1];
		DWORD dwCopied = ::GetPrivateProfileSection(lpSection, psz, dwLen, m_sPath.c_str());
		
		while (dwCopied + 2 >= dwLen)
		{
			dwLen += DEF_PROFILE_THRESHOLD;
			delete [] psz;
			psz = new char[dwLen + 1];
			dwCopied = ::GetPrivateProfileSection(lpSection, psz, dwLen, m_sPath.c_str());
		}
		
		delete [] psz;
		return dwCopied + 2;
	}
	else
	{
		return ::GetPrivateProfileSection(lpSection, lpBuffer, dwBufSize, m_sPath.c_str());
	}
}


BOOL ConfigFile::ParseString( char* buff, vector<string> &ar )
{
	if (buff == NULL)
		return FALSE;
	
	char* p = buff;
	DWORD dwLen = strlen(p);
	
	while (dwLen > 0)
	{
		ar.push_back(string(p));
		p = &p[dwLen + 1];
		dwLen = strlen(p);
	}
	return TRUE;
}

void ConfigFile::GetKeyNames(const char* lpSection/*段名*/, vector<string> &ar )
{
	vector<string> key_value;
    GetKey_Value(lpSection, key_value);//先得到所有的key_value，然后解析出来

	int num = key_value.size();

	for(int i=0; i<num; i++)
	{
		int pos = key_value[i].find('=', 0);
		if(-1 == pos)
			ar.push_back(key_value[i]);
		else
		    ar.push_back(key_value[i].substr(0, pos));
	}
}

DWORD ConfigFile::GetValue(const char *lpSection/*段名*/,const char *sKey/*Key值*/, string& key)
{
	if (lpSection == NULL || sKey == NULL)
		return FALSE;

	char val[512]={'\0'};
	
    DWORD ret = GetPrivateProfileString(lpSection, sKey, "", val, 512, m_sPath.c_str());
	
    key = val;
	return ret;
}

BOOL ConfigFile::Write( const char* lpSection, const char* lpKey, const char* lpValue )
{
	if (lpSection == NULL || lpKey == NULL)
		return FALSE;
	
	return ::WritePrivateProfileString(lpSection, lpKey, lpValue == NULL ? "" : lpValue, m_sPath.c_str());
}

BOOL ConfigFile::DeleteSection(const char* lpSection) 
{
	return ::WritePrivateProfileString(lpSection, NULL, "", m_sPath.c_str());
}

BOOL ConfigFile::DeleteKey(const char* lpSection, const char* lpKey)
{

	return ::WritePrivateProfileString(lpSection, lpKey, NULL, m_sPath.c_str());
}

