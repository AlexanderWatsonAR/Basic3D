#include "stdafx.h"
#include "Camera.h"

namespace Basic3D
{
	Camera::Camera(Vector3* eye, Vector3* center, Vector3* up, Perspective* perspective, char * camName) : eye(eye), center(center), up(up), perspective(perspective), name(camName)
	{
	}

	void Camera::LookAt()
	{
		glLoadIdentity();
		gluLookAt(eye->x, eye->y, eye->z, center->x, center->y, center->z, up->x, up->y, up->z);
	}

	void Camera::Update()
	{

	}

	void Camera::Reshape(int width, int height)
	{
		perspective->aspect = width / (GLdouble)height;
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(perspective->fieldOfView, perspective->aspect, perspective->nearPlane, perspective->farPlane);
		glMatrixMode(GL_MODELVIEW);
	}
}
