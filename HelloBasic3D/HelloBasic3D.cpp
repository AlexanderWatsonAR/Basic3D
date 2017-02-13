#include "HelloBasic3D.h"
#include <iostream>
#include <stdlib.h>
#include <iostream>

HelloBasic3D::HelloBasic3D(int argc, char* argv[]) : Scene(argc, argv)
{
	int viewportHeight = 768;
	int viewportWidth = 1024;
	GLdouble aspect = viewportWidth / viewportHeight;
	Colour* red = new Colour(1.0f, 0.0f, 0.0f, 1.0f);
	Director::Initialise(argc, argv, this, 300, 100, viewportWidth, viewportHeight, nullptr, "HelloBasic3D", 60);
}

HelloBasic3D::~HelloBasic3D()
{
	delete crateTexture;
	delete groundTexture;
	delete ground;
	delete crateModel;
	delete groundModel;
	delete grandParent;
	delete parent;
	delete child;
	delete cam;
}

void HelloBasic3D::LoadContent()
{
	crateTexture = new Texture2D();
	crateTexture->HasMipMaps(true);
	crateTexture->Load("Textures/crate.bmp");

	groundTexture = new Texture2D();
	groundTexture->IsRepeated(true);
	groundTexture->Load("Textures/ground.png");

	cubeMeshID = MeshLoader::Load("Meshes/Cube.obj");
	planeMeshID = MeshLoader::Load("Meshes/Plane15x15.obj");

	material.Alpha = 1.0;
	material.Ambient = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	material.Diffuse = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	material.Specular = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
	material.Shininess = 10;

	crateModel = new Model(cubeMeshID, crateTexture, material);
	groundModel = new Model(planeMeshID, groundTexture, material);

	Transform* groundTransform = new Transform();
	groundTransform->position = Vector3(0.0f, -1.0f, -10.0f);

	Transform* grandParentTransform = new Transform();
	grandParentTransform->position = Vector3(0.0f, 0.0f, -5.0f);

	Transform* parentTransform = new Transform();
	parentTransform->position = Vector3(0.0f, 0.0f, -6.0f);

	Transform* childTransform = new Transform();
	childTransform->position = Vector3(0.0f, 0.0f, -7.0f);

	Lighting light01;
	light01.Ambient = Vector4(0.7f, 0.5f, 0.5f, 1.0f);
	light01.Diffuse = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	light01.Specular = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
	light01.Position = Vector4(0.2f, 10.0f, -8.0f, 1.0f);
	light01.lightNumber = GL_LIGHT0;

	Perspective* p = new Perspective(45, 1, 0.1, 250);

	CameraManager::AddCamera(new Camera(new Vector3(0.0f, 3.0f, 0.0f), new Vector3(0.0f, 0.0f, -8.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "Main"));
	CameraManager::AddCamera(new Camera(new Vector3(0.0f, 20.0f, -9.0f), new Vector3(0.0f, 0.0f, -8.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "TopView"));
	CameraManager::AddCamera(new Camera(new Vector3(-8.0f, 0.0f, -10.0f), new Vector3(0.0f, 0.0f, -8.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "LeftView"));
	CameraManager::AddCamera(new Camera(new Vector3(0.0f, 3.0f, 10.0f), new Vector3(0.0f, 0.0f, -8.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "Back"));
	CameraManager::SetActiveCamera("Main");

	ground = new SceneObject(groundModel, groundTransform);
	grandParent = new SceneObject(crateModel, grandParentTransform);
	parent = new SceneObject(crateModel, parentTransform);
	child = new SceneObject(crateModel, childTransform);

	grandParent->children[0] = parent;
	parent->parent = grandParent;
	parent->children[0] = child;
	child->parent = parent;

	CameraManager::Initialise();
	Input::Initialise();

	Director::AddLight(light01);
	Director::AddChild(ground);
}

void HelloBasic3D::Draw()
{
	Draw::DrawModel(grandParent);
}

void HelloBasic3D::Keyboard(Input::KeyboardState * state)
{
	if (state->IsKeyDown(Input::Keys::NUMPAD1))
	{
		CameraManager::SetActiveCamera("Main");
	}

	if (state->IsKeyDown(Input::Keys::NUMPAD2))
	{
		CameraManager::SetActiveCamera("TopView");
	}

	if (state->IsKeyDown(Input::Keys::NUMPAD3))
	{
		CameraManager::SetActiveCamera("LeftView");
	}

	if (state->IsKeyDown(Input::Keys::NUMPAD4))
	{
		CameraManager::SetActiveCamera("Back");
	}

	if (state->IsKeyDown(Input::Keys::W))
	{
		grandParent->transform->position.z -= 0.1f;
	}

	if (state->IsKeyDown(Input::Keys::S))
	{
		grandParent->transform->position.z += 0.1f;
	}

	if (state->IsKeyDown(Input::Keys::A))
	{
		grandParent->transform->position.x -= 0.1f;
	}

	if (state->IsKeyDown(Input::Keys::D))
	{
		grandParent->transform->position.x += 0.1f;
	}

	if (state->IsKeyDown(Input::Keys::Z))
	{
		grandParent->transform->position.y -= 0.1f;
	}

	if (state->IsKeyDown(Input::Keys::X))
	{
		grandParent->transform->position.y += 0.1f;
	}

	if (state->IsKeyDown(Input::Keys::LEFT))
	{
		grandParent->transform->heading -= 0.5f;
	}

	if (state->IsKeyDown(Input::Keys::RIGHT))
	{
		grandParent->transform->heading += 0.5f;
	}
}

void HelloBasic3D::Update(int timeStep)
{
	Input::KeyboardState * keyboardState = Input::Keyboard::GetState();
	Keyboard(keyboardState);
	CameraManager::UpdateActiveCamera();

	//crates[0]->box->position = crates[0]->position;
	//crates[1]->box->position = crates[1]->position;

	//crates[0]->box->Intersects(crates[1]->box);
	//crates[1]->box->Intersects(crates[0]->box);
}