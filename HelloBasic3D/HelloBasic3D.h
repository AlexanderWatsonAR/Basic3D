#pragma once
#include "Transforms.h"

using namespace std;
using namespace Basic3D;

class ThirdPersonCamera : public Camera
{
public:
	GLfloat heading;
	GLfloat distance;
	GLfloat offset;

	ThirdPersonCamera(Vector3* eye, Vector3* center, Vector3* up, Perspective* p,
	char * name, GLfloat distance, GLfloat offset) : Camera(eye, center, up, p, name), distance(distance), offset(offset) {}

	inline void Update()
	{
		Vector3 direction;
		direction.x = sin(BasicMath::DegreesToRadians(heading)) * distance;
		direction.y = offset;
		direction.z = cos(BasicMath::DegreesToRadians(heading)) * distance;
		Vector3 pos = *center;
		eye = new Vector3(pos + direction);
	}
};


class HelloBasic3D : public Scene
{
private:
	SceneObject* ground;
	SceneObject* stickMan;

	CharacterTransform* origin;
	AnimateTransform* rightLeg;
	AnimateTransform* leftLeg;
	AnimateTransform* rightArm;
	AnimateTransform* leftArm;

	Model* groundModel;
	ThirdPersonCamera* cam;
	GLuint cubeMeshID;
	GLuint planeMeshID;
	GLuint plane15x15MeshID;
	Material material;
	Texture2D* blueTexture;
	Texture2D* redTexture;
	Texture2D* skinTexture;
	Texture2D* groundTexture;

public:
	HelloBasic3D(int argc, char* argv[]);
	~HelloBasic3D();
	void LoadContent();
	void Update(int timeStep);
	void Draw();
	void Keyboard(Input::KeyboardState * state);
	void Mouse(Input::MouseState * state);
};

