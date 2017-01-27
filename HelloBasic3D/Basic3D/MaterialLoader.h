#pragma once

#include "Basic3D.h"

namespace Basic3D
{
	class Material;
	namespace MaterialLoader
	{
		BASIC3D_API Material Load(char* path);
	}
}
