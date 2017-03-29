#include "SecondScene.h"
#include <stdlib.h>
#include <time.h>

SecondScene::SecondScene() : Scene()
{
}

SecondScene::~SecondScene()
{
}

void SecondScene::LoadContent()
{
	// Objects are loaded in a second time for clarity.
	// Currently lib doesn't have obvious asset control across scenes.
	GLuint planeMeshID = MeshLoader::Load("Meshes/Plane.obj");
	GLuint groundMeshID = MeshLoader::Load("Meshes/Plane15x15.obj");
	GLuint cubeMeshID = MeshLoader::Load("Meshes/Cube.obj");
	Material groundMaterial = MaterialLoader::Load("Meshes/Plane15x15.mtl");
	Material treeMaterial = MaterialLoader::Load("Meshes/Tree.mtl");

	Texture2D* groundTexture = new Texture2D();
	groundTexture->IsRepeated(true);
	groundTexture->Load("Textures/grass.png");

	Texture2D* billboardTexture = new Texture2D();
	billboardTexture->HasMipMaps(true);
	billboardTexture->Load("Textures/grass_billboard_small.png");

	Texture2D* barkTexture = new Texture2D();
	barkTexture->HasMipMaps(true);
	barkTexture->Load("Textures/bark_tileable1.png");

	Transform* groundTransform = new Transform();
	groundTransform->position = Vector3(0.0f, -1.0f, -15.0f);

	Transform* treeTransform = new Transform();
	treeTransform->position = Vector3(0.0f, 1.0f, -18.0f);
	treeTransform->scale = Vector3(1.0f, 2.0f, 1.0f);

	topLeftBranchTransform = new Joint();
	topLeftBranchTransform->position = Vector3(-1.0f, 1.8f, -1.0f);
	topLeftBranchTransform->scale = Vector3(0.5f, 0.9f, 0.5f);
	//topLeftBranchTransform->heading = 45.0f;
	//topLeftBranchTransform->pitch = 45.0f;

	Joint* topRightBranchTransform = new Joint();
	topRightBranchTransform->position = Vector3(1.0f, 1.8f, -1.0f);
	topRightBranchTransform->scale = Vector3(0.5f, 0.9f, 0.5f);
	topRightBranchTransform->heading = -45.0f;
	//topRightBranchTransform->pitch = 45.0f;

	Joint* bottomLeftBranchTransform = new Joint();
	bottomLeftBranchTransform->position = Vector3(-1.0f, 1.8f, 1.0f);
	bottomLeftBranchTransform->scale = Vector3(0.5f, 0.9f, 0.5f);
	bottomLeftBranchTransform->heading = -135.0f;
	//bottomLeftBranchTransform->pitch = 45.0f;

	Joint* bottomRightBranchTransform = new Joint();
	bottomRightBranchTransform->position = Vector3(1.0f, 1.8f, 1.0f);
	bottomRightBranchTransform->scale = Vector3(0.5f, 0.9f, 0.5f);
	bottomRightBranchTransform->heading = 135.0f;
	//bottomRightBranchTransform->pitch = 45.0f;

	Model* groundModel = new Model(groundMeshID, groundTexture, groundMaterial);
	Model* billboardModel = new Model(planeMeshID, billboardTexture, groundMaterial);
	Model* branchModel = new Model(cubeMeshID, barkTexture, treeMaterial);

	ground = new SceneObject(groundModel, groundTransform);
	tree = new SceneObject(branchModel, treeTransform);
	tree->children[0] = new SceneObject(branchModel, topLeftBranchTransform);
	tree->children[1] = new SceneObject(branchModel, topRightBranchTransform);
	tree->children[2] = new SceneObject(branchModel, bottomLeftBranchTransform);
	tree->children[3] = new SceneObject(branchModel, bottomRightBranchTransform);

	for (int i = 0; i < 4; i++)
		tree->children[i]->parent = tree;

	SceneObject* billboardOrigin = new SceneObject(nullptr, new Transform(0.0f, 0.0f, -15.0f));

	srand((unsigned int)time(NULL));
	int count = -25;
	for (int i = 0; i < SCENE_OBJECT_CHILD_COUNT; i++)
	{ 
		int x = rand() % 10 + 1;
		if (x < 5)
			x = -x;

		billboardOrigin->children[i] = new SceneObject(billboardModel, new Billboard(Vector3((float)x, 0.0f, (float)count)));
		billboardOrigin->children[i]->parent = billboardOrigin;
		count++;
	}

	Perspective* p = new Perspective(45, 1, 0.1, 250);
	CameraManager::ClearAllCameras();
	cam = new ThirdPersonCamera(new Vector3(0.0f, 6.0f, -8.5f), new Vector3(tree->transform->position), new Vector3(0.0f, 1.0f, 0.0f), p, "TPC", 10.0f, 4.0f);
	CameraManager::AddCamera(cam);
	CameraManager::AddCamera(new Camera(new Vector3(13.0f, 6.0f, -18.0f), new Vector3(0.0f, 3.0f, -18.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "RightView"));
	CameraManager::AddCamera(new Camera(new Vector3(0.0f, 20.0f, -17.0f), new Vector3(0.0f, 0.0f, -18.0f), new Vector3(0.0f, 1.0f, 0.0f), p, "TopView"));
	CameraManager::SetActiveCamera("TPC");

	Lighting light01;
	light01.ambient = Vector4(0.8f, 0.8f, 0.8f, 1.0f);;
	light01.diffuse = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	light01.specular = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
	light01.position = Vector4(0.2f, 8.0f, -15.0f, 1.0f);
	light01.lightNumber = GL_LIGHT0;

	CameraManager::Initialise();
	Input::Initialise();

	Director::AddChild(ground);
	Director::AddChild(tree);
	Director::AddChild(billboardOrigin);
	Director::AddLight(light01);
}

void SecondScene::Draw()
{
}

void SecondScene::Update(int timeStep)
{
	Keyboard(Input::Keyboard::GetState());
	Mouse(Input::Mouse::GetState());

	cam->heading = tree->transform->heading;
	cam->center = new Vector3(tree->transform->position);

	CameraManager::UpdateActiveCamera();
}

void SecondScene::Keyboard(Input::KeyboardState * state)
{
	if (state->IsKeyDown(Input::Keys::NUMPAD1))
	{
		CameraManager::SetActiveCamera("TPC");
	}

	if (state->IsKeyDown(Input::Keys::NUMPAD2))
	{
		CameraManager::SetActiveCamera("RightView");
	}

	if (state->IsKeyDown(Input::Keys::NUMPAD3))
	{
		CameraManager::SetActiveCamera("TopView");
	}

	if (state->IsKeyDown(Input::Keys::LEFT))
	{
		tree->transform->heading += 1.0f;
	}

	if (state->IsKeyDown(Input::Keys::RIGHT))
	{
		tree->transform->heading -= 1.0f;
	}

	if (state->IsKeyDown(Input::Keys::P))
	{
		topLeftBranchTransform->jointPitch -= 0.5f;
	}
}

void SecondScene::Mouse(Input::MouseState * state)
{
	if (state->scrollWheelValue < -10)
		cam->distance = -(float)state->scrollWheelValue;
}


