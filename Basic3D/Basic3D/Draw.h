#pragma once
#include "Basic3D.h"

namespace Basic3D
{
	class SceneObject;
	class Vector3;
	class Vector2;
	struct Colour;
	class BoundingBox;
	class SGnode;
	class Material;
	class Texture2D;
	namespace Draw
	{
		BASIC3D_API void DrawSGnodes(SGnode* node);
		BASIC3D_API void DrawModel(GLuint meshID, Texture2D* tex, Material material);
		BASIC3D_API void DrawModel(GLuint meshID, Texture2D* tex, Material material,
								   Vector3 position, Vector3 scale,
								   GLfloat heading, GLfloat pitch, GLfloat roll,
								   BoundingBox* box, bool billboard);
		BASIC3D_API void DrawModel(SceneObject * sceneObject);
		BASIC3D_API void DrawString(const char * text, Colour colour, Vector3 position, Vector2 rasterPos);
		BASIC3D_API void DrawCube(int size, Colour colour, Vector3 position);
	}
}

