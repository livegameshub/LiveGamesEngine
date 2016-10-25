#include "SpheresScene.h"
#include "Shader.h"
#include "Engine.h"
#include "Window.h"
#include "Resources.h"
#include "Time.h"
#include "Input.h"
#include "Scenes.h"
#include "DiffuseMaterial.h"
#include "DirectionalLight.h"

SpheresScene::SpheresScene()
	: mDirectionalLight(nullptr)
	, mCamera(nullptr)
{
}

SpheresScene::SpheresScene(const glm::vec3& ambientLight)
	: Scene(ambientLight)
	, mDirectionalLight(nullptr)
	, mCamera(nullptr)
{
}

SpheresScene::~SpheresScene()
{
}

void SpheresScene::init()
{
	/* call the basic init function */
	Scene::init();

	// meshes

	lg::Mesh* sphere_mesh = lg::Resources::getInstance().createMesh(lg::Resources::getNextAvailableId(), "Sphere.mesh");

	// materials

	lg::Material* red_material = static_cast<lg::Material*>(lg::Resources::getInstance().getResource(14));
	lg::DiffuseMaterial* yellow_material = static_cast<lg::DiffuseMaterial*>(lg::Resources::getInstance().getResource(15));
	lg::DiffuseMaterial* blue_material = static_cast<lg::DiffuseMaterial*>(lg::Resources::getInstance().getResource(16));

	// camera 

	mCamera = createCamera(1, lg::Engine::getInstance().getWindowByIndex(0)->getSize(), glm::vec3(0.0f, 0.0f, 7.0f));
	mRootNode.addChild(mCamera);

	// models

	mSpheres.push_back(createModel(2, sphere_mesh, blue_material));
	mSpheres.push_back(createModel(3, sphere_mesh, yellow_material));
	mSpheres.push_back(createModel(4, sphere_mesh, red_material));

	mSpheres[0]->getTransform().setPosition(glm::vec3(-3.5f, 0.0f, 0.0f));
	mSpheres[2]->getTransform().setPosition(glm::vec3(3.5f, 0.0f, 0.0f));

	for (auto sphere : mSpheres)
	{
		mRootNode.addChild(sphere);
	}

	// light

	mDirectionalLight = createDirectionalLight(5, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f), glm::vec3(0.5f));
	mRootNode.addChild(mDirectionalLight);
}

void SpheresScene::update()
{
	/* call the basic update function */

	Scene::update();

	static glm::f32 cameraAngle = 0.0f;
	static glm::f32 speed = 10.0f;

	if (lg::Input::isKeyDown(GLFW_KEY_UP))
	{
		mCamera->moveForward(speed * lg::Time::getDeltaTime());
	}
	else if (lg::Input::isKeyDown(GLFW_KEY_DOWN))
	{
		mCamera->moveForward(-speed * lg::Time::getDeltaTime());
	}

	if (lg::Input::isKeyDown(GLFW_KEY_RIGHT))
	{
		cameraAngle -= lg::Time::getDeltaTime() * 75.0f;

		mCamera->rotateOnY(cameraAngle);
	}
	else if (lg::Input::isKeyDown(GLFW_KEY_LEFT))
	{
		cameraAngle += lg::Time::getDeltaTime() * 75.0f;

		mCamera->rotateOnY(cameraAngle);
	}


	if (lg::Input::isKeyDown(GLFW_KEY_SPACE))
	{
		lg::Engine::loadScene(2);
	}
}
