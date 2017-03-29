#include "stdafx.h"
#include "Director.h"

namespace Basic3D
{
	namespace Director
	{
		namespace
		{
			Scene* _scene = nullptr;
			Scene* _nextScene = nullptr;
			Colour* _clearColour = nullptr;
			std::vector<SceneObject*> _objects;
			std::vector<Lighting> _lights;
		}

		void Destroy();
		void Display();
		void Tick(int preferredRefresh);
		void Update(int updateTime);

		void Director::Initialise(int argc, char *argv[], Scene* initScene, int windowX, int windowY,
								  int viewportWidth, int viewportHeight, Colour* clearColour,
								  const char * windowTitle, int preferredFPS)
		{
			int refreshRate = 1000 / preferredFPS;
			_scene = initScene;

			glutInitDisplayMode(GLUT_DOUBLE);
			glutInit(&argc, argv);	
			glutInitWindowSize(viewportWidth, viewportHeight);
			glutInitWindowPosition(windowX, windowY);
			glutCreateWindow(windowTitle);
			glutDisplayFunc(Display);
			glutTimerFunc(refreshRate, Director::Tick, refreshRate);		

			if (clearColour != nullptr)
				_clearColour = clearColour;
			else
				_clearColour = new Colour(0.5f, 0.8f, 0.9f, 1.0f);

			glClearColor(_clearColour->r, _clearColour->g, _clearColour->b, _clearColour->a);
			glShadeModel(GL_SMOOTH);

			glMatrixMode(GL_MODELVIEW);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glEnable(GL_TEXTURE);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_NORMALIZE);
			glEnable(GL_LIGHTING);
			glCullFace(GL_BACK);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);

			_scene->LoadContent();

			glutMainLoop();
		}

		void Director::AddChild(SceneObject* child)
		{
			_objects.push_back(child);
		}

		void Director::AddLight(Lighting light)
		{
			glEnable(light.lightNumber);
			_lights.push_back(light);
		}

		void EmptyScene()
		{
			RemoveChildren();
			RemoveLights();
		}

		void SetClearColour(Colour* colour)
		{
			_clearColour = colour;
		}

		bool Director::RemoveChildAtIndex(unsigned int index)
		{
			if (index > _objects.size())
			{
				return false;
			}
			_objects.erase(_objects.begin() + index);
			return true;
		}

		void RemoveChildren()
		{
			if (!_objects.empty())
				_objects.clear();
		}

		void RemoveLights()
		{
			for (auto light : _lights)
				glDisable(light.lightNumber);

			if (!_lights.empty())
				_lights.clear();
		}

		void Director::ReplaceScene(Scene* newScene)
		{
			if (_scene != nullptr)
			{
				_nextScene = newScene;
			}
		}

		unsigned int Director::GetNumberOfChildren()
		{
			return _objects.size();
		}

		SceneObject* Director::GetChildAtIndex(unsigned int index)
		{
			if (index > _objects.size())
				return nullptr;
			return _objects[index];
		}

		Colour* Director::GetClearColour()
		{
			return _clearColour;
		}

		int Director::GetViewportWidth()
		{
			return CameraManager::GetViewportWidth();
		}

		int Director::GetViewportHeight()
		{
			return CameraManager::GetViewportHeight();
		}

		// Private Director Functions
		void Destroy()
		{
			EmptyScene();
			delete _scene;
		}

		void Display()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if(_scene != nullptr)
				_scene->Draw();

			for (auto sceneObject : _objects)
				Draw::DrawModel(sceneObject);

			glutSwapBuffers();
		}

		void Tick(int preferredRefresh)
		{
			int updateTime = glutGet(GLUT_ELAPSED_TIME);
			Update(updateTime);
			updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
			glutTimerFunc(preferredRefresh - updateTime, Director::Tick, preferredRefresh);
		}

		void Update(int updateTime)
		{
			if (_nextScene != nullptr)
			{
				EmptyScene();
				_scene = _nextScene;
				_scene->LoadContent();
				_nextScene = nullptr;
			}

			glLoadIdentity();

			if (_scene != nullptr)
				_scene->Update(updateTime);

			for (auto light : _lights)
			{
				glLightfv(light.lightNumber, GL_AMBIENT, &light.ambient.x);
				glLightfv(light.lightNumber, GL_DIFFUSE, &light.diffuse.x);
				glLightfv(light.lightNumber, GL_SPECULAR, &light.specular.x);
				glLightfv(light.lightNumber, GL_POSITION, &light.position.x);
			}

			glutPostRedisplay();
		}
	}
}
