#pragma once
#include "Basic3D/Basic3D.h"
#include "Cameras.h"
#include "Transforms.h"

using namespace std;
using namespace Basic3D;

class SecondScene : public Scene
{
private:
	SceneObject* ground;
	SceneObject* tree;
	ThirdPersonCamera* cam;
	Joint* topLeftBranchTransform;
public:
	SecondScene();
	~SecondScene();
	void LoadContent();
	void Draw();
	void Update(int timeStep);
	void Keyboard(Input::KeyboardState* state);
	void Mouse(Input::MouseState* state);
};

