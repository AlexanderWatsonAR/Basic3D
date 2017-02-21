#include "Transforms.h"


CharacterTransform::CharacterTransform() : Transform(), walk(0.0f), run(0.0f)
{
}

void CharacterTransform::Foreward()
{
	position.x -= sin(BasicMath::DegreesToRadians(heading)) * walk;
	position.z -= cos(BasicMath::DegreesToRadians(heading)) * walk;
}

void CharacterTransform::Backward()
{
	position.x += sin(BasicMath::DegreesToRadians(heading)) * walk;
	position.z += cos(BasicMath::DegreesToRadians(heading)) * walk;
}

void CharacterTransform::Left()
{
	position.x -= sin(BasicMath::DegreesToRadians(heading + 90.0f)) * walk;
	position.z -= cos(BasicMath::DegreesToRadians(heading + 90.0f)) * walk;
}

void CharacterTransform::Right()
{
	position.x += sin(BasicMath::DegreesToRadians(heading + 90.0f)) * walk;
	position.z += cos(BasicMath::DegreesToRadians(heading + 90.0f)) * walk;
}

void CharacterTransform::Run()
{
	position.x -= sin(BasicMath::DegreesToRadians(heading)) * run;
	position.z -= cos(BasicMath::DegreesToRadians(heading)) * run;
}

AnimateTransform::AnimateTransform(GLfloat speed) : Transform(), rotate(0.0f), speed(speed), startStop(false), joint(position)
{
}

void AnimateTransform::Update()
{
	glTranslatef(position.x, position.y, position.z);
	glScalef(scale.x, scale.y, scale.z);
	glRotatef(heading, 0, 1, 0);
	glRotatef(pitch, 1, 0, 0);
	glRotatef(roll, 0, 0, 1);
	if (!startStop)
		return;
	glTranslatef(joint.x, joint.y, joint.z);
	glRotatef(rotate, 1, 0, 0);
	glTranslatef(-joint.x, -joint.y, -joint.z);

	if (rotate >= 45.0f || rotate <= -45.0f)
	{
		speed = -speed;
	}

	rotate += speed;
}
