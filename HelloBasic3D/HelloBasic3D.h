#pragma once
#include "Transforms.h"
#include "SecondScene.h"
#include "Cameras.h"

using namespace std;
using namespace Basic3D;


class HelloBasic3D : public Scene
{
private:
	SceneObject* ground;
	SceneObject* stickMan;

	CharacterMovement* origin;
	Animate* rightLeg;
	Animate* leftLeg;
	Animate* rightArm;
	Animate* leftArm;

	ThirdPersonCamera* cam;

public:
	HelloBasic3D();
	~HelloBasic3D();
	void LoadContent();
	void Update(int timeStep);
	void Draw();
	void Keyboard(Input::KeyboardState * state);
	void Mouse(Input::MouseState * state);
};

