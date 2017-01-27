#include "stdafx.h"
#include "Basic3D.h"
#include <math.h>

namespace Basic3D
{
	GLfloat Vector3::DotProduct(const Vector3 &vector)
	{
		return x * vector.x + y * vector.y + z * vector.z;
	}

	GLfloat Vector3::Angle3D(const Vector3 &vector)
	{
		return acosf(DotProduct(vector));
	}

	GLfloat Vector3::Distance(const Vector3 &vector)
	{
		Vector3 dir;
		dir.x = vector.x - x;
		dir.y = vector.y - y;
		dir.z = vector.z - z;

		GLfloat hyp = sqrtf(pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2));

		return hyp;
	}

	Vector3 Vector3::Direction(const Vector3 &vector)
	{
		Vector3 dir;
		dir.x = vector.x - x;
		dir.y = vector.y - y;
		dir.z = vector.z - z;

		GLfloat hyp = sqrtf(pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2));

		dir.x /= hyp;
		dir.y /= hyp;
		dir.z /= hyp;

		return dir;
	}
}
