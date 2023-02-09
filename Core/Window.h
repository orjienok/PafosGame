#pragma once
#include <Windows.h>
class Window
{
public:
	Window(HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc);
	HWND getHWND();

	UINT getWindowWidth();
	UINT getWindowHeight();

	UINT getClientWidth();
	UINT getClientHeight();

	~Window();
private:
	HWND m_hwnd;
	HINSTANCE m_hInstance;
};

