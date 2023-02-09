#pragma once
#include <d3d11.h>
#include "Window.h"

class D3DManager
{
public:
	D3DManager(Window&);

	void InitD3D(Window&);

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
	IDXGISwapChain* getDeviceSwapchain();
	ID3D11RenderTargetView* getRenderTarget();

	void getDeviceName();



	~D3DManager();
private:
	IDXGISwapChain* swapchain;             // the pointer to the swap chain interface
	ID3D11Device* dev;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext* devcon;// the pointer to our Direct3D device context

	ID3D11RenderTargetView* m_renderTarget;

	IDXGIDevice* pDXGIDevice;
	IDXGIAdapter* pDXGIAdapter;
};

