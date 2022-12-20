#pragma once
#include <d3d11.h>

class D3DManager
{
public:
	D3DManager(HWND hWnd);

	void InitD3D(HWND hWnd);

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
	IDXGISwapChain* getDeviceSwapchain();
	void getDeviceName();



	~D3DManager();
private:
	IDXGISwapChain* swapchain;             // the pointer to the swap chain interface
	ID3D11Device* dev;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext* devcon;		   // the pointer to our Direct3D device context

	IDXGIDevice* pDXGIDevice;
	IDXGIAdapter* pDXGIAdapter;
};

