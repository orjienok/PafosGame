#pragma once
#include "Core/D3DManager.h"
#include "ConstantBuffer.h"
#include "Core/SimpleMath.h"
#include "geometry/GeometryPrimitive.h"
#include "Core/Window.h"
#include "ConstantStruct.h"
#include "Shaders.h"

class Renderer
{
public:
	Renderer(D3DManager*,Window&);


	void render(ID3D11RenderTargetView* renderTarget);
	void render(Shaders&, ID3D11RenderTargetView*);

	void update();

	~Renderer();
private:
	D3DManager* d3dmanager;
	vs_constant_buffer vs_constant_buffer;
	ID3D11Buffer* m_pConstantBuffer;
	UINT m_frameCount;
};

