#include "Camera.h"

Camera::Camera()
{

}

void Camera::render()
{
	
}

Camera::~Camera()
{

}

DirectX::XMFLOAT3 Camera::getCameraPos()
{
	return DirectX::XMFLOAT3(this->posX, this->posY, this->posZ);
}