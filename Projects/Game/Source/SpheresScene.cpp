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
#include "Console.h"
#include "Mesh.h"

SpheresScene::SpheresScene()
	: mDirectionalLight(nullptr)
	, mCamera(nullptr)
{
}

SpheresScene::SpheresScene(const vec3& ambientLight)
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
	// meshes
	lg::Mesh* sphere_mesh = lg::Resources::instance().create<lg::Mesh>(lg::Resources::getNextId(), "Sphere.mesh");
	lg::Mesh* sphere_mesh2 = lg::Resources::instance().create<lg::Mesh>(lg::Resources::getNextId(), "Sphere2.mesh");
	
	// materials
	lg::Material* red_material = lg::Resources::instance().getResource<lg::Material>(14);
	lg::DiffuseMaterial* yellow_material = lg::Resources::instance().getResource<lg::DiffuseMaterial>(15);
	lg::DiffuseMaterial* blue_material = lg::Resources::instance().getResource<lg::DiffuseMaterial>(16);
	
	// camera 
	mCamera = create<lg::Camera>(1, lg::Node::CAMERA, &mRootNode);
	mCamera->setViewSize(lg::Engine::instance().getWindowByIndex(0)->getSize());
	mCamera->moveAt(vec3(0.0f, 0.0f, 7.0f));
	
	// models
	mSpheres.push_back(create<lg::Node>(2, lg::Node::MODEL, &mRootNode, vec3(-3.5f, 0.0f, 0.0f)));
	mSpheres.push_back(create<lg::Node>(3, lg::Node::MODEL, &mRootNode));
	mSpheres.push_back(create<lg::Node>(4, lg::Node::MODEL, &mRootNode, vec3(3.5f, 0.0f, 0.0f)));
	
	mSpheres[0]->setRenderer(lg::MeshRenderer::create(blue_material, sphere_mesh));
	mSpheres[1]->setRenderer(lg::MeshRenderer::create(yellow_material, sphere_mesh));
	mSpheres[2]->setRenderer(lg::MeshRenderer::create(red_material, sphere_mesh2));
	
	// light
	mDirectionalLight = create<lg::DirectionalLight>(5, lg::Node::DIRECTIONAL_LIGHT, &mRootNode);
	mDirectionalLight->setDirection(vec3(0.0f, 0.0f, -1.0f));

	/* call the basic init function */
	//Scene::init();
}

void SpheresScene::update()
{
	static f32 cameraAngle = 0.0f;
	static f32 speed = 10.0f;
	
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
	
	/* call the basic update function */
	Scene::update();

	if (lg::Input::isKeyDown(GLFW_KEY_SPACE))
	{
		lg::Engine::loadScene(2);
	}
}
