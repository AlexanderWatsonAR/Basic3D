#pragma once
#include "Basic3D.h"

namespace Basic3D
{
	class BASIC3D_API Scene
	{
	public:
		Scene();
		virtual ~Scene();
		virtual void LoadContent() = 0;
		virtual void Update(int elapsedTime) = 0;
		virtual void Draw() {}
	};
}