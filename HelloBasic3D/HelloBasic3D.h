#pragma once

#include "Basic3D\Basic3D.h"

using namespace std;
using namespace Basic3D;

class ParentTransformation : public Transform
{
public:
	ParentTransformation() : Transform() {}

	inline void Update()
	{
		glTranslatef(position.x, position.y, position.z);
		glScalef(scale.x, scale.y, scale.z);
		glRotatef(heading, 0, 1, 0);
		glRotatef(pitch, 1, 0, 0);
		glRotatef(roll, 0, 0, 1);
	}
};

class HelloBasic3D : public Scene
{
private:
	SceneObject* ground;
	SceneObject* stickMan;

	Model* groundModel;
	Model* crateModel;
	Camera* cam;
	GLuint cubeMeshID;
	GLuint planeMeshID;
	Material material;
	Texture2D* crateTexture [2];
	Texture2D* groundTexture;

public:
	HelloBasic3D(int argc, char* argv[]);
	~HelloBasic3D();
	void LoadContent();
	void Update(int timeStep);
	void Draw();
	void Keyboard(Input::KeyboardState * state);
};

