#pragma once

#include "Basic3D\Basic3D.h"

using namespace std;
using namespace Basic3D;

class HelloBasic3D : public Scene
{
private:
	SceneObject * crate;
	Camera * cam;
	GLuint meshID;
	Material material;

public:
	HelloBasic3D(int argc, char* argv[]);
	~HelloBasic3D();
	void LoadContent();
	void Update(int timeStep);
	void Draw();
	void Keyboard(unsigned char key, int x, int y);
};

