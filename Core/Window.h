#pragma once
#include <Windows.h>
class Window
{
public:
	Window(HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc);
	HWND getHWND();
	~Window();
private:
	UINT width;
	UINT height;
	HWND m_hwnd;
	HINSTANCE m_hInstance;
};

