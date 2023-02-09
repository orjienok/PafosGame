#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(const void* data, UINT sizeOfData, D3DManager* d3dmanager)
{
	this->m_pd3dmanager = d3dmanager;

	InitBuffer(data, sizeOfData);
}

ConstantBuffer::~ConstantBuffer()
{

}

ID3D11Buffer* ConstantBuffer::getConstantBuffer()
{
	return this->m_pConstantBuffer;
}

void ConstantBuffer::InitBuffer(const void* data,UINT sizeOfData)
{
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeOfData;
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = data;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	HRESULT hr = m_pd3dmanager->getDevice()->CreateBuffer(&cbDesc, &InitData,&m_pConstantBuffer);

}

void ConstantBuffer::setBuffer()
{
	m_pd3dmanager->getDeviceContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pd3dmanager->getDeviceContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
}