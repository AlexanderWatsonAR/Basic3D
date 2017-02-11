#include "stdafx.h"
#include "CameraManager.h"
#include <map>

namespace Basic3D
{
	namespace CameraManager
	{
		namespace
		{
			std::map<const char*, Camera*> _cameras;
			Camera* _activeCamera = nullptr;
			int _viewportWidth, _viewportHeight;
		}

		void Reshape(int width, int height);

		void Initialise()
		{
			glutReshapeFunc(Reshape);
		}

		void AddCamera(Camera* camera)
		{
			_cameras[camera->name] = camera;
		}

		void AddCamera(Vector3* eye, Vector3* center, Vector3* up, Perspective* perspective, char * name)
		{
			_cameras[name] = new Camera(eye, center, up, perspective, name);
		}

		Camera* RetrieveCamera(char * camName)
		{
			if (_cameras.count(camName) > 0)
				return _cameras[camName];
			return nullptr;
		}

		void DeleteCamera(char * camName)
		{
			if (_cameras.count(camName) > 0)
				_cameras.erase(camName);
		}

		void SetActiveCamera(char * camName)
		{
			_activeCamera = _cameras[camName];
		}

		Camera * GetActiveCamera()
		{
			return _activeCamera;
		}

		void UpdateActiveCamera()
		{
			_activeCamera->LookAt();
			_activeCamera->Update();
		}

		void SetActiveCamera(Camera * camera)
		{
			_activeCamera = camera;
		}

		int GetViewportWidth()
		{
			return _viewportWidth;
		}

		int GetViewportHeight()
		{
			return _viewportHeight;
		}

		// Private.
		void Reshape(int width, int height)
		{
			_viewportWidth = width;
			_viewportHeight = height;
			_activeCamera->Reshape(width, height);
		}

	}
}
