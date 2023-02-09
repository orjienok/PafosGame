#pragma once
#include <fbxsdk.h>
#include "geometry/Vertex.h"
#include <vector>
class ModelReader
{
public:
	ModelReader(const char*);
	void PrintNode();
	const char* EnumSender(FbxNodeAttribute::EType unit);
	~ModelReader();
private:
	FbxManager* m_pFbxManager;
	FbxScene* lScene;
	std::vector<Vertex> vertices;
};

