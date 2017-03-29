#include "Cameras.h"

void ThirdPersonCamera::Update()
{
	Vector3 direction;
	direction.x = sin(BasicMath::DegreesToRadians(heading)) * distance;
	direction.y = offset;
	direction.z = cos(BasicMath::DegreesToRadians(heading)) * distance;
	Vector3 pos = *center;
	eye = new Vector3(pos + direction);
}
