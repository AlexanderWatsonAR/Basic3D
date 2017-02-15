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
	delete crateTexture[0];
	delete crateTexture[1];
	delete groundTexture;
	delete ground;
	delete crateModel;
	delete groundModel;
	for (int i = 0; i < SCENE_OBJECT_CHILD_COUNT; i++)
	{
		delete stickMan->children[i];
	}
	delete stickMan;
	delete cam;
}

void HelloBasic3D::LoadContent()
{
	crateTexture[0] = new Texture2D();
	crateTexture[0]->HasMipMaps(true);
	crateTexture[0]->Load("Textures/crate.bmp");

	crateTexture[1] = new Texture2D();
	crateTexture[1]->HasMipMaps(true);
	crateTexture[1]->Load("Textures/crate_1.jpg");

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

	crateModel = new Model(cubeMeshID, crateTexture[0], material);
	groundModel = new Model(planeMeshID, groundTexture, material);

	Transform* groundTransform = new Transform();
	groundTransform->position = Vector3(0.0f, -1.0f, -10.0f);

	Transform* origin = new Transform();
	origin->position = Vector3(0.0f, 0.0f, -15.0f);

	Transform* rightLeg = new Transform();
	rightLeg->position = Vector3(0.5f, 0.0f, 0.0f);
	rightLeg->scale = Vector3(0.4f, 1.0f, 0.5f);

	Transform* leftLeg = new Transform();
	leftLeg->position = Vector3(-0.5f, 0.0f, 0.0f);
	leftLeg->scale = Vector3(0.4f, 1.0f, 0.5f);

	Transform* body = new Transform();
	body->position = Vector3(0.0f, 2.0f, 0.0f);

	Transform* rightArm = new Transform();
	rightArm->position = Vector3(1.3f, 2.0f, 0.0f);
	rightArm->scale = Vector3(0.3f, 0.75f, 0.5f);

	Transform* leftArm = new Transform();
	leftArm->position = Vector3(-1.3f, 2.0f, 0.0f);
	leftArm->scale = Vector3(0.3f, 0.75f, 0.5f);

	Transform* Head = new Transform();
	Head->position = Vector3(0.0f, 3.5f, 0.0f);
	Head->scale = Vector3(0.5f, 0.5f, 0.5f);

	Lighting light01;
	light01.Ambient = Vector4(0.7f, 0.5f, 0.5f, 1.0f);
	light01.Diffuse = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	light01.Specular = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
	light01.Position = Vector4(0.2f, 10.0f, -8.0f, 1.0f);
	light01.lightNumber = GL_LIGHT0;

	Perspective* p = new Perspective(45, 1, 0.1, 250);

	CameraManager::AddCamera(new Camera(new Vector3(0.0f, 5.0f, 0.0f), new Vector3(0.0f, 4.0f, -10.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "Main"));
	CameraManager::AddCamera(new Camera(new Vector3(0.0f, 20.0f, -7.0f), new Vector3(0.0f, 0.0f, -8.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "TopView"));
	CameraManager::AddCamera(new Camera(new Vector3(-8.0f, 0.0f, -10.0f), new Vector3(0.0f, 0.0f, -8.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "LeftView"));
	CameraManager::AddCamera(new Camera(new Vector3(0.0f, 3.0f, -25.0f), new Vector3(0.0f, 0.0f, -8.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "Back"));
	CameraManager::SetActiveCamera("Main");

	ground = new SceneObject(groundModel, groundTransform);
	stickMan = new SceneObject(nullptr, origin);
	stickMan->children[0] = new SceneObject(crateModel, rightLeg);
	stickMan->children[1] = new SceneObject(crateModel, leftLeg);
	stickMan->children[2] = new SceneObject(crateModel, body);
	stickMan->children[3] = new SceneObject(crateModel, rightArm);
	stickMan->children[4] = new SceneObject(crateModel, leftArm);
	stickMan->children[5] = new SceneObject(crateModel, Head);

	for (int i = 0; i < SCENE_OBJECT_CHILD_COUNT; i++)
	{
		stickMan->children[i]->parent = stickMan;
	}

	CameraManager::Initialise();
	Input::Initialise();

	Director::AddLight(light01);
	Director::AddChild(ground);
	Director::AddChild(stickMan);
}

void HelloBasic3D::Draw()
{
	//Draw::DrawString("This is some text", Colour(1.0f, 0.0f, 0.0f, 0.0f), Vector2(20.0f, 20.0f));
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
		stickMan->transform->position.z -= 0.1f;
	}

	if (state->IsKeyDown(Input::Keys::S))
	{
		stickMan->transform->position.z += 0.1f;
	}

	if (state->IsKeyDown(Input::Keys::A))
	{
		stickMan->transform->position.x -= 0.1f;
	}

	if (state->IsKeyDown(Input::Keys::D))
	{
		stickMan->transform->position.x += 0.1f;
	}

	if (state->IsKeyDown(Input::Keys::Z))
	{
		stickMan->transform->position.y -= 0.1f;
	}

	if (state->IsKeyDown(Input::Keys::X))
	{
		stickMan->transform->position.y += 0.1f;
	}

	if (state->IsKeyDown(Input::Keys::LEFT))
	{
		stickMan->transform->heading -= 0.5f;
	}

	if (state->IsKeyDown(Input::Keys::RIGHT))
	{
		stickMan->transform->heading += 0.5f;
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