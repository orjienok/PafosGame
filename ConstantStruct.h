#pragma once
#include <DirectXMath.h>
struct vs_constant_buffer
{
	DirectX::XMFLOAT4X4 world;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
	DirectX::XMFLOAT4 LightDir;
};