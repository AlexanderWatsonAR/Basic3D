#include "stdafx.h"
#include "Texture2D.h"
#include <iostream>

namespace Basic3D
{
	Texture2D::Texture2D() : _ID(new GLuint()), _repeat(false), _buildMipMaps(false)
	{
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

		if (_buildMipMaps)
		{
			// TGA files are stored as BGR(A) - Specify the format as GL_BGR(A)_EXT.
			if (channels == 4)
				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, data);
			else
				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			if (channels == 4)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			else
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		if (_repeat)
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}

#if _DEBUG
			std::cout << path << " Loaded" << std::endl;
#endif

		delete [] data;
	}

	void Texture2D::IsRepeated(bool isRepeated)
	{
		_repeat = isRepeated;
	}

	void Texture2D::HasMipMaps(bool hasMipMaps)
	{
		_buildMipMaps = hasMipMaps;
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

	bool Texture2D::IsRepeated() const
	{
		return _repeat;
	}

	bool Texture2D::HasMipMaps() const
	{
		return _buildMipMaps;
	}
}
