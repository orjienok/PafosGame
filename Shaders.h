#pragma once
#include "Core/D3DManager.h"
#include <d3dcompiler.h>
#include <iostream>

class Shaders
{
public:
	Shaders(D3DManager*);
	void createVertexShaderFromFile(LPCWSTR);
	void createPixelShaderFromFile(LPCWSTR);
	void createInputLayout();
	ID3D11VertexShader* getVertexShader();
	ID3D11PixelShader* getPixelShader();
	ID3D11InputLayout* getInpuLayout();

	~Shaders();
private:
	D3DManager* d3dmanager;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* in_layout;
};

