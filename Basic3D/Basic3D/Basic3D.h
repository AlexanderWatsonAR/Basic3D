#pragma once
#ifdef BASIC3D_EXPORTS
#define BASIC3D_API __declspec(dllexport) 
#else
#define BASIC3D_API __declspec(dllimport) 
#pragma comment(lib, "Basic3D.lib")
#endif

#include <Windows.h> //Required for OpenGL on Windows
#include <GL/GL.h> //OpenGL
#include <GL/GLU.h> //OpenGL Utilities
#include "GL/freeglut.h" //freeglut library

#include "Director.h"
#include "Draw.h"
#include "MaterialLoader.h"
#include "MeshLoader.h"
#include "Scene.h"
#include "Texture2D.h"
#include <vector>

namespace Basic3D
{
	class BASIC3D_API Vector2
	{
		GLfloat x;
		GLfloat y;

		Vector2() {}
		Vector2(GLfloat x, GLfloat y) : x(x), y(y) {}
	};

	class BASIC3D_API Vector3
	{
	public:
		GLfloat x;
		GLfloat y;
		GLfloat z;

		Vector3() {}
		Vector3(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}

		inline Vector3 operator- (const Vector3 &vector) const
		{
			return Vector3(vector.x - x, vector.y - y, vector.z - z);
		}

		inline Vector3 operator+ (const Vector3 &vector) const
		{
			return Vector3(vector.x + x, vector.y + y, vector.z + z);
		}

		inline Vector3 operator* (const Vector3 &vector) const
		{
			return Vector3(vector.x * x, vector.y * y, vector.z * z);
		}

		inline bool operator== (const Vector3 &vector) const
		{
			if (vector.x == x && vector.y == y && vector.z == z)
				return true;
			return false;
		}

		inline bool operator!= (const Vector3 &vector) const
		{
			if (vector.x != x && vector.y != y && vector.z != z)
				return true;
			return false;
		}

		GLfloat Angle3D(const Vector3 &vector);
		Vector3 Direction(const Vector3 &vector);
		GLfloat Distance(const Vector3 &vector);
		GLfloat DotProduct(const Vector3 &vector);
	};

	class BASIC3D_API Vector4
	{
	public:
		float x, y, z, w;
		Vector4() {}
		Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	};
	
	class BASIC3D_API Camera
	{
	public:
		Vector3 eye, center, up;
		Camera() : eye(0.0f, 0.0f, 0.0f), center(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f) {}
	};

	struct BASIC3D_API Colour
	{
		GLfloat r, g, b, a;
		Colour() {}
		Colour(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
	};

	class BASIC3D_API Perspective
	{
	public:
		double fieldOfView, aspect, nearPlane, farPlane;
		Perspective() {}
		Perspective(double fieldOfView, double aspect, double nearPlane, double farPlane) :
		fieldOfView(fieldOfView), aspect(aspect), nearPlane(nearPlane), farPlane(farPlane) {}
	};

	class BASIC3D_API Lighting
	{
	public:
		GLenum lightNumber;
		Vector4 Ambient, Diffuse, Specular, Position;
		Lighting() {}
		Lighting(GLenum lightNumber, Vector4 ambient, Vector4 diffuse, Vector4 specular, Vector4 position) :
			lightNumber(lightNumber), Ambient(ambient), Diffuse(diffuse), Specular(specular), Position(position) {}
	};

	class BASIC3D_API Material
	{
	public:
		Vector4 Ambient, Diffuse, Specular;
		GLfloat Shininess, Alpha;
		Material() {}
		Material(Vector4 ambient, Vector4 diffuse, Vector4 specular, GLfloat Shininess, GLfloat Alpha) :
			Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(Shininess), Alpha(Alpha) {}
	};

	class BASIC3D_API BoundingBox
	{
	public:
		Vector3 top, bottom, left, right, back, front;

		inline BoundingBox operator() (const Vector3 &position, const Vector3 &minCoords, const Vector3 &maxCoords)
		{
			left = Vector3(position.x + minCoords.x, position.y, position.z);
			right = Vector3(position.x + maxCoords.x, position.y, position.z);
			front = Vector3(position.x, position.y, position.z + maxCoords.z);
			back = Vector3(position.x, position.y, position.z + minCoords.z);
			bottom = Vector3(position.x, position.y + minCoords.y, position.z);
			top = Vector3(position.x, position.y + maxCoords.y, position.z);

			BoundingBox box;
			box.top = top;
			box.bottom = bottom;
			box.left = left;
			box.right = right;
			box.front = front;
			return box;
		}
	};

	class BASIC3D_API SceneObject
	{
	public:
		GLuint texID;
		GLuint meshID;
		Material material;
		Vector3 position;
		Vector3 scale;
		GLfloat heading;
		GLfloat pitch;
		GLfloat roll;

		SceneObject(GLuint meshID, GLuint texID, Material material) : meshID(meshID), texID(texID), material(material) {}
	};

	struct BASIC3D_API Vertex
	{
		GLfloat x, y, z;
	};

	struct BASIC3D_API TexCoord
	{
		GLfloat u, v;
	};

	struct Mesh
	{
		std::vector<std::string> meshNames;
		std::vector<std::vector<GLushort>> indices;
		std::vector<Vertex> vertices;
		std::vector<Vector3> normals;
		std::vector<TexCoord> texCoords;
	};

	struct BASIC3D_API ReturnableMesh
	{
		std::string* meshNames;
		GLushort* indices;
		Vertex* vertices;
		Vector3* normals;
		TexCoord* texCoords;
	};
}