#ifndef _MAIN_H1_2
#define _MAIN_H1_2

#include <windows.h>
 class RainMain
{
	public:
		static BOOL WINAPI RainMain_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static void CommandMg(int id,HWND hwnd, WPARAM wParam, LPARAM lParam);
		static BOOL InitDiaLog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	private:
		
};
#endif