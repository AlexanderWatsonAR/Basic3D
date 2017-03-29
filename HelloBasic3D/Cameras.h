#pragma once
#include "Basic3D\Basic3D.h"

using namespace Basic3D;

class ThirdPersonCamera : public Camera
{
public:
	GLfloat heading;
	GLfloat distance;
	GLfloat offset;

	ThirdPersonCamera(Vector3* eye, Vector3* center, Vector3* up, Perspective* p,
		char * name, GLfloat distance, GLfloat offset) : Camera(eye, center, up, p, name), distance(distance), offset(offset) {}

	void Update();
};