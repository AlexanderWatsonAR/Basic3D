#pragma once

#include "Basic3D.h"

namespace Basic3D
{
	class Scene;
	class SceneObject;
	class SGnode;
	class Vector3;
	class Lighting;
	class Material;
	class Texture2D;
	struct Colour;

	namespace Director
	{
		BASIC3D_API void Initialise(int argc, char *argv[], Scene * initGame, int windowX, int windowY,
									int viewportWidth, int viewportHeight, Colour* clearColour,
									const char * windowTitle, int preferredFPS);
		BASIC3D_API void ReplaceScene(Scene* newScene);
		BASIC3D_API void AddChild(GLuint meshID, Texture2D * tex, Material material);
		BASIC3D_API void AddChild(SceneObject* child);
		BASIC3D_API void AddLight(Lighting light);
		BASIC3D_API void EmptyScene();
		BASIC3D_API bool RemoveChildAtIndex(unsigned int index);
		BASIC3D_API void RemoveChildren();
		BASIC3D_API void RemoveLights();

		BASIC3D_API SceneObject* GetChildAtIndex(unsigned int index);
		BASIC3D_API unsigned int GetNumberOfChildren();
		BASIC3D_API Colour* GetClearColour();
		BASIC3D_API int GetViewportHeight();
		BASIC3D_API int GetViewportWidth();
	}
}


