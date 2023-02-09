#include "GeometryPrimitives.h"
#include "Vertex.h"

GeometryPrimitives::GeometryPrimitives(D3DManager* d3dmanager)
{
    this->m_pd3dmanager = d3dmanager;
}

void GeometryPrimitives::createCube()
{
	Vertex CubeVertices[] =
	{
		{-1.0f, 1.0f, -1.0f},
		{1.0f, 1.0f, -1.0f},
		{1.0f, 1.0f, 1.0f},
		{-1.0f, 1.0f, 1.0f},
		{-1.0f, -1.0f, -1.0f},
		{1.0f, -1.0f, -1.0f},
		{1.0f, -1.0f, 1.0f},
		{-1.0f, -1.0f, 1.0f}
	};

    CD3D11_BUFFER_DESC vDesc(
        sizeof(CubeVertices),
        D3D11_BIND_VERTEX_BUFFER
    );

    D3D11_SUBRESOURCE_DATA vData;
    ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
    vData.pSysMem = CubeVertices;
    vData.SysMemPitch = 0;
    vData.SysMemSlicePitch = 0;

    m_pd3dmanager->getDevice()->CreateBuffer(&vDesc, &vData, &vertexBuffer);

    unsigned short CubeIndices[] =
    {
        3,1,0,
        2,1,3,

        0,5,4,
        1,5,0,

        3,4,7,
        0,4,3,

        1,6,5,
        2,6,1,

        2,7,6,
        3,7,2,

        6,4,5,
        7,4,6,
    };
    
    m_indexCount = ARRAYSIZE(CubeIndices);

    CD3D11_BUFFER_DESC iDesc(
        sizeof(CubeIndices),
        D3D11_BIND_INDEX_BUFFER
    );

    D3D11_SUBRESOURCE_DATA iData;
    ZeroMemory(&iData, sizeof(D3D11_SUBRESOURCE_DATA));
    iData.pSysMem = CubeIndices;
    iData.SysMemPitch = 0;
    iData.SysMemSlicePitch = 0;

    m_pd3dmanager->getDevice()->CreateBuffer(&iDesc, &iData, &indexBuffer);
}

GeometryPrimitives::~GeometryPrimitives()
{

}

ID3D11Buffer* GeometryPrimitives::getVertexBuffer()
{
    return this->vertexBuffer;
}
ID3D11Buffer* GeometryPrimitives::getIndexBuffer()
{
    return this->indexBuffer;
}