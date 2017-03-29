#include "Transforms.h"


CharacterMovement::CharacterMovement() : Transform(), walk(0.0f), run(0.0f)
{
}

void CharacterMovement::Foreward()
{
	position.x -= sin(BasicMath::DegreesToRadians(heading)) * walk;
	position.z -= cos(BasicMath::DegreesToRadians(heading)) * walk;
}

void CharacterMovement::Backward()
{
	position.x += sin(BasicMath::DegreesToRadians(heading)) * walk;
	position.z += cos(BasicMath::DegreesToRadians(heading)) * walk;
}

void CharacterMovement::Left()
{
	position.x -= sin(BasicMath::DegreesToRadians(heading + 90.0f)) * walk;
	position.z -= cos(BasicMath::DegreesToRadians(heading + 90.0f)) * walk;
}

void CharacterMovement::Right()
{
	position.x += sin(BasicMath::DegreesToRadians(heading + 90.0f)) * walk;
	position.z += cos(BasicMath::DegreesToRadians(heading + 90.0f)) * walk;
}

void CharacterMovement::Run()
{
	position.x -= sin(BasicMath::DegreesToRadians(heading)) * run;
	position.z -= cos(BasicMath::DegreesToRadians(heading)) * run;
}

Joint::Joint() : Transform(), jointPitch(0.0f), jointHeading(0.0f), jointRoll(0.0f), joint(Vector3())
{
}

void Joint::Update()
{
	glTranslatef(position.x, position.y, position.z);
	glScalef(scale.x, scale.y, scale.z);
	glRotatef(pitch, 1, 0, 0); // rotates around center.
	glRotatef(heading, 0, 1, 0); // rotates around center.
	glRotatef(roll, 0, 0, 1); // rotates around center.

	glTranslatef(joint.x, joint.y, joint.z);
	glRotatef(jointPitch, 1, 0, 0);
	glRotatef(jointHeading, 0, 1, 0);
	glRotatef(jointRoll, 0, 0, 1);
	glTranslatef(-joint.x, -joint.y, -joint.z);
}

Animate::Animate(GLfloat speed) : Joint(), speed(speed), startStop(false)
{
}

void Animate::Update()
{
	Joint::Update();
	if (!startStop)
	{
		jointPitch = 0.0f;
		return;
	}

	if (jointPitch >= 45.0f || jointPitch <= -45.0f)
		speed = -speed;

	jointPitch += speed;
}
