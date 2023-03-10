#include "D3DManager.h"
#include <iostream>

D3DManager::D3DManager(Window& window)
{
	InitD3D(window);
}

D3DManager::~D3DManager()
{
    this->dev->Release();
    this->devcon->Release();
    this->swapchain->Release();
}

void D3DManager::InitD3D(Window& window)
{
    DXGI_SWAP_CHAIN_DESC scd;

    // clear out the struct for use
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // fill the swap chain description struct
    scd.BufferCount = 1;                                    // one back buffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.Width = window.getClientWidth();
    scd.BufferDesc.Height = window.getClientHeight();
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
    scd.OutputWindow = window.getHWND();                                // the window to be used
    scd.SampleDesc.Count = 4;                               // how many multisamples
    scd.Windowed = TRUE;                                    // windowed/full-screen mode

    // create a device, device context and swap chain using the information in the scd struct
    D3D11CreateDeviceAndSwapChain(NULL,D3D_DRIVER_TYPE_HARDWARE,NULL,D3D11_CREATE_DEVICE_DEBUG,NULL,NULL,D3D11_SDK_VERSION,&scd,&swapchain,&dev,NULL,&devcon);

    this->dev->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDXGIDevice);
    pDXGIDevice->GetAdapter(&pDXGIAdapter);

    ID3D11Texture2D* pBackBuffer;
    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // use the back buffer address to create the render target
    dev->CreateRenderTargetView(pBackBuffer, NULL, &m_renderTarget);
    pBackBuffer->Release();
}

ID3D11Device* D3DManager::getDevice()
{
    return this->dev;
}
ID3D11DeviceContext* D3DManager::getDeviceContext()
{
    return this->devcon;
}
IDXGISwapChain* D3DManager::getDeviceSwapchain()
{
    return this->swapchain;
}

void D3DManager::getDeviceName()
{
    DXGI_ADAPTER_DESC desc;
    this->pDXGIAdapter->GetDesc(&desc);

    const wchar_t* wcsIndirectString = desc.Description;
    char mychars[128] ;

    size_t          countConverted;
    errno_t         err;
    mbstate_t       mbstate;

    err = wcsrtombs_s(&countConverted, mychars, 128,
        &wcsIndirectString, 128, &mbstate);

    if (err == EILSEQ)
    {
        printf("An encoding error was detected in the string.\n");
    }
    else
    {
        std::cout << mychars << std::endl;
    }
}

ID3D11RenderTargetView* D3DManager::getRenderTarget()
{
    return this->m_renderTarget;
}