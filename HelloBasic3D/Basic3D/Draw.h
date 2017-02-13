#pragma once
#include "Basic3D.h"

namespace Basic3D
{
	class SceneObject;
	class Vector3;
	class Vector2;
	struct Colour;

	namespace Draw
	{
		BASIC3D_API void DrawModel(SceneObject * sceneObject);
		BASIC3D_API void DrawString(const char * text, Colour colour, Vector3 position, Vector2 rasterPos);
		BASIC3D_API void DrawCube(int size, Colour colour, Vector3 position);
	}
}

