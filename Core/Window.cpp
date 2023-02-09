#include "Window.h"
#include <dwmapi.h>

Window::Window(HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc)
{
    WNDCLASSEX wcex = {0};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.lpszClassName = "WindowClass";
    RegisterClassEx(&wcex);

    // Create window
    this->m_hInstance = hInstance;
    this->m_hwnd = CreateWindowEx(0,"WindowClass", "PafosGame", WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance,this);

    ShowWindow(this->m_hwnd, nCmdShow);
}

Window::~Window()
{
    DestroyWindow(this->m_hwnd);
}

HWND Window::getHWND()
{
    return this->m_hwnd;
}

UINT Window::getWindowWidth()
{
    RECT rect;
    if (GetWindowRect(this->m_hwnd, &rect))
    {
        UINT width = rect.right - rect.left;
        return width;
    }
}
UINT Window::getWindowHeight()
{
    RECT rect;
    if (GetWindowRect(this->m_hwnd, &rect))
    {
        UINT height = rect.bottom - rect.top;
        return height;
    }
}

UINT Window::getClientWidth()
{
    RECT rect;
    if (GetClientRect(this->m_hwnd, &rect))
    {
        UINT width = rect.right - rect.left;
        return width;
    }
}

UINT Window::getClientHeight()
{
    RECT rect;
    if (GetClientRect(this->m_hwnd, &rect))
    {
        UINT height = rect.bottom - rect.top;
        return height;
    }
}