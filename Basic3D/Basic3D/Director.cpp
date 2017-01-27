#include "stdafx.h"
#include "Director.h"

namespace Basic3D
{
#define DEFAULT_CLEARCOLOUR Colour(0.5f, 0.8f, 0.9f, 1.0f) // Sky Blue.
#define DEFAULT_PERSPECTIVE Perspective(45, 1, 0.1, 500) // Aspect assumes window is square.
#define ONE_SECOND 1000 // ms.

	namespace Director
	{
		namespace
		{
			Camera* _activeCamera = nullptr;
			Scene* _scene = nullptr;
			std::vector<SceneObject*> _objects;
			std::vector<Lighting> _lights;
			Perspective* _perspective = nullptr;
			Colour* _clearColour = nullptr;
			int _viewportWidth, _viewportHeight;
		}

		void Destroy();
		void Display();
		void Keyboard(unsigned char key, int x, int y);
		void Reshape(int width, int height);
		void MousePress(int button, int state, int x, int y);
		void MouseMove(int x, int y);
		void Tick(int preferredRefresh);
		void Update(int updateTime);

		void Director::Initialise(int argc, char *argv[], Scene * initScene, int windowX, int windowY,
								  int viewportWidth, int viewportHeight, Perspective* perspective,
								  Colour* clearColour, const char * windowTitle, int preferredFPS)
		{
			int refreshRate = ONE_SECOND / preferredFPS;
			_scene = initScene;
			_viewportWidth = viewportWidth;
			_viewportHeight = viewportHeight;

			glutInitDisplayMode(GLUT_DOUBLE);
			glutInit(&argc, argv);
			glutInitWindowSize(_viewportWidth, _viewportHeight);
			glutInitWindowPosition(windowX, windowY);

			glutCreateWindow(windowTitle);
			glutDisplayFunc(Display);
			glutTimerFunc(refreshRate, Director::Tick, refreshRate);
			glutReshapeFunc(Reshape);
			glutKeyboardFunc(Keyboard);
			glutMouseFunc(MousePress);
			glutMotionFunc(MouseMove);
			if (clearColour != nullptr)
			{
				_clearColour = clearColour;
			}
			else
			{
				_clearColour = new DEFAULT_CLEARCOLOUR;
			}

			glClearColor(_clearColour->r, _clearColour->g, _clearColour->b, _clearColour->a);
			glShadeModel(GL_SMOOTH);
			glLoadIdentity();
			glMatrixMode(GL_PROJECTION);
			glViewport(0, 0, _viewportWidth, _viewportHeight);
			if (perspective != nullptr)
			{
				_perspective = perspective;
			}
			else
			{
				if (_viewportHeight != _viewportWidth)
					_perspective = new Perspective(DEFAULT_PERSPECTIVE.fieldOfView, _viewportWidth / (GLdouble)_viewportHeight, DEFAULT_PERSPECTIVE.nearPlane, DEFAULT_PERSPECTIVE.farPlane);
				else
					_perspective = new DEFAULT_PERSPECTIVE;
			}

			gluPerspective(_perspective->fieldOfView, _perspective->aspect, _perspective->nearPlane, _perspective->farPlane);

			glMatrixMode(GL_MODELVIEW);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glEnable(GL_TEXTURE);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_NORMALIZE);
			//glEnable(GL_LIGHT0); -- lights enabled when a light is added 
			glEnable(GL_LIGHTING);
			glCullFace(GL_BACK);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);

			_scene->LoadContent();

			glutMainLoop();
		}

		void Director::AddChild(GLuint meshID, GLuint texID, Material material)
		{
			SceneObject * child = new SceneObject(meshID, texID, material);
			child->scale = Vector3(1.0f, 1.0f, 1.0f);
			_objects.push_back(child);
		}

		void Director::AddChild(SceneObject* child)
		{
			_objects.push_back(child);
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

		void Director::AddLight(Lighting light)
		{
			glEnable(light.lightNumber);
			_lights.push_back(light);
		}

		void Director::ReplaceScene(Scene * newScene)
		{
			if (_scene != nullptr)
			{
				EmptyScene();
				_scene = newScene;
				_scene->LoadContent();
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

		void Director::SetActiveCamera(Camera* camera)
		{
			_activeCamera = camera;
		}

		Camera * Director::GetActiveCamera()
		{
			return _activeCamera;
		}

		Perspective * Director::GetPerspective()
		{
			return _perspective;
		}

		Colour* Director::GetClearColour()
		{
			return _clearColour;
		}

		int Director::GetViewportHeight()
		{
			return _viewportHeight;
		}

		int Director::GetViewportWidth()
		{
			return _viewportWidth;
		}

		// Private Director Functions
		void Tick(int preferredRefresh)
		{
			int updateTime = glutGet(GLUT_ELAPSED_TIME);
			Update(updateTime);
			updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
			glutTimerFunc(preferredRefresh - updateTime, Director::Tick, preferredRefresh);
		}

		void EmptyScene()
		{
			RemoveChildren();
			RemoveLights();
		}

		void Destroy()
		{
			EmptyScene();
			delete _scene;
			delete _activeCamera;
			delete _clearColour;
			delete _perspective;
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

		void Reshape(int width, int height)
		{
			_viewportHeight = height;
			_viewportWidth = width;
			glLoadIdentity();
			glMatrixMode(GL_PROJECTION);
			glViewport(0, 0, _viewportWidth, _viewportHeight);
			gluPerspective(_perspective->fieldOfView, width / (GLdouble)height, _perspective->nearPlane, _perspective->farPlane);
			glMatrixMode(GL_MODELVIEW);
		}

		void Display()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			_scene->Draw();

			for (auto sceneObject : _objects)
				Draw::DrawModel(sceneObject);

			glFlush();
			glutSwapBuffers();
		}
		void Update(int updateTime)
		{
			glLoadIdentity();

			_scene->Update(updateTime);

			gluLookAt(_activeCamera->eye.x, _activeCamera->eye.y, _activeCamera->eye.z,
				_activeCamera->center.x, _activeCamera->center.y, _activeCamera->center.z,
				_activeCamera->up.x, _activeCamera->up.y, _activeCamera->up.z);

			for (auto light : _lights)
			{
				glLightfv(light.lightNumber, GL_AMBIENT, &light.Ambient.x);
				glLightfv(light.lightNumber, GL_DIFFUSE, &light.Diffuse.x);
				glLightfv(light.lightNumber, GL_SPECULAR, &light.Specular.x);
				glLightfv(light.lightNumber, GL_POSITION, &light.Position.x);
			}

			glutPostRedisplay();
		}

		void Keyboard(unsigned char key, int x, int y)
		{
			_scene->Keyboard(key, x, y);
		}

		void MousePress(int button, int state, int x, int y)
		{
			_scene->MousePress(button, state, x, y);
		}

		void MouseMove(int x, int y)
		{
			_scene->MouseMove(x, y);
		}
	}
}
