#include "TestScene.h"
#include "Shader.h"
#include "Engine.h"
#include "Window.h"
#include "Resources.h"
#include "Time.h"
#include "Input.h"
#include "Scenes.h"
#include "DiffuseMaterial.h"
#include "DirectionalLight.h"

TestScene::TestScene()
	: mDirectionalLight(nullptr)
	, mCamera(nullptr)
{
}

TestScene::TestScene(const glm::vec3& ambientLight)
	: ai::Scene(ambientLight)
	, mDirectionalLight(nullptr)
	, mCamera(nullptr)
{
}

TestScene::~TestScene()
{
}

void TestScene::init()
{
	/* call the basic init function */
	ai::Scene::init();

	// shaders 

	ai::Shader* vertexShader = ai::Resources::getInstance().createShader(1, ai::Shader::VERTEX_SHADER, "BasicShader.vs");
	ai::Shader* fragmentShader = ai::Resources::getInstance().createShader(2, ai::Shader::FRAGMENT_SHADER, "BasicShader.fs");

	ai::Shader* vertexShader2 = ai::Resources::getInstance().createShader(8, ai::Shader::VERTEX_SHADER, "DiffuseShader.vs");
	ai::Shader* fragmentShader2 = ai::Resources::getInstance().createShader(9, ai::Shader::FRAGMENT_SHADER, "DiffuseShader.fs");

	// programs

	ai::Program* program = ai::Resources::getInstance().createProgram(3, { vertexShader, fragmentShader });
	ai::Program* program2 = ai::Resources::getInstance().createProgram(10, { vertexShader2, fragmentShader2 });

	// meshes

	ai::Mesh* cube_mesh = ai::Resources::getInstance().createMesh(4, "Cube.mesh");
	ai::Mesh* cube_mesh2 = ai::Resources::getInstance().createMesh(11, "Cube2.mesh");

	// materials

	ai::Material* red_material = ai::Resources::getInstance().createMaterial(5, program, glm::vec3(1.0f, 0.0f, 0.0f));
	ai::DiffuseMaterial* yellow_material = ai::Resources::getInstance().createMaterial(7, program2, glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.5f), 32.0f);
	ai::DiffuseMaterial* blue_material = ai::Resources::getInstance().createMaterial(6, program2, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.5f), 32.0f, ai::Material::IS_SHINY);

	// camera 

	mCamera = createCamera(1, ai::Engine::getInstance().getWindowByIndex(0)->getSize(), glm::vec3(0.0f, 0.0f, 7.0f));
	mRootNode.addChild(mCamera);

	// models

	mCubes.push_back(createModel(2, cube_mesh2, blue_material));
	mCubes.push_back(createModel(3, cube_mesh2, yellow_material));
	mCubes.push_back(createModel(4, cube_mesh, red_material));

	mCubes[0]->getTransform().setPosition(glm::vec3(-3.5f, 0.0f, 0.0f));
	mCubes[2]->getTransform().setPosition(glm::vec3(3.5f, 0.0f, 0.0f));

	for (auto cube : mCubes)
	{
		mRootNode.addChild(cube);
	}

	// light

	mDirectionalLight = createDirectionalLight(5, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f), glm::vec3(0.5f));
	mRootNode.addChild(mDirectionalLight);
}

void TestScene::update()
{
	/* call the basic update function */

	ai::Scene::update();

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
		ai::Scenes::getInstance().setMainScene(1);
	}
}

void TestScene::release()
{
	/* class the basic release function */

	ai::Scene::release();
}
