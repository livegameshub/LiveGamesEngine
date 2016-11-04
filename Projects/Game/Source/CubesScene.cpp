#include "CubesScene.h"
#include "Shader.h"
#include "Engine.h"
#include "Window.h"
#include "Resources.h"
#include "Time.h"
#include "Input.h"
#include "Scenes.h"
#include "DiffuseMaterial.h"
#include "DirectionalLight.h"
#include "Sprite.h"
#include "Texture.h"
#include <Console.h>

CubesScene::CubesScene()
	: mDirectionalLight(nullptr)
	, mCamera(nullptr)
{
}

CubesScene::CubesScene(const vec3& ambientLight)
	: Scene(ambientLight)
	, mDirectionalLight(nullptr)
	, mCamera(nullptr)
{
}

CubesScene::~CubesScene()
{
}

void CubesScene::init()
{
	// shaders 
	lg::Shader* vertexShader = lg::Resources::instance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::VERTEX, "BasicShader.vs");
	lg::Shader* fragmentShader = lg::Resources::instance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::FRAGMENT, "BasicShader.fs");

	lg::Shader* vertexShader2 = lg::Resources::instance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::VERTEX, "DiffuseShader.vs");
	lg::Shader* fragmentShader2 = lg::Resources::instance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::FRAGMENT, "DiffuseShader.fs");

	lg::Shader* vertexShader3 = lg::Resources::instance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::VERTEX, "DiffuseTextureShader.vs");
	lg::Shader* fragmentShader3 = lg::Resources::instance().createShader(lg::Resources::getNextAvailableId(), lg::Shader::FRAGMENT, "DiffuseTextureShader.fs");

	// programs
	lg::Program* program = lg::Resources::instance().createProgram(lg::Resources::getNextAvailableId(), { vertexShader, fragmentShader });
	lg::Program* program2 = lg::Resources::instance().createProgram(lg::Resources::getNextAvailableId(), { vertexShader2, fragmentShader2 });
	lg::Program* program3 = lg::Resources::instance().createProgram(lg::Resources::getNextAvailableId(), { vertexShader3, fragmentShader3 });

	// textures
	lg::Texture* plane_texture = lg::Resources::instance().createTexture(lg::Resources::getNextAvailableId(), "floor.texture", false);

	// meshes
	lg::Mesh* cube_mesh = lg::Resources::instance().createMesh(lg::Resources::getNextAvailableId(), "Cube.mesh");
	lg::Mesh* cube_mesh2 = lg::Resources::instance().createMesh(lg::Resources::getNextAvailableId(), "Cube2.mesh");
	lg::Mesh* plane_mesh = lg::Resources::instance().createMesh(lg::Resources::getNextAvailableId(), "Plane.mesh");

	// materials
	lg::Material* red_material = lg::Resources::instance().createMaterial<lg::Material>(lg::Resources::getNextAvailableId(), program, nullptr, vec3(1.0f, 0.0f, 0.0f));
	lg::DiffuseMaterial* yellow_material = lg::Resources::instance().createMaterial<lg::DiffuseMaterial>(lg::Resources::getNextAvailableId(), program2, nullptr, vec3(1.0f, 1.0f, 0.0f), lg::Material::IS_LIGHTED);
	lg::DiffuseMaterial* blue_material = lg::Resources::instance().createMaterial<lg::DiffuseMaterial>(lg::Resources::getNextAvailableId(), program2, nullptr, vec3(0.0f, 0.0f, 1.0f), lg::Material::IS_SHINY | lg::Material::IS_LIGHTED);
	lg::DiffuseMaterial* plane_material = lg::Resources::instance().createMaterial<lg::DiffuseMaterial>(lg::Resources::getNextAvailableId(), program3, plane_texture, vec3(1.0f), lg::Material::IS_SHINY | lg::Material::IS_TEXTURED | lg::Material::IS_LIGHTED);

	// camera 
	mCamera = createNode<lg::Camera>(1, lg::Node::CAMERA);
	mCamera->setViewSize(lg::Engine::instance().getWindowByIndex(0)->getSize());
	mCamera->moveAt(vec3(0.0f, 0.0f, 7.0f));
	mRootNode.addChild(mCamera);

	// models
	lg::Node* plane = createNode<lg::Node>(2, lg::Node::MODEL);
	plane->setRenderer(lg::MeshRenderer::create(plane_material, plane_mesh));
	plane->getTransform().setScale(vec3(8.0f));
	plane->getTransform().translate(vec3(0.0f, -1.5f, 0.0f));
	plane->getTransform().rotateOnX(270.0f);
	mRootNode.addChild(plane);

	mCubes.push_back(createNode<lg::Node>(3, lg::Node::MODEL));
	mCubes.push_back(createNode<lg::Node>(4, lg::Node::MODEL));
	mCubes.push_back(createNode<lg::Node>(5, lg::Node::MODEL));
	
	mCubes[0]->setRenderer(lg::MeshRenderer::create(blue_material, cube_mesh2));
	mCubes[1]->setRenderer(lg::MeshRenderer::create(yellow_material, cube_mesh2));
	mCubes[2]->setRenderer(lg::MeshRenderer::create(red_material, cube_mesh));

	mCubes[0]->getTransform().setPosition(vec3(-3.5f, 0.0f, 0.0f));
	mCubes[2]->getTransform().setPosition(vec3(3.5f, 0.0f, 0.0f));
	
	for (auto cube : mCubes)
	{
		mRootNode.addChild(cube);
	}

	// light
	mDirectionalLight = createNode<lg::DirectionalLight>(6, lg::Node::DIRECTIONAL_LIGHT);
	mDirectionalLight->setDirection(vec3(0.0f, 0.0f, -1.0f));
	mRootNode.addChild(mDirectionalLight);

	/* call the basic init function */
	//Scene::init();
}

void CubesScene::update()
{
	static f32 cameraAngle = 0.0f;
	static f32 angle = 0.0f;
	static f32 speed = 10.0f;

	angle += lg::Time::getDeltaTime() * 20.0f;

	for (auto cube : mCubes)
	{
		cube->getTransform().rotateOnY(angle);
	}

	if (angle > 360.0f)
	{
		angle -= 360.0f;
	}

	if (lg::Input::isKeyDown(GLFW_KEY_UP))
	{
		mCamera->moveForward(speed * lg::Time::getDeltaTime());
	}
	else if(lg::Input::isKeyDown(GLFW_KEY_DOWN))
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
		lg::Engine::loadScene(1);
	}
}
