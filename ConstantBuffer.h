#pragma once
#include "Core/D3DManager.h"
#include <DirectXMath.h>
#include <iostream>
class ConstantBuffer
{
public:
	ConstantBuffer(const void* data, UINT sizeOfData, D3DManager* d3dmanager);

	ID3D11Buffer* getConstantBuffer();
	void InitBuffer(const void* data, UINT sizeOfData);

	void setBuffer();

	void update();

	~ConstantBuffer();
private:
	ID3D11Buffer* m_pConstantBuffer;
	D3DManager* m_pd3dmanager;
};

