#include "HelloBasic3D.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>

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
	delete groundTexture;
	delete groundModel;
	delete ground;
	for (int i = 0; i < SCENE_OBJECT_CHILD_COUNT; i++)
		if(stickMan->children[i] != nullptr)
			delete stickMan->children[i];
	delete stickMan;
	delete cam;
}

void HelloBasic3D::LoadContent()
{
	blueTexture = new Texture2D();
	blueTexture->HasMipMaps(true);
	blueTexture->Load("Textures/blue.png");

	redTexture = new Texture2D();
	redTexture->HasMipMaps(true);
	redTexture->Load("Textures/red.png");

	skinTexture = new Texture2D();
	skinTexture->HasMipMaps(true);
	skinTexture->Load("Textures/skin.png");

	groundTexture = new Texture2D();
	groundTexture->IsRepeated(true);
	groundTexture->Load("Textures/ground.png");

	cubeMeshID = MeshLoader::Load("Meshes/Cube.obj");
	planeMeshID = MeshLoader::Load("Meshes/Plane.obj");
	plane15x15MeshID = MeshLoader::Load("Meshes/Plane15x15.obj");

	material.Alpha = 1.0f;
	material.Ambient = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	material.Diffuse = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	material.Specular = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
	material.Shininess = 10;

	Model* Jeans = new Model(cubeMeshID, blueTexture, material);
	Model* Shirt = new Model(cubeMeshID, redTexture, material);
	Model* Skin = new Model(cubeMeshID, skinTexture, material);
	groundModel = new Model(plane15x15MeshID, groundTexture, material);
	Model* billboard = new Model(planeMeshID, redTexture, material);

	Transform* groundTransform = new Transform();
	groundTransform->position = Vector3(0.0f, -1.0f, -10.0f);

	Billboard* billboardTransform = new Billboard();
	billboardTransform->position = Vector3(0.0f, 0.0f, -20.0f);
	billboardTransform->scale = Vector3(1.0f, 1.0f, 1.0f);

	origin = new CharacterTransform();
	origin->position = Vector3(0.0f, 0.0f, -15.0f);
	origin->walk = 0.1f;
	origin->run = 0.3f;

	rightLeg = new AnimateTransform(2.0f);
	rightLeg->position = Vector3(0.5f, 0.0f, 0.0f);
	rightLeg->scale = Vector3(0.4f, 1.0f, 0.5f);
	rightLeg->joint = Vector3(0.0f, 2.0f, 0.0f);

	leftLeg = new AnimateTransform(-2.0f);
	leftLeg->position = Vector3(-0.5f, 0.0f, 0.0f);
	leftLeg->scale = Vector3(0.4f, 1.0f, 0.5f);
	leftLeg->joint = Vector3(0.0f, 2.0f, 0.0f);

	Transform* body = new Transform();
	body->position = Vector3(0.0f, 2.0f, 0.0f);

	rightArm = new AnimateTransform(1.5f);
	rightArm->position = Vector3(1.2f, 2.0f, 0.0f);
	rightArm->scale = Vector3(0.2f, 0.75f, 0.4f);
	rightArm->joint = Vector3(0.0f, 0.75f, 0.0f);

	Transform* rightHand = new Transform();
	rightHand->position = Vector3(0.0f, -1.3f, 0.0f);
	rightHand->scale = Vector3(0.6f, 0.3f, 1.0f);

	leftArm = new AnimateTransform(-1.5f);
	leftArm->position = Vector3(-1.2f, 2.0f, 0.0f);
	leftArm->scale = Vector3(0.2f, 0.75f, 0.4f);
	leftArm->joint = Vector3(0.0f, 0.75f, 0.0f);

	Transform* leftHand = new Transform();
	leftHand->position = Vector3(0.0f, -1.3f, 0.0f);
	leftHand->scale = Vector3(0.6f, 0.3f, 1.0f);

	Transform* Head = new Transform();
	Head->position = Vector3(0.0f, 3.5f, 0.0f);
	Head->scale = Vector3(0.5f, 0.5f, 0.5f);

	Lighting light01;
	light01.Ambient = Vector4(0.7f, 0.5f, 0.5f, 1.0f);;
	light01.Diffuse = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	light01.Specular = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
	light01.Position = Vector4(0.2f, 10.0f, -8.0f, 1.0f);
	light01.lightNumber = GL_LIGHT0;

	Perspective* p = new Perspective(45, 1, 0.1, 250);

	cam = new ThirdPersonCamera(new Vector3(0.0f, 6.0f, -5.0f), new Vector3(origin->position + body->position), new Vector3(0.0f, 1.0f, 0.0f), p, "TPC", 10.0f, 4.0f);

	CameraManager::AddCamera(cam);
	CameraManager::AddCamera(new Camera(new Vector3(0.0f, 20.0f, -7.0f), new Vector3(0.0f, 0.0f, -8.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "TopView"));
	CameraManager::AddCamera(new Camera(new Vector3(9.0f, 0.0f, -15.0f), new Vector3(0.0f, 0.0f, -15.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "RightView"));
	CameraManager::AddCamera(new Camera(new Vector3(-9.0f, 0.0f, -15.0f), new Vector3(0.0f, 0.0f, -15.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "LeftView"));
	CameraManager::SetActiveCamera("TPC");

	ground = new SceneObject(groundModel, groundTransform);
	SceneObject* bill = new SceneObject(billboard, billboardTransform);
	stickMan = new SceneObject(nullptr, origin);
	stickMan->children[0] = new SceneObject(Jeans, rightLeg);
	stickMan->children[1] = new SceneObject(Jeans, leftLeg);
	stickMan->children[2] = new SceneObject(Shirt, body);
	stickMan->children[3] = new SceneObject(Shirt, rightArm);
	stickMan->children[4] = new SceneObject(Shirt, leftArm);
	stickMan->children[5] = new SceneObject(Skin, Head);
	stickMan->children[3]->children[0] = new SceneObject(Skin, rightHand);
	stickMan->children[4]->children[0] = new SceneObject(Skin, leftHand);

	for (int i = 0; i < SCENE_OBJECT_CHILD_COUNT; i++)
	{
		if(stickMan->children[i] != nullptr)
			stickMan->children[i]->parent = stickMan;
		if (stickMan->children[i] == nullptr)
			break;
	}
	stickMan->children[3]->children[0]->parent = stickMan->children[3];
	stickMan->children[4]->children[0]->parent = stickMan->children[4];

	CameraManager::Initialise();
	Input::Initialise();

	Director::AddLight(light01);
	Director::AddChild(ground);
	Director::AddChild(stickMan);
	Director::AddChild(bill);
}

void HelloBasic3D::Draw()
{
	Draw::DrawString("This is some text", Colour(1.0f, 0.0f, 0.0f, 1.0f), Vector3(0.0f, 2.0f, -17.0f), Vector2(10.0f, 10.0f));
}

void HelloBasic3D::Update(int timeStep)
{
	Keyboard(Input::Keyboard::GetState());
	Mouse(Input::Mouse::GetState());

	cam->heading = stickMan->transform->heading;
	cam->center = new Vector3(stickMan->transform->position + stickMan->children[2]->transform->position);

	CameraManager::UpdateActiveCamera();

	//crates[0]->box->position = crates[0]->position;
	//crates[1]->box->position = crates[1]->position;

	//crates[0]->box->Intersects(crates[1]->box);
	//crates[1]->box->Intersects(crates[0]->box);
}


void HelloBasic3D::Keyboard(Input::KeyboardState * state)
{
	if (state->IsKeyDown(Input::Keys::NUMPAD1))
	{
		CameraManager::SetActiveCamera("TPC");
	}

	if (state->IsKeyDown(Input::Keys::NUMPAD2))
	{
		CameraManager::SetActiveCamera("TopView");
	}

	if (state->IsKeyDown(Input::Keys::NUMPAD3))
	{
		CameraManager::SetActiveCamera("RightView");
	}

	if (state->IsKeyDown(Input::Keys::NUMPAD4))
	{
		CameraManager::SetActiveCamera("LeftView");
	}

	if (state->IsKeyDown(Input::Keys::W))
	{
		if(state->IsKeyUp(Input::Keys::LEFT_SHIFT))
			origin->Foreward();
		rightLeg->startStop = true;
		leftLeg->startStop = true;
		rightArm->startStop = true;
		leftArm->startStop = true;
	}

	if (state->IsKeyUp(Input::Keys::W))
	{
		rightLeg->startStop = false;
		leftLeg->startStop = false;
		rightArm->startStop = false;
		leftArm->startStop = false;
	}

	if (state->IsKeyDown(Input::Keys::W) && state->IsKeyDown(Input::Keys::LEFT_SHIFT))
	{
		origin->Run();
	}

	if (state->IsKeyDown(Input::Keys::S))
	{
		origin->Backward();
	}

	if (state->IsKeyDown(Input::Keys::A))
	{
		origin->Left();
	}

	if (state->IsKeyDown(Input::Keys::D))
	{
		origin->Right();
	}

	if (state->IsKeyDown(Input::Keys::SPACE))
	{
		// TO DO: Jump code.
	}

	if (state->IsKeyDown(Input::Keys::LEFT))
	{
		stickMan->transform->heading += 1.0f;
	}

	if (state->IsKeyDown(Input::Keys::RIGHT))
	{
		stickMan->transform->heading -= 1.0f;
	}
}

void HelloBasic3D::Mouse(Input::MouseState * state)
{
	if(state->scrollWheelValue < -10)
		cam->distance = -(float)state->scrollWheelValue;
}