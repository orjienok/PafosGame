#include "GPUManager.h"

GPUManager::GPUManager(HWND hWnd)
{
	InitD3D(hWnd);
}

GPUManager::~GPUManager()
{
    this->dev->Release();
    this->devcon->Release();
    this->swapchain->Release();
}

void GPUManager::InitD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC scd;

    // clear out the struct for use
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // fill the swap chain description struct
    scd.BufferCount = 1;                                    // one back buffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
    scd.OutputWindow = hWnd;                                // the window to be used
    scd.SampleDesc.Count = 4;                               // how many multisamples
    scd.Windowed = TRUE;                                    // windowed/full-screen mode

    // create a device, device context and swap chain using the information in the scd struct
    D3D11CreateDeviceAndSwapChain(NULL,D3D_DRIVER_TYPE_HARDWARE,NULL,NULL,NULL,NULL,D3D11_SDK_VERSION,&scd,&swapchain,&dev,NULL,&devcon);
}

ID3D11Device* GPUManager::getDevice()
{
    return this->dev;
}
ID3D11DeviceContext* GPUManager::getDeviceContext()
{
    return this->devcon;
}
IDXGISwapChain* GPUManager::getDeviceSwapchain()
{
    return this->swapchain;
}