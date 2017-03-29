#include "stdafx.h"
#include "Basic3D.h"

namespace Basic3D
{
	GLfloat Vector2::Angle(Vector2 camPos, Vector2 boardPos)
	{
		return atan2(camPos.x - boardPos.x, camPos.y - boardPos.y);
	}

	// "this->" used for clarity. 
	Vector3 & Vector3::operator-= (const Vector3 & rVec)
	{
		this->x -= rVec.x;
		this->y -= rVec.y;
		this->z -= rVec.z;
		return *this;
	}

	Vector3 & Vector3::operator+= (const Vector3 & rVec)
	{
		this->x += rVec.x;
		this->y += rVec.y;
		this->z += rVec.z;
		return *this;
	}

	Vector3 & Vector3::operator*= (const Vector3 & rVec)
	{
		this->x *= rVec.x;
		this->y *= rVec.y;
		this->z *= rVec.z;
		return *this;
	}

	Vector3 & Vector3::operator/= (const Vector3 & rVec)
	{
		this->x /= rVec.x;
		this->y /= rVec.y;
		this->z /= rVec.z;
		return *this;
	}

	Vector3 & Vector3::operator= (const Vector3 & rVec)
	{
		this->x = rVec.x;
		this->y = rVec.y;
		this->z = rVec.z;
		return *this;
	}

	Vector3 & Vector3::operator-= (const GLfloat & rVal)
	{
		this->x -= rVal;
		this->y -= rVal;
		this->z -= rVal;
		return *this;
	}

	Vector3 & Vector3::operator+= (const GLfloat & rVal)
	{
		this->x += rVal;
		this->y += rVal;
		this->z += rVal;
		return *this;
	}

	Vector3 & Vector3::operator*= (const GLfloat & rVal)
	{
		this->x *= rVal;
		this->y *= rVal;
		this->z *= rVal;
		return *this;
	}

	Vector3 & Vector3::operator/= (const GLfloat & rVal)
	{
		this->x /= rVal;
		this->y /= rVal;
		this->z /= rVal;
		return *this;
	}

	Vector3 & Vector3::operator=(const GLfloat & rVal)
	{
		this->x = rVal;
		this->y = rVal;
		this->z = rVal;
		return *this;
	}

	const Vector3 Vector3::operator- (const Vector3 &subtract) const
	{
		Vector3 result = *this;
		result -= subtract;
		return result;
	}

	const Vector3 Vector3::operator+ (const Vector3 &add) const
	{
		Vector3 result = *this;
		result += add;
		return result;
	}

	const Vector3 Vector3::operator* (const Vector3 &multiply) const
	{
		Vector3 result = *this;
		result *= multiply;
		return result;
	}

	const Vector3 Vector3::operator/ (const Vector3 & divide) const
	{
		Vector3 result = *this;
		result /= divide;
		return result;
	}

	const Vector3 Vector3::operator- (const GLfloat &subtract) const
	{
		Vector3 result = *this;
		result -= subtract;
		return result;
	}

	const Vector3 Vector3::operator+ (const GLfloat &add) const
	{
		Vector3 result = *this;
		result += add;
		return result;
	}

	const Vector3 Vector3::operator* (const GLfloat &multiply) const
	{
		Vector3 result = *this;
		result *= multiply;
		return result;
	}

	const Vector3 Vector3::operator/ (const GLfloat &divide) const
	{
		Vector3 result = *this;
		result /= divide;
		return result;
	}

	bool Vector3::operator==(const Vector3 & other) const
	{
		if (x == other.x && y == other.y && x == other.z)
			return true;
		return false;
	}

	bool Vector3::operator==(const GLfloat & value) const
	{
		if (x == value && y == value && x == value)
			return true;
		return false;
	}

	bool Vector3::operator!=(const Vector3 & other) const
	{
		return !(*this == other);
	}

	bool Vector3::operator!=(const GLfloat & value) const
	{
		return !(*this == value);;
	}

	GLfloat Vector3::DotProduct(const Vector3 &vector)
	{
		return x * vector.x + y * vector.y + z * vector.z;
	}

	GLfloat Vector3::Angle3D(const Vector3 &vector)
	{
		return acosf(DotProduct(vector));
	}

