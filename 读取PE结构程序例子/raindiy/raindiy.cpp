#include "StdAfx.h"
#include "resource.h"
//#include "main.h"
#include "rainmain.h"
#define MAX_LOADSTRING 100
//#pragma comment(lib,"res/SkinMagicLib.lib")
//#pragma comment(lib,"res/DETOURS.lib")
int WINAPI WinMain(HINSTANCE Ihnstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	InitSkinMagicLib(Ihnstance, "LSA" , NULL,NULL );//加载SkinMagicLib.lib、DETOURS.lib库 
	//LoadSkinFile("corona.smf");
	LoadSkinFromResource( GetModuleHandle(NULL),"XPBLUE" ,"SKINMAGIC");//加载静态自定义皮肤资源

	DialogBox(Ihnstance,MAKEINTRESOURCE(IDD_RAINMAIN),NULL,RainMain::RainMain_Proc);
	
	ExitSkinMagicLib(); 

	return 0;
}
