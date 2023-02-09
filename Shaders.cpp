#include "Shaders.h"


Shaders::Shaders(D3DManager* d3dmanager)
{
    this->d3dmanager = d3dmanager;
}

Shaders::~Shaders()
{

}



void Shaders::createVertexShaderFromFile(LPCWSTR FileToShader)
{
    ID3DBlob* CompiledCodeOfVertexShader;
    ID3DBlob* Err;

	D3DCompileFromFile(FileToShader, NULL, NULL, "main", "vs_4_0", NULL, NULL, &CompiledCodeOfVertexShader, &Err);
 

    D3D11_INPUT_ELEMENT_DESC iaDesc[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        {"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
    };

    d3dmanager->getDevice()->CreateVertexShader(CompiledCodeOfVertexShader->GetBufferPointer(), CompiledCodeOfVertexShader->GetBufferSize(), NULL, &vertexShader);
    d3dmanager->getDevice()->CreateInputLayout(iaDesc, ARRAYSIZE(iaDesc), CompiledCodeOfVertexShader->GetBufferPointer(), CompiledCodeOfVertexShader->GetBufferSize(), &in_layout);
}

void Shaders::createPixelShaderFromFile(LPCWSTR FileToShader)
{
    ID3DBlob* CompiledCodeOfPixelShader;
    ID3DBlob* Err;
	D3DCompileFromFile(FileToShader, NULL, NULL, "main", "ps_4_0", NULL, NULL, &CompiledCodeOfPixelShader, &Err);

    d3dmanager->getDevice()->CreatePixelShader(CompiledCodeOfPixelShader->GetBufferPointer(), CompiledCodeOfPixelShader->GetBufferSize(), NULL, &pixelShader);
}


ID3D11VertexShader* Shaders::getVertexShader()
{
    return this->vertexShader;
}
ID3D11PixelShader* Shaders::getPixelShader()
{
    return this->pixelShader;
}

ID3D11InputLayout* Shaders::getInpuLayout()
{
    return this->in_layout;
}