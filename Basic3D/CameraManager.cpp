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

		void CameraManager::Initialise()
		{
			glutReshapeFunc(Reshape);
		}

		void CameraManager::Destroy()
		{
			glutReshapeFunc(nullptr);
		}

		void CameraManager::AddCamera(Camera* camera)
		{
			_cameras[camera->name] = camera;
		}

		void CameraManager::AddCamera(Vector3* eye, Vector3* center, Vector3* up, Perspective* perspective, char * name)
		{
			_cameras[name] = new Camera(eye, center, up, perspective, name);
		}

		Camera* CameraManager::RetrieveCamera(char * camName)
		{
			if (_cameras.count(camName) > 0)
				return _cameras[camName];
			return nullptr;
		}

		void CameraManager::DeleteCamera(char * camName)
		{
			if (_cameras.count(camName) > 0)
				_cameras.erase(camName);
		}

		void CameraManager::ClearAllCameras()
		{
			_cameras.clear();
		}

		void CameraManager::SetActiveCamera(char * camName)
		{
			_activeCamera = _cameras[camName];
		}

		void CameraManager::SetActiveCamera(Camera * camera)
		{
			_activeCamera = camera;
		}

		Camera * CameraManager::GetActiveCamera()
		{
			return _activeCamera;
		}

		void CameraManager::UpdateActiveCamera()
		{
			_activeCamera->LookAt();
			_activeCamera->Update();
		}

		int CameraManager::GetViewportWidth()
		{
			return _viewportWidth;
		}

		int CameraManager::GetViewportHeight()
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
