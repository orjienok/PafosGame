#include "Window.h"

Window::Window(HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc)
{
    WNDCLASSEX wcex = {0};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.lpszClassName = "TutorialWindowClass";
    RegisterClassEx(&wcex);

    // Create window
    this->m_hInstance = hInstance;
    this->m_hwnd = CreateWindowEx(0,"TutorialWindowClass", "Direct3D 11",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance,NULL);

    RECT rect;
    if (GetWindowRect(this->m_hwnd, &rect))
    {
        this->width = rect.right - rect.left;
        this->height = rect.bottom - rect.top;
    }

    ShowWindow(this->m_hwnd, nCmdShow);
}

Window::~Window()
{
    DestroyWindow(this->m_hwnd);
}