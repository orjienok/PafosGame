#include <DirectXMath.h>
class Camera
{
public:
	Camera();

	DirectX::XMFLOAT3 getCameraPos();

	void render();

	~Camera();
private:
	float posX, posY, posZ;
};