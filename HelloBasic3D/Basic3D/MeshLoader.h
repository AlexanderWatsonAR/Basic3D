#pragma once
#include "Basic3D.h"

namespace Basic3D
{
	struct Mesh;
	struct ReturnableMesh;

	namespace MeshLoader
	{
		BASIC3D_API GLuint Load(const char* path);
		Mesh * GetMesh(GLuint meshID);
		BASIC3D_API ReturnableMesh GetReturnableMesh(GLuint meshID);
	}
}
