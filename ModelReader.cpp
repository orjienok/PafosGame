#include "ModelReader.h"
#include <iostream>

ModelReader::ModelReader(const char* fileName)
{
	bool hr = false;
	this->m_pFbxManager = FbxManager::Create();
	FbxIOSettings* ios = FbxIOSettings::Create(this->m_pFbxManager, IOSROOT);
	this->m_pFbxManager->SetIOSettings(ios);
	FbxImporter* lImporter = FbxImporter::Create(this->m_pFbxManager, "");
	hr = lImporter->Initialize(fileName, -1, ios);
	
	lScene = FbxScene::Create(this->m_pFbxManager, "myScene");
	lImporter->Import(lScene);
	lImporter->Destroy();
}

ModelReader::~ModelReader()
{
	
}

void ModelReader::PrintNode()
{
	FbxNode* lRootNode = lScene->GetRootNode();
	if (lRootNode)
	{
		for (int i = 0; i < lRootNode->GetChildCount(); i++)
		{
			std::cout << lRootNode->GetChild(i)->GetName() << std::endl;
			for (size_t x = 0; x < lRootNode->GetChild(i)->GetMaterialCount(); x++)
			{
				std::cout << "\t" << lRootNode->GetChild(i)->GetMesh()->GetName() << std::endl;
				std::cout << "\t\t" << lRootNode->GetChild(i)->GetMaterial(x)->GetName() << std::endl;
				for (size_t y = 0; y < FbxLayerElement::sTypeTextureCount; y++)
				{
					std::cout << "\t\t\t" << lRootNode->GetChild(i)->GetMaterial(x)->FindProperty(FbxLayerElement::sTextureChannelNames[y]).GetName() << std::endl;
					for (size_t z = 0; z < lRootNode->GetChild(i)->GetMaterial(x)->FindProperty(FbxLayerElement::sTextureChannelNames[y]).GetSrcObjectCount<FbxFileTexture>(); z++)
					{
						std::cout << "\t\t\t\t" <<lRootNode->GetChild(i)->GetMaterial(x)->FindProperty(FbxLayerElement::sTextureChannelNames[y]).GetSrcObject<FbxFileTexture>()->GetFileName() << std::endl;
					}
				}
			}
		}
	}
}

const char* ModelReader::EnumSender(FbxNodeAttribute::EType unit)
{
	switch (unit)
	{
	case fbxsdk::FbxNodeAttribute::eUnknown:
		return "Unknown";
	case fbxsdk::FbxNodeAttribute::eNull:
		return "Null";
	case fbxsdk::FbxNodeAttribute::eMarker:
		return "Marker";
	case fbxsdk::FbxNodeAttribute::eSkeleton:
		return "Skeleton";
	case fbxsdk::FbxNodeAttribute::eMesh:
		return "Mesh";
	case fbxsdk::FbxNodeAttribute::eNurbs:
		return "Nurbs";
	case fbxsdk::FbxNodeAttribute::ePatch:
		return "Patch";
	case fbxsdk::FbxNodeAttribute::eCamera:
		return "Camera";
	case fbxsdk::FbxNodeAttribute::eLight:
		return "Light";
	case fbxsdk::FbxNodeAttribute::eShape:
		return "Shape";
	case fbxsdk::FbxNodeAttribute::eLODGroup:
		return "LODGroup";
	case fbxsdk::FbxNodeAttribute::eSubDiv:
		return "SubDiv";
	case fbxsdk::FbxNodeAttribute::eLine:
		return "Line";
	default:
		return "not found";
	}
}