#pragma once
#include "Basic3D.h"

namespace Basic3D
{
	class Perspective;
	class Vector3;
	class BASIC3D_API Camera
	{
	public:
		Vector3 *eye, *center, *up;
		Perspective* perspective;
		const char * name;

		Camera(Vector3* eye, Vector3* center, Vector3* up, Perspective* perspective, char * camName);
		virtual void Update();
		void LookAt();
		void Reshape(int width, int height);
	};
}

