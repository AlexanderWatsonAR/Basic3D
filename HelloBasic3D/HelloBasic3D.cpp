#include "HelloBasic3D.h"
#include <stdlib.h>

HelloBasic3D::HelloBasic3D()
{
}

HelloBasic3D::~HelloBasic3D()
{
	delete leftArm;
	delete leftLeg;
	delete rightArm;
	delete rightLeg;
	delete ground;
	delete stickMan;
	delete cam;
}

void HelloBasic3D::LoadContent()
{
	Texture2D* blueTexture = new Texture2D();
	blueTexture->HasMipMaps(true);
	blueTexture->Load("Textures/blue.png");

	Texture2D* redTexture = new Texture2D();
	redTexture->HasMipMaps(true);
	redTexture->Load("Textures/red.png");

	Texture2D* skinTexture = new Texture2D();
	skinTexture->HasMipMaps(true);
	skinTexture->Load("Textures/skin.png");

	Texture2D* headTexture = new Texture2D();
	headTexture->Load("Textures/face_cube_map.bmp");

	Texture2D* groundTexture = new Texture2D();
	groundTexture->IsRepeated(true);
	groundTexture->Load("Textures/ground.png");

	GLuint cubeMapMeshID = MeshLoader::Load("Meshes/CubeMap.obj");
	GLuint planeMeshID = MeshLoader::Load("Meshes/Plane.obj");
	GLuint plane15x15MeshID = MeshLoader::Load("Meshes/Plane15x15.obj");

	Material material;
	material.alpha = 1.0f;
	material.ambient = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	material.diffuse = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	material.specular = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
	material.shininess = 10;

	Model* jeansModel = new Model(cubeMapMeshID, blueTexture, material);
	Model* shirtModel = new Model(cubeMapMeshID, redTexture, material);
	Model* skinModel = new Model(cubeMapMeshID, skinTexture, material);
	Model* HeadModel = new Model(cubeMapMeshID, headTexture, material);
	Model* groundModel = new Model(plane15x15MeshID, groundTexture, material);
	Model* billboardModel = new Model(planeMeshID, redTexture, material);

	Transform* groundTransform = new Transform();
	groundTransform->position = Vector3(0.0f, -1.0f, -10.0f);

	Billboard* billboardTransform = new Billboard();
	billboardTransform->position = Vector3(0.0f, 0.0f, -20.0f);
	billboardTransform->scale = Vector3(1.0f, 1.0f, 1.0f);

	origin = new CharacterMovement();
	origin->position = Vector3(0.0f, 0.0f, -15.0f);
	origin->walk = 0.1f;
	origin->run = 0.3f;

	rightLeg = new Animate(2.0f);
	rightLeg->position = Vector3(0.5f, 0.0f, 0.0f);
	rightLeg->scale = Vector3(0.4f, 1.0f, 0.5f);
	rightLeg->joint = Vector3(0.0f, 2.0f, 0.0f);

	leftLeg = new Animate(-2.0f);
	leftLeg->position = Vector3(-0.5f, 0.0f, 0.0f);
	leftLeg->scale = Vector3(0.4f, 1.0f, 0.5f);
	leftLeg->joint = Vector3(0.0f, 2.0f, 0.0f);

	Transform* body = new Transform();
	body->position = Vector3(0.0f, 2.0f, 0.0f);

	rightArm = new Animate(1.0f);
	rightArm->position = Vector3(1.2f, 2.0f, 0.0f);
	rightArm->scale = Vector3(0.2f, 0.75f, 0.3f);
	rightArm->joint = Vector3(0.0f, 0.75f, 0.0f);

	Transform* rightHand = new Transform();
	rightHand->position = Vector3(0.0f, -1.3f, 0.0f);
	rightHand->scale = Vector3(0.6f, 0.3f, 1.0f);

	leftArm = new Animate(-1.0f);
	leftArm->position = Vector3(-1.2f, 2.0f, 0.0f);
	leftArm->scale = Vector3(0.2f, 0.75f, 0.3f);
	leftArm->joint = Vector3(0.0f, 0.75f, 0.0f);

	Transform* leftHand = new Transform();
	leftHand->position = Vector3(0.0f, -1.3f, 0.0f);
	leftHand->scale = Vector3(0.6f, 0.3f, 1.0f);

	Transform* Head = new Transform();
	Head->position = Vector3(0.0f, 3.5f, 0.0f);
	Head->scale = Vector3(0.5f, 0.5f, 0.5f);
	Head->pitch = 90.0f;
	Head->roll = -90.0f;

	Lighting light01;
	light01.ambient = Vector4(0.7f, 0.5f, 0.5f, 1.0f);;
	light01.diffuse = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	light01.specular = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
	light01.position = Vector4(0.2f, 10.0f, -15.0f, 1.0f);
	light01.lightNumber = GL_LIGHT0;

	Perspective* p = new Perspective(45, 1, 0.1, 250);

	cam = new ThirdPersonCamera(new Vector3(0.0f, 6.0f, -5.0f), new Vector3(origin->position + body->position), new Vector3(0.0f, 1.0f, 0.0f), p, "TPC", 10.0f, 4.0f);

	CameraManager::AddCamera(cam);
	CameraManager::AddCamera(new Camera(new Vector3(0.0f, 20.0f, -7.0f), new Vector3(0.0f, 0.0f, -8.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "TopView"));
	CameraManager::AddCamera(new Camera(new Vector3(9.0f, 0.0f, -15.0f), new Vector3(0.0f, 0.0f, -15.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "RightView"));
	CameraManager::AddCamera(new Camera(new Vector3(-9.0f, 0.0f, -15.0f), new Vector3(0.0f, 0.0f, -15.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "LeftView"));
	CameraManager::SetActiveCamera("TPC");

	ground = new SceneObject(groundModel, groundTransform);
	SceneObject* bill = new SceneObject(billboardModel, billboardTransform);
	stickMan = new SceneObject(nullptr, origin);
	stickMan->children[0] = new SceneObject(jeansModel, rightLeg);
	stickMan->children[1] = new SceneObject(jeansModel, leftLeg);
	stickMan->children[2] = new SceneObject(shirtModel, body);
	stickMan->children[3] = new SceneObject(shirtModel, rightArm);
	stickMan->children[4] = new SceneObject(shirtModel, leftArm);
	stickMan->children[5] = new SceneObject(HeadModel, Head);
	stickMan->children[3]->children[0] = new SceneObject(skinModel, rightHand);
	stickMan->children[4]->children[0] = new SceneObject(skinModel, leftHand);

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
	//Draw::DrawString("This is some text", Colour(1.0f, 0.0f, 0.0f, 1.0f), Vector3(0.0f, 5.0f, -17.0f), Vector2(0.0f, 0.0f));
	//Draw::DrawString("This is some text", Colour(1.0f, 0.0f, 0.0f, 1.0f), Vector2(50.0f, 50.0f));
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

	if (state->IsKeyDown(Input::Keys::NUMPAD0))
	{
		Director::ReplaceScene(new SecondScene());
	}
}

void HelloBasic3D::Mouse(Input::MouseState * state)
{
	if(state->scrollWheelValue < -10)
		cam->distance = -(float)state->scrollWheelValue;
}