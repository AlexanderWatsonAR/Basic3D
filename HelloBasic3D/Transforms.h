#pragma once
#include "Basic3D\Basic3D.h"
using namespace Basic3D;

class CharacterMovement : public Transform
{
public:
	GLfloat walk, run;

	CharacterMovement();

	void Foreward(); // Takes Degrees.
	void Backward(); // Takes Degrees.
	void Left(); // Takes Degrees.
	void Right(); // Takes Degrees.
	void Run(); // Takes Degrees.
};

class Joint : public Transform
{
public:
	Vector3 joint; // Joint is relative to last position.
	GLfloat jointPitch, jointHeading, jointRoll; 
	Joint();

	void Update();
};

class Animate : public Joint
{
public:
	GLfloat speed;
	bool startStop;

	Animate(GLfloat speed);
	void Update();
};
