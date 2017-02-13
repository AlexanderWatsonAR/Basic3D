#pragma once

#include "Basic3D\Basic3D.h"

using namespace std;
using namespace Basic3D;

class HelloBasic3D : public Scene
{
private:
	SceneObject* ground;
	SceneObject* grandParent;
	SceneObject* parent;
	SceneObject* child;

	Model* groundModel;
	Model* crateModel;
	Camera* cam;
	GLuint cubeMeshID;
	GLuint planeMeshID;
	Material material;
	Texture2D* crateTexture;
	Texture2D* groundTexture;

public:
	HelloBasic3D(int argc, char* argv[]);
	~HelloBasic3D();
	void LoadContent();
	void Update(int timeStep);
	void Draw();
	void Keyboard(Input::KeyboardState * state);
};

