#include "stdafx.h"
#include "Texture2D.h"
#include <iostream>

namespace Basic3D
{
	Texture2D::Texture2D()
	{
		_ID = new GLuint();
	}
	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, _ID);
		delete _ID;
	}
	void Texture2D::Load(const char * path)
	{
		int channels;

		unsigned char* data = SOIL_load_image
			(
				path,
				&_width, &_height, &channels,
				SOIL_LOAD_AUTO
				);

		glGenTextures(1, _ID); //Get next Texture ID
		glBindTexture(GL_TEXTURE_2D, *_ID); //Bind the texture to the ID

			//Note that TGA files are stored as BGR(A) - So we need to specify the format as GL_BGR(A)_EXT
		if (channels == 4)
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, data);

#if _DEBUG
			std::cout << path << " Loaded" << std::endl;
#endif

		delete [] data;
	}
	int Texture2D::GetWidth() const
	{
		return _width;
	}
	int Texture2D::GetHeight() const
	{
		return _height;
	}
	GLuint * Texture2D::GetID() const
	{
		return _ID;
	}
}
