#pragma once
#include "Core/SimpleMath.h"
class Light
{
public:
	Light();
	~Light();
private:
	DirectX::SimpleMath::Vector3 position;
	float intensive;
};

