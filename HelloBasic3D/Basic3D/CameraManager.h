#pragma once
#include "Basic3D.h"

namespace Basic3D
{
	class Vector3;
	class Camera;
	class Perspective;
	namespace CameraManager
	{
		BASIC3D_API void Initialise();
		BASIC3D_API void AddCamera(Camera* camera);
		BASIC3D_API void AddCamera(Vector3* eye, Vector3* center, Vector3* up, Perspective* perspective, char * name);
		BASIC3D_API Camera* RetrieveCamera(char * camName);
		BASIC3D_API void DeleteCamera(char * camName);
		BASIC3D_API void SetActiveCamera(char * camName);
		BASIC3D_API void SetActiveCamera(char * camName);
		BASIC3D_API Camera * GetActiveCamera();
		BASIC3D_API void UpdateActiveCamera();
		int GetViewportWidth();
		int GetViewportHeight();
	};
}

