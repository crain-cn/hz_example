#ifndef _MAIN_H1_4
#define _MAIN_H1_4

#include <windows.h>

//PE文件查看
class RainPe
{
public:
	RainPe(void)
	{
		
	}
	~RainPe()
	{

	}
	static BOOL WINAPI RainMain_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void CommandMg(int id,HWND hwnd, WPARAM wParam, LPARAM lParam);
	static BOOL InitDiaLog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
private:
};
#endif
