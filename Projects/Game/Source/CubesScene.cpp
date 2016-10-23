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
#include <Console.h>
#include <array>

CubesScene::CubesScene()
	: mDirectionalLight(nullptr)
	, mCamera(nullptr)
{
}

CubesScene::CubesScene(const glm::vec3& ambientLight)
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
	/* call the basic init function */
	Scene::init();

	// shaders 

	ai::Shader* vertexShader = ai::Resources::getInstance().createShader(ai::Resources::getNextAvailableId(), ai::Shader::VERTEX_SHADER, "BasicShader.vs");
	ai::Shader* fragmentShader = ai::Resources::getInstance().createShader(ai::Resources::getNextAvailableId(), ai::Shader::FRAGMENT_SHADER, "BasicShader.fs");

	ai::Shader* vertexShader2 = ai::Resources::getInstance().createShader(ai::Resources::getNextAvailableId(), ai::Shader::VERTEX_SHADER, "DiffuseShader.vs");
	ai::Shader* fragmentShader2 = ai::Resources::getInstance().createShader(ai::Resources::getNextAvailableId(), ai::Shader::FRAGMENT_SHADER, "DiffuseShader.fs");

	ai::Shader* vertexShader3 = ai::Resources::getInstance().createShader(ai::Resources::getNextAvailableId(), ai::Shader::VERTEX_SHADER, "DiffuseTextureShader.vs");
	ai::Shader* fragmentShader3 = ai::Resources::getInstance().createShader(ai::Resources::getNextAvailableId(), ai::Shader::FRAGMENT_SHADER, "DiffuseTextureShader.fs");

	// programs

	ai::Program* program = ai::Resources::getInstance().createProgram(ai::Resources::getNextAvailableId(), { vertexShader, fragmentShader });
	ai::Program* program2 = ai::Resources::getInstance().createProgram(ai::Resources::getNextAvailableId(), { vertexShader2, fragmentShader2 });
	ai::Program* program3 = ai::Resources::getInstance().createProgram(ai::Resources::getNextAvailableId(), { vertexShader3, fragmentShader3 });

	// meshes

	ai::Mesh* cube_mesh = ai::Resources::getInstance().createMesh(ai::Resources::getNextAvailableId(), "Cube.mesh");
	ai::Mesh* cube_mesh2 = ai::Resources::getInstance().createMesh(ai::Resources::getNextAvailableId(), "Cube2.mesh");
	ai::Mesh* plane_mesh = ai::Resources::getInstance().createMesh(ai::Resources::getNextAvailableId(), "Plane.mesh");

	// textures

	ai::Texture* plane_texture = ai::Resources::getInstance().createTexture(ai::Resources::getNextAvailableId(), "Texture.tga");

	// materials

	ai::Material* red_material = ai::Resources::getInstance().createMaterial(ai::Resources::getNextAvailableId(), program, glm::vec3(1.0f, 0.0f, 0.0f));
	ai::DiffuseMaterial* yellow_material = ai::Resources::getInstance().createMaterial(ai::Resources::getNextAvailableId(), program2, glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.5f), 32.0f);
	ai::DiffuseMaterial* blue_material = ai::Resources::getInstance().createMaterial(ai::Resources::getNextAvailableId(), program2, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.5f), 32.0f, ai::Material::IS_SHINY);

	ai::DiffuseMaterial* plane_material = ai::Resources::getInstance().createMaterial(ai::Resources::getNextAvailableId(), program3, glm::vec3(1.0f), glm::vec3(0.5f), 32.0f, ai::Material::IS_SHINY);
	plane_material->setDiffuseTexture(plane_texture);

	// camera 

	mCamera = createCamera(1, ai::Engine::getInstance().getWindowByIndex(0)->getSize(), glm::vec3(0.0f, 0.0f, 7.0f));
	mRootNode.addChild(mCamera);

	// models

	ai::Model* plane = createModel(2, plane_mesh, plane_material);
	mRootNode.addChild(plane);

	mCubes.push_back(createModel(3, cube_mesh2, blue_material));
	mCubes.push_back(createModel(4, cube_mesh2, yellow_material));
	mCubes.push_back(createModel(5, cube_mesh, red_material));

	mCubes[0]->getTransform().setPosition(glm::vec3(-3.5f, 0.0f, 0.0f));
	mCubes[2]->getTransform().setPosition(glm::vec3(3.5f, 0.0f, 0.0f));

	for (auto cube : mCubes)
	{
		mRootNode.addChild(cube);
	}

	// light

	mDirectionalLight = createDirectionalLight(6, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f), glm::vec3(0.5f));
	mRootNode.addChild(mDirectionalLight);
}

void CubesScene::update()
{
	/* call the basic update function */

	Scene::update();

	static glm::f32 cameraAngle = 0.0f;
	static glm::f32 angle = 0.0f;
	static glm::f32 speed = 10.0f;

	angle += ai::Time::getDeltaTime() * 20.0f;

	for (auto cube : mCubes)
	{
		cube->getTransform().rotateOnY(angle);
	}

	if (angle > 360.0f)
	{
		angle -= 360.0f;
	}

	if (ai::Input::isKeyDown(GLFW_KEY_UP))
	{
		mCamera->moveForward(speed * ai::Time::getDeltaTime());
	}
	else if(ai::Input::isKeyDown(GLFW_KEY_DOWN))
	{
		mCamera->moveForward(-speed * ai::Time::getDeltaTime());
	}

	if (ai::Input::isKeyDown(GLFW_KEY_RIGHT))
	{
		cameraAngle -= ai::Time::getDeltaTime() * 75.0f;

		mCamera->rotateOnY(cameraAngle);
	}
	else if (ai::Input::isKeyDown(GLFW_KEY_LEFT))
	{
		cameraAngle += ai::Time::getDeltaTime() * 75.0f;

		mCamera->rotateOnY(cameraAngle);
	}
			

	if (ai::Input::isKeyDown(GLFW_KEY_SPACE))
	{
		ai::Engine::loadScene(1);
	}
}
