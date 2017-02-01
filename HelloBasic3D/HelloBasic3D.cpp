#include "HelloBasic3D.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

HelloBasic3D::HelloBasic3D(int argc, char* argv[]) : Scene(argc, argv)
{
	int viewportHeight = 768;
	int viewportWidth = 1024;
	GLdouble aspect = viewportWidth / viewportHeight;
	Perspective* p = new Perspective(45, aspect, 0.1, 250);
	Colour* red = new Colour(1.0f, 0.0f, 0.0f, 1.0f);
	Director::Initialise(argc, argv, this, 300, 100, viewportWidth, viewportHeight, nullptr, "HelloBasic3D", 60);
}

HelloBasic3D::~HelloBasic3D()
{
	delete crate;
	delete cam;
}

void HelloBasic3D::LoadContent()
{
	Texture2D* texture = new Texture2D();
	texture->Load("Textures/crate.bmp");
	meshID = MeshLoader::Load("Meshes/Cube.obj");
	material.Alpha = 1.0;
	material.Ambient = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	material.Diffuse = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	material.Specular = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
	material.Shininess = 10;

	Lighting light01;
	light01.Ambient = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	light01.Diffuse = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	light01.Specular = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
	light01.Position = Vector4(0.2f, 10.0f, -12.5f, 1.0f);
	light01.lightNumber = GL_LIGHT0;

	Vector3* eye = new Vector3(0.0f, 4.0f, 0.0f);
	Vector3* center = new Vector3(0.0f, 0.0f, -12.5f);
	Vector3* up = new Vector3(0.0f, 1.0f, 0.0f);
	Perspective* p = new Perspective(45, 1, 0.1, 250);
	CameraManager::AddCamera(new Camera(eye, center, up, p, "Main"));
	CameraManager::SetActiveCamera("Main");

	crate = new SceneObject(meshID, texture->GetID(), material);
	crate->scale = Vector3(1.0f, 1.0f, 1.0f);
	crate->position = Vector3(0.0f, 0.0f, -12.5f);
	crate->heading = 0;
	crate->roll = 0;
	crate->pitch = 0;

	CameraManager::Initialise();
	Input::Initialise();

	Director::AddLight(light01);
	Director::AddChild(crate);
}

void HelloBasic3D::Draw()
{
	Draw::DrawString("This is some text.", Vector3(0, 0, -10));
}

void HelloBasic3D::Keyboard(Input::KeyboardState * state)
{
	if (state->IsKeyDown(Input::Keys::P))
	{
		Camera * main = CameraManager::RetrieveCamera("Main");
		main->eye->x += 0.1f;
	}
}

void HelloBasic3D::Update(int timeStep)
{
	Input::KeyboardState * keyboardState = Input::Keyboard::GetState();
	Keyboard(keyboardState);
	Camera * main = CameraManager::RetrieveCamera("Main");
	main->LookAt();
}