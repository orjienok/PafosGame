#pragma once
#include <d3d11.h>

class GPUManager
{
public:
	GPUManager(HWND hWnd);

	void InitD3D(HWND hWnd);

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
	IDXGISwapChain* getDeviceSwapchain();

	~GPUManager();
private:
	IDXGISwapChain* swapchain;             // the pointer to the swap chain interface
	ID3D11Device* dev;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext* devcon;		   // the pointer to our Direct3D device context
};

