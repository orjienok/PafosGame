#pragma once
#include "../Core/D3DManager.h"

class GeometryPrimitive
{
public:
	virtual void Draw() = 0;

protected:
	D3DManager* m_pd3dmanager;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	UINT m_indexCount;
};