	GLfloat Vector3::Length()
	{
		GLfloat hyp = sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2));
		return hyp;
	}

	Vector3 Vector3::Normal()
	{
		return Vector3(x, y, z) / Length();
	}

	BoundingBox::BoundingBox(GLuint meshID)
	{
		Mesh * mesh = MeshLoader::GetMesh(meshID);
		minCoords.x = maxCoords.x = mesh->vertices[0].x;
		minCoords.y = maxCoords.y = mesh->vertices[0].y;
		minCoords.z = maxCoords.z = mesh->vertices[0].z;
		
		for (unsigned int i = 0; i < (mesh->vertices.size()); i++)
		{
			if (mesh->vertices[i].x < minCoords.x) minCoords.x = mesh->vertices[i].x;
			if (mesh->vertices[i].x > maxCoords.x) maxCoords.x = mesh->vertices[i].x;
			if (mesh->vertices[i].y < minCoords.y) minCoords.y = mesh->vertices[i].y;
			if (mesh->vertices[i].y > maxCoords.y) maxCoords.y = mesh->vertices[i].y;
			if (mesh->vertices[i].z < minCoords.z) minCoords.z = mesh->vertices[i].z;
			if (mesh->vertices[i].z > maxCoords.z) maxCoords.z = mesh->vertices[i].z;
		}
	}

	BoundingBox::BoundingBox(GLfloat size) : minCoords(-size), maxCoords(size)
	{
	}

	BoundingBox::BoundingBox(GLfloat width, GLfloat height, GLfloat depth) : minCoords(-width, -height, -depth), maxCoords(width, height, depth)
	{
	}

	Vector3 BoundingBox::Left()
	{
		return Vector3(position.x + minCoords.x, position.y, position.z);
	}

	Vector3 BoundingBox::Right()
	{
		return Vector3(position.x + maxCoords.x, position.y, position.z);
	}

	Vector3 BoundingBox::Bottom()
	{
		return Vector3(position.x, position.y + minCoords.y, position.z);
	}

	Vector3 BoundingBox::Top()
	{
		return Vector3(position.x, position.y + maxCoords.y, position.z);
	}

	Vector3 BoundingBox::Front()
	{
		return Vector3(position.x, position.y, position.z + maxCoords.z);
	}

	Vector3 BoundingBox::Back()
	{
		return Vector3(position.x, position.y, position.z + minCoords.z);
	}

	bool BoundingBox::Contains(Vector3 point)
	{
		if((Left().x > point.x) &&
		   (Right().x < point.x) &&
		   (Top().y > point.y) &&
		   (Bottom().y < point.y) &&
		   (Front().z > point.z) &&
		   (Back().z < point.z))
		{
			return true;
		}
		return false;
	}

	bool BoundingBox::Intersects(BoundingBox* box)
	{
		if ((Left().x < box->Right().x) && (Right().x > box->Left().x) &&
			(Bottom().y < box->Top().y) && (Top().y > box->Bottom().y) &&
			(Back().z < box->Front().z) && (Front().z > box->Back().z))
		{
			return true;
		}
		return false;
	}

	Model::Model(GLuint meshID, Texture2D * tex, Material material) : meshID(meshID), tex(tex), material(material)
	{
	}

	Model::~Model()
	{
		if (tex != nullptr)
			delete tex;
	}

	Transform::Transform() : position(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), pitch(0.0f), heading(0.0f), roll(0.0f)
	{
	}

	Transform::Transform(GLfloat x, GLfloat y, GLfloat z) : position(x, y, z), scale(1.0f, 1.0f, 1.0f), pitch(0.0f), heading(0.0f), roll(0.0f)
	{
	}

	Transform::Transform(Vector3 position) : position(position), scale(1.0f, 1.0f, 1.0f), pitch(0.0f), heading(0.0f), roll(0.0f)
	{
	}

	Transform::Transform(Vector3 position, Vector3 scale) : position(position), scale(scale), pitch(0.0f), heading(0.0f), roll(0.0f)
	{
	}

	Transform::Transform(Vector3 position, Vector3 scale, GLfloat heading, GLfloat pitch, GLfloat roll) : position(position), scale(scale), pitch(pitch), heading(heading), roll(roll)
	{
	}

	void Transform::Update()
	{
		glTranslatef(position.x, position.y, position.z);
		glScalef(scale.x, scale.y, scale.z);
		glRotatef(pitch, 1, 0, 0);
		glRotatef(heading, 0, 1, 0);
		glRotatef(roll, 0, 0, 1);
	}

	Billboard::Billboard() : Transform()
	{
	}

	Billboard::Billboard(GLfloat x, GLfloat y, GLfloat z) : Transform(x, y, z)
	{
	}

	Billboard::Billboard(Vector3 position) : Transform(position)
	{
	}

	Billboard::Billboard(Vector3 position, Vector3 scale) : Transform(position, scale)
	{
	}

	Billboard::Billboard(Vector3 position, Vector3 scale, GLfloat pitch, GLfloat heading, GLfloat roll) : Transform(position, scale, pitch, heading, roll)
	{
	}

	void Billboard::Update()
	{
		Camera* cam = CameraManager::GetActiveCamera();
		glTranslatef(position.x, position.y, position.z);
		glScalef(scale.x, scale.y, scale.z);
		glRotatef(90.0f, 1, 0, 0);
		glRotatef(180.0f, 0, 1, 0);
		GLfloat rotation = Vector2::Angle(Vector2(cam->eye->x, cam->eye->z), Vector2(position.x, position.z));
		rotation = BasicMath::RadiansToDegrees(rotation);
		glRotatef(rotation, 0, 0, 1);
	}

	SceneObject::SceneObject(Model * model, Transform * transform) : model(model), transform(transform), box(nullptr),
																	 parent(nullptr)
	{
		for (int i = 0; i < SCENE_OBJECT_CHILD_COUNT; i++)
		{
			children[i] = nullptr;
		}
	}

	SceneObject::SceneObject(Model * model, Transform * transform, BoundingBox * box) : model(model), transform(transform), box(box),
																						parent(nullptr)
	{
		for (int i = 0; i < SCENE_OBJECT_CHILD_COUNT; i++)
		{
			children[i] = nullptr;
		}
	}

	SceneObject::~SceneObject()
	{
		for (int i = 0; i < SCENE_OBJECT_CHILD_COUNT; i++)
			if (children[i] != nullptr)
				delete children[i];

		if (model != nullptr)
			delete model;

		if (transform != nullptr)
			delete transform;

		if (box != nullptr)
			delete box;
	}
}
