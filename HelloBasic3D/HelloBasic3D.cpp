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
	Director::Initialise(argc, argv, this, 300, 100, viewportWidth, viewportHeight, p, nullptr, "HelloBasic3D", 60);
}

HelloBasic3D::~HelloBasic3D()
{
	delete crate;
}

void HelloBasic3D::LoadContent()
{
	srand(time(NULL));

	Texture2D texture;
	texture.Load("Textures/crate.bmp");

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

	cam = new Camera();
	cam->eye = Vector3(0.0f, 2.0f, 0.0f);
	cam->center = Vector3(0.0f, 0.0f, -12.5f);
	cam->up = Vector3(0.0f, 1.0f, 0.0f);

	Director::SetActiveCamera(cam);

	crate = new SceneObject(meshID, texture.GetID(), material);
	crate->scale = Vector3(1.0f, 1.0f, 1.0f);
	crate->position = Vector3(0.0f, 0.0f, -12.5f);
	crate->heading = 0;
	crate->roll = 0;
	crate->pitch = 0;

	Director::AddLight(light01);
	Director::AddChild(crate);
}

void HelloBasic3D::Draw()
{
	//Draw::DrawModel(crate);
}

void HelloBasic3D::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'p')
	{
		cout << "key press" << endl;
	}

	if (key == 'r')
	{
		crate->pitch += 0.1f;
		crate->heading += 0.3f;
		crate->roll += 0.45f;
	}

	if (key == 'i')
	{
		crate->position = Vector3(rand() % 12 + 1, rand() % 12 + 1, rand() % 12 + 1);
	}
}

void HelloBasic3D::Update(int timeStep)
{
	//GLfloat distance = crate->position.Distance(cam.eye);
	//cout << distance << endl;
}