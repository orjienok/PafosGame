#include "Core/Window.h";
#include "Core/D3DManager.h"
#include "Core/SimpleMath.h";
#include "Renderer.h"
#include "geometry/Cube.h"
#include "Shaders.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_dx11.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "RenderUI.h";
#include <iostream>
#include <directxtk/WICTextureLoader.h>
#include "ModelReader.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

ID3D11Device* g_pd3dDevice;

ID3D11RenderTargetView* g_mainRenderTargetView = NULL;
IDXGISwapChain* g_pSwapChain;
ID3D11Texture2D* pTexture = NULL;

float color[4] = { 0.40, 0.40, 0.40, 1.0 };
float backColor[4] = {0.93,0.93,0.94};

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    Window myWindow = Window(hInstance, SW_MAXIMIZE, WndProc);
    D3DManager myD3DManager = D3DManager(myWindow);
    g_pd3dDevice = myD3DManager.getDevice();
    g_mainRenderTargetView = myD3DManager.getRenderTarget();
    g_pSwapChain = myD3DManager.getDeviceSwapchain();

    AllocConsole();
    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);

   
    Shaders myShaders = Shaders(&myD3DManager);

    myShaders.createVertexShaderFromFile(L"C://Users//admin123//source//repos//PafosGame//PafosGame//assets//Shaders//VertexShader.hlsl");
    myShaders.createPixelShaderFromFile(L"C://Users//admin123//source//repos//PafosGame//PafosGame//assets//Shaders//PixelShader.hlsl");

    Cube myCube = Cube(&myD3DManager);


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    bool show_demo_window = true;

    Renderer myRenderer = Renderer(&myD3DManager, myWindow);
    RenderUI myRenderUI = RenderUI(myWindow.getHWND(), &myD3DManager,io,&myRenderer);


    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = 1920;
    desc.Height = 1017;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;

    g_pd3dDevice->CreateTexture2D(&desc, NULL, &pTexture);

    D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
    ZeroMemory(&renderTargetViewDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
    renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    renderTargetViewDesc.Texture2D.MipSlice = 0;

    ID3D11RenderTargetView* renderTex;

    g_pd3dDevice->CreateRenderTargetView(pTexture, &renderTargetViewDesc, &renderTex);

    D3D11_SHADER_RESOURCE_VIEW_DESC shaderViewDesc;
    ZeroMemory(&shaderViewDesc, sizeof(shaderViewDesc));
    shaderViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    shaderViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderViewDesc.Texture2D.MipLevels = 1;

    ID3D11ShaderResourceView* my_tex;

    g_pd3dDevice->CreateShaderResourceView(pTexture, &shaderViewDesc, &my_tex);

    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.MaxDepth = 1.0f;
    viewport.MinDepth = 0.0f;
    viewport.Width = myWindow.getClientWidth();
    viewport.Height = myWindow.getClientHeight();

    myD3DManager.getDeviceContext()->RSSetViewports(1, &viewport);

    HRESULT hr;

    hr = CoInitialize(NULL);

    ID3D11SamplerState* texFiltiringInformation;

    D3D11_SAMPLER_DESC samp_desc;
    ZeroMemory(&samp_desc, sizeof(samp_desc));
    samp_desc.Filter = D3D11_FILTER_ANISOTROPIC;
    samp_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samp_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samp_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samp_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

    myD3DManager.getDevice()->CreateSamplerState(&samp_desc, &texFiltiringInformation);

    ID3D11Resource* texture = nullptr;

    desc.Width = 492;
    desc.Height = 492;

    ID3D11ShaderResourceView* ShaderTexView;

    myD3DManager.getDevice()->CreateShaderResourceView(texture,&shaderViewDesc,&ShaderTexView);

    hr = DirectX::CreateWICTextureFromFile(myD3DManager.getDevice(), L"C://Users//admin123//source//repos//PafosGame//PafosGame//assets//Textures//sand.jpg", &texture, &ShaderTexView);

    ModelReader myModelReader = ModelReader("untitled.fbx");

    myModelReader.PrintNode();

    // Main message loop
     MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            myD3DManager.getDeviceContext()->RSSetViewports(1, &viewport);
            myD3DManager.getDeviceContext()->ClearRenderTargetView(myD3DManager.getRenderTarget(), backColor);
            myD3DManager.getDeviceContext()->ClearRenderTargetView(renderTex, color);

            myD3DManager.getDeviceContext()->PSSetSamplers(0, 1, &texFiltiringInformation);
            myD3DManager.getDeviceContext()->PSSetShaderResources(1, 1, &ShaderTexView);

            myRenderUI.render();
            myRenderer.update();
            myCube.Draw();
            myRenderer.render(myShaders,renderTex);

            ImGui::Image(my_tex, ImGui::GetWindowSize());

            myRenderUI.update(g_mainRenderTargetView);



            myD3DManager.getDeviceSwapchain()->Present(0, 0);
        }
    }

    return (int)msg.wParam;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            std::cout << "resized" << std::endl;

            if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);

            ID3D11Texture2D* pBackBuffer;
            g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
            g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
            pBackBuffer->Release();
        }
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

