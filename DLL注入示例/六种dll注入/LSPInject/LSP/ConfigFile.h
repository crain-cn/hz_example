// ConfigFile.h: interface for the ConfigFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGFILE_H__7D6BD22C_657B_4F3E_8752_4061EFB73101__INCLUDED_)
#define AFX_CONFIGFILE_H__7D6BD22C_657B_4F3E_8752_4061EFB73101__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <vector>
#include <string>
using namespace std;
class ConfigFile  
{public:
	ConfigFile();
    ConfigFile(const char* sPath);
	virtual ~ConfigFile();
	
	void  LoadFile(const char* sPath ); //文件路径
	
	void  GetSectionNames(vector<string> &ar);/*得到所有段*/	
	
	void  GetKeyNames(const char* lpSection/*段名*/, vector<string> &ar);//得到某段下所有key名称
	DWORD GetValue(const char *lpSection/*段名*/, const char *sKey/*Key值*/, string& key);//得到可以值
	
	void  GetKey_Value(const char* lpSection/*段名*/, vector<string> &ar );/*得到该段下的所有key-value*/
	
	
	BOOL  Write(const char* lpSection, const char* lpKey, const char* lpValue);//写入键值
	BOOL  DeleteSection(const char* lpSection);//删除段
	BOOL  DeleteKey(const char* lpSection, const char* lpKey);//删除key
	
protected:
	DWORD GetSectionNames(char* lpBuffer, DWORD dwBufSize);//返回字符总数
	DWORD GetKey_Value(const char* lpSection, char* lpBuffer, DWORD dwBufSize);//返回字符总数
	
	BOOL  ParseString( char* buff, vector<string> &ar );//解析出段、键值
	
	
protected:
	string m_sPath;

};

#endif // !defined(AFX_CONFIGFILE_H__7D6BD22C_657B_4F3E_8752_4061EFB73101__INCLUDED_)
