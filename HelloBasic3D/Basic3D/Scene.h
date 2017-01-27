#pragma once
#include "Basic3D.h"

namespace Basic3D
{
	class BASIC3D_API Scene
	{
	public:
		Scene(int argc, char * argv[]);
		virtual ~Scene();
		virtual void LoadContent() = 0;
		virtual void Update(int elapsedTime) = 0;
		virtual void Keyboard(unsigned char key, int x, int y) {}
		virtual void Draw() {}
		virtual void MousePress(int button, int state, int x, int y) {}
		virtual void MouseMove(int x, int y) {}
	};
}