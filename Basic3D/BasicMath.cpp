#include "stdafx.h"
#define _USE_MATH_DEFINES
#include "BasicMath.h"
#include <cmath>

namespace Basic3D
{
	namespace BasicMath
	{
		float DegreesToRadians(float degrees)
		{
			return ((float)M_PI * degrees) / 180;
		}

		float RadiansToDegrees(float radians)
		{
			return (radians * 180) / (float)M_PI;
		}
	}
}