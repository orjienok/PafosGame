#include "Renderer.h"

Renderer::Renderer(D3DManager* d3dmanager,Window& window)
{
	this->d3dmanager = d3dmanager;

	vs_constant_buffer.world = DirectX::SimpleMath::Matrix();
	DirectX::SimpleMath::Vector3 Eye = DirectX::SimpleMath::Vector3(0.0f, 1.0f, -5.0f);
	DirectX::SimpleMath::Vector3 At = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
	DirectX::SimpleMath::Vector3 Up = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);

	DirectX::SimpleMath::Vector4 lighDIR = DirectX::SimpleMath::Vector4(0.0f, 0.0f, -1.0f, 1.0f);
	//vs_constant_buffer.view = DirectX::SimpleMath::Matrix::CreateLookAt(myEye,At,Up);
	//DirectX::XMVECTOR Eye = DirectX::XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
	//DirectX::XMVECTOR At = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	DirectX::XMStoreFloat4x4(&vs_constant_buffer.view,DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(Eye, At, Up)));
	DirectX::XMStoreFloat4x4(&vs_constant_buffer.projection,DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, window.getClientWidth() / (FLOAT)window.getClientHeight(), 0.01f, 100.0f)));
	DirectX::XMStoreFloat4(&vs_constant_buffer.LightDir,lighDIR);

	ConstantBuffer myConstantBuffer(&vs_constant_buffer,sizeof(vs_constant_buffer),d3dmanager);

	

	std::cout << myConstantBuffer.getConstantBuffer() << std::endl;

	this->m_pConstantBuffer = myConstantBuffer.getConstantBuffer();
}

void Renderer::render(Shaders& shader, ID3D11RenderTargetView* renderTarget)
{
	ID3D11DeviceContext* context = d3dmanager->getDeviceContext();

	context->UpdateSubresource(m_pConstantBuffer, 0, 0, &vs_constant_buffer, 0, 0);

	context->OMSetRenderTargets(1, &renderTarget, NULL);

	context->IASetInputLayout(shader.getInpuLayout());

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->VSSetShader(shader.getVertexShader(), NULL, 0);

	D3D11_BUFFER_DESC des;

	m_pConstantBuffer->GetDesc(&des);

	context->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	context->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	context->PSSetShader(shader.getPixelShader(), NULL, 0);

	d3dmanager->getDeviceContext()->DrawIndexed(36, 0, 0);
}

void Renderer::render(ID3D11RenderTargetView* renderTarget)
{
	ID3D11DeviceContext* context = d3dmanager->getDeviceContext();
	context->OMSetRenderTargets(1, &renderTarget, NULL);
}

Renderer::~Renderer()
{

}

void Renderer::update()
{
	
	static float t = 0.0f;

	static ULONGLONG timeStart = 0;
	ULONGLONG timeCur = GetTickCount64();
	if (timeStart == 0)
		timeStart = timeCur;
	t = (timeCur - timeStart) / 1000.0f;

	DirectX::XMStoreFloat4x4(&vs_constant_buffer.world,
		DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationY(t)));
}