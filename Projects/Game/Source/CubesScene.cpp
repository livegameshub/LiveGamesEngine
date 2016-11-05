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
#include "Console.h"
#include "Program.h"
#include "Mesh.h"

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
	lg::Shader* vertexShader = lg::Resources::instance().create<lg::Shader>(lg::Resources::getNextId(), "BasicShader.vs");
	lg::Shader* fragmentShader = lg::Resources::instance().create<lg::Shader>(lg::Resources::getNextId(), "BasicShader.fs");

	lg::Shader* vertexShader2 = lg::Resources::instance().create<lg::Shader>(lg::Resources::getNextId(), "DiffuseShader.vs");
	lg::Shader* fragmentShader2 = lg::Resources::instance().create<lg::Shader>(lg::Resources::getNextId(), "DiffuseShader.fs");

	lg::Shader* vertexShader3 = lg::Resources::instance().create<lg::Shader>(lg::Resources::getNextId(), "DiffuseTextureShader.vs");
	lg::Shader* fragmentShader3 = lg::Resources::instance().create<lg::Shader>(lg::Resources::getNextId(), "DiffuseTextureShader.fs");

	// programs
	lg::Program* program = lg::Resources::instance().create<lg::Program>(lg::Resources::getNextId());
	lg::Program* program2 = lg::Resources::instance().create<lg::Program>(lg::Resources::getNextId());
	lg::Program* program3 = lg::Resources::instance().create<lg::Program>(lg::Resources::getNextId());

	program->addShader(vertexShader);
	program->addShader(fragmentShader);

	program2->addShader(vertexShader2);
	program2->addShader(fragmentShader2);

	program3->addShader(vertexShader3);
	program3->addShader(fragmentShader3);

	// textures
	lg::Texture* plane_texture = lg::Resources::instance().create<lg::Texture>(lg::Resources::getNextId(), "floor.texture");

	// meshes
	lg::Mesh* cube_mesh = lg::Resources::instance().create<lg::Mesh>(lg::Resources::getNextId(), "Cube.mesh");
	lg::Mesh* cube_mesh2 = lg::Resources::instance().create<lg::Mesh>(lg::Resources::getNextId(), "Cube2.mesh");
	lg::Mesh* plane_mesh = lg::Resources::instance().create<lg::Mesh>(lg::Resources::getNextId(), "Plane.mesh");

	// materials
	lg::Material* red_material = lg::Resources::instance().createMaterial<lg::Material>(lg::Resources::getNextId(), program, nullptr, vec3(1.0f, 0.0f, 0.0f));
	lg::DiffuseMaterial* yellow_material = lg::Resources::instance().createMaterial<lg::DiffuseMaterial>(lg::Resources::getNextId(), program2, nullptr, vec3(1.0f, 1.0f, 0.0f), lg::Material::IS_LIGHTED);
	lg::DiffuseMaterial* blue_material = lg::Resources::instance().createMaterial<lg::DiffuseMaterial>(lg::Resources::getNextId(), program2, nullptr, vec3(0.0f, 0.0f, 1.0f), lg::Material::IS_SHINY | lg::Material::IS_LIGHTED);
	lg::DiffuseMaterial* plane_material = lg::Resources::instance().createMaterial<lg::DiffuseMaterial>(lg::Resources::getNextId(), program3, plane_texture, vec3(1.0f), lg::Material::IS_SHINY | lg::Material::IS_TEXTURED | lg::Material::IS_LIGHTED);

	// camera 
	mCamera = create<lg::Camera>(1, lg::Node::CAMERA, &mRootNode);
	mCamera->setViewSize(lg::Engine::instance().getWindowByIndex(0)->getSize());
	mCamera->moveAt(vec3(0.0f, 0.0f, 7.0f));

	// models
	lg::Node* plane = create<lg::Node>(2, lg::Node::MODEL, &mRootNode, vec3(0.0f, -1.5f, 0.0f));
	plane->setRenderer(lg::MeshRenderer::create(plane_material, plane_mesh));
	plane->getTransform().setScale(vec3(8.0f));
	plane->getTransform().rotateOnX(270.0f);

	mCubes.push_back(create<lg::Node>(3, lg::Node::MODEL, &mRootNode, vec3(-3.5f, 0.0f, 0.0f)));
	mCubes.push_back(create<lg::Node>(4, lg::Node::MODEL, &mRootNode));
	mCubes.push_back(create<lg::Node>(5, lg::Node::MODEL, &mRootNode, vec3(3.5f, 0.0f, 0.0f)));
	
	mCubes[0]->setRenderer(lg::MeshRenderer::create(blue_material, cube_mesh2));
	mCubes[1]->setRenderer(lg::MeshRenderer::create(yellow_material, cube_mesh2));
	mCubes[2]->setRenderer(lg::MeshRenderer::create(red_material, cube_mesh));

	// light
	mDirectionalLight = create<lg::DirectionalLight>(6, lg::Node::DIRECTIONAL_LIGHT, &mRootNode);
	mDirectionalLight->setDirection(vec3(0.0f, 0.0f, -1.0f));

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
