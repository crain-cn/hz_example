#ifndef _MAIN_H
#define _MAIN_H

#include <windows.h>

BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL InitDiaLog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CommandMg(int id,HWND uMsg, WPARAM wParam, LPARAM lParam);
void CloseMg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CommandMgLive(int id,HWND hwnd, WPARAM wParam, LPARAM lParam);
#endif