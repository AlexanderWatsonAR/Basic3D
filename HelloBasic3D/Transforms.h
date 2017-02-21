#pragma once
#include "Basic3D\Basic3D.h"
using namespace Basic3D;

class CharacterTransform : public Transform
{
public:
	GLfloat walk, run;

	CharacterTransform();

	void Foreward(); // Takes Degrees.
	void Backward(); // Takes Degrees.
	void Left(); // Takes Degrees.
	void Right(); // Takes Degrees.
	void Run(); // Takes Degrees.
};

class AnimateTransform : public Transform
{
public:
	GLfloat rotate, speed;
	bool startStop;
	Vector3 joint; // Joint is relative to last position.

	AnimateTransform(GLfloat speed);

	void Update();
};
