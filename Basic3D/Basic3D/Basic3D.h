#pragma once
#ifdef BASIC3D_EXPORTS
#define BASIC3D_API __declspec(dllexport) 
#else
#define BASIC3D_API __declspec(dllimport) 
#pragma comment(lib, "Basic3D.lib")
#endif

#include <Windows.h> //Required for OpenGL on Windows
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> //OpenGL Utilities
#include "GL/freeglut.h" //freeglut library

#include "Camera.h"
#include "CameraManager.h"
#include "Director.h"
#include "Draw.h"
#include "Input.h"
#include "MaterialLoader.h"
#include "MeshLoader.h"
#include "Scene.h"
#include "Texture2D.h"
#include <vector>

namespace Basic3D
{
#define SCENE_OBJECT_CHILD_COUNT 6

	class BASIC3D_API Vector2
	{
	public:
		GLfloat x;
		GLfloat y;

		Vector2() {}
		Vector2(GLfloat x, GLfloat y) : x(x), y(y) {}

		static GLfloat Angle(Vector2 camPos, Vector2 boardPos);
	};

	class BASIC3D_API Vector3
	{
	public:
		GLfloat x;
		GLfloat y;
		GLfloat z;

		Vector3() {}
		Vector3(GLfloat value) : x(value), y(value), z(value) {}
		Vector3(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}

		// Right hand opearators. 
		Vector3 & operator-=  (const Vector3 & rVec);
		Vector3 & operator+=  (const Vector3 & rVec);
		Vector3 & operator*=  (const Vector3 & rVec);
		Vector3 & operator/=  (const Vector3 & rVec);
		Vector3 & operator=   (const Vector3 & rVal);
		Vector3 & operator-=  (const GLfloat & rVal);
		Vector3 & operator+=  (const GLfloat & rVal);
		Vector3 & operator*=  (const GLfloat & rVal);
		Vector3 & operator/=  (const GLfloat & rVal);
		Vector3 & operator=   (const GLfloat & rVal);

		const Vector3 operator- (const Vector3 &subtract) const;
		const Vector3 operator+ (const Vector3 &add) const;
		const Vector3 operator* (const Vector3 &multiply) const;
		const Vector3 operator/ (const Vector3 &divide) const;
		const Vector3 operator- (const GLfloat &subtract) const;
		const Vector3 operator+ (const GLfloat &add) const;
		const Vector3 operator* (const GLfloat &multiply) const;
		const Vector3 operator/ (const GLfloat &divide) const;

		GLfloat Angle3D(const Vector3 &vector);
		Vector3 Normal();
		GLfloat Length();
		GLfloat DotProduct(const Vector3 &vector);
	};

	class BASIC3D_API Vector4
	{
	public:
		float x, y, z, w;
		Vector4() {}
		Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
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
		Vector3 position;
		Vector3 minCoords, maxCoords;
	
		BoundingBox(GLuint meshID);
		BoundingBox(GLfloat size);
		BoundingBox(GLfloat width, GLfloat height, GLfloat depth);

		Vector3 Left();
		Vector3 Right();
		Vector3 Bottom();
		Vector3 Top();
		Vector3 Front();
		Vector3 Back();

		bool Contains(Vector3 point); // AARB.
		bool Intersects(BoundingBox* box);
	};

	class BASIC3D_API Model
	{
	public:
		GLuint meshID;
		Texture2D * tex;
		Material material;

		Model(GLuint meshID, Texture2D * tex, Material material);
	};

	class BASIC3D_API Transform
	{
	public:
		Vector3 position;
		Vector3 scale;
		GLfloat heading;
		GLfloat pitch;
		GLfloat roll;

		Transform();
		Transform(Vector3 position, Vector3 scale, GLfloat heading, GLfloat pitch, GLfloat roll);

		virtual void Update(); // Perform transformations here.
	};

	class BASIC3D_API SceneObject
	{
	public:
		SceneObject* parent;
		SceneObject* children[SCENE_OBJECT_CHILD_COUNT]; // Statically allocated children for each child.

		Model* model;
		Transform* transform;
		BoundingBox* box;
		bool billboard;

		SceneObject(Model* model, Transform* transform);
		SceneObject(Model* model, Transform* transform, BoundingBox* box, bool billboard);
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