#pragma once
#include "Basic3D.h"

namespace Basic3D
{
	class SceneObject;
	class Vector3;
	namespace Draw
	{
		BASIC3D_API void DrawModel(const SceneObject * sceneObject);
		BASIC3D_API void DrawString(const char * text, Vector3 position);
	}
}

