#pragma once

#pragma comment(lib, "SOIL.lib")

#include "Basic3D.h"
#include "SOIL\SOIL.h"

namespace Basic3D
{
	struct Colour;
	class BASIC3D_API Texture2D
	{
	private:
		int _width, _height;
		GLuint *_ID;
	public:
		Texture2D();
		~Texture2D();
		void Load(const char* path);
		int GetWidth() const;
		int GetHeight() const;
		GLuint * GetID() const;
	};
}

