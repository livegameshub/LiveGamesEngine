#include "TestScene.h"
#include "ShaderResource.h"
#include "Engine.h"
#include "Window.h"
#include "ResourceManager.h"
#include "Time.h"
#include "Input.h"
#include "SceneManager.h"
#include "DiffuseMaterialResource.h"
#include "DirectionalLightNode.h"

namespace ai
{
	TestScene::TestScene()
		: mDirectionalLight(nullptr)
		, mCamera(nullptr)
	{
	}

	TestScene::TestScene(const glm::vec3& ambientLight)
		: BasicScene(ambientLight)
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
		BasicScene::init();

		ShaderResource* vertexShader = ResourceManager::getInstance().createShader(1, ShaderResource::VERTEX_SHADER, "BasicShader.vs");
		ShaderResource* fragmentShader = ResourceManager::getInstance().createShader(2, ShaderResource::FRAGMENT_SHADER, "BasicShader.fs");

		ShaderResource* vertexShader2 = ResourceManager::getInstance().createShader(8, ShaderResource::VERTEX_SHADER, "DiffuseShader.vs");
		ShaderResource* fragmentShader2 = ResourceManager::getInstance().createShader(9, ShaderResource::FRAGMENT_SHADER, "DiffuseShader.fs");

		ProgramResource* program = ResourceManager::getInstance().createProgram(3, { vertexShader, fragmentShader });
		ProgramResource* program2 = ResourceManager::getInstance().createProgram(10, { vertexShader2, fragmentShader2 });

		MeshResource* cube_mesh = ResourceManager::getInstance().createMesh(4, "Cube.mesh");
		MeshResource* cube_mesh2 = ResourceManager::getInstance().createMesh(11, "Cube2.mesh");
		//MeshResource* sphere_mesh = ResourceManager::getInstance().createMesh(20, "Sphere.mesh");

		BasicMaterialResource* red_material = ResourceManager::getInstance().createMaterial(5, program, glm::vec3(1.0f, 0.0f, 0.0f));
		BasicMaterialResource* yellow_material = ResourceManager::getInstance().createMaterial(7, program, glm::vec3(1.0f, 1.0f, 0.0f));
		DiffuseMaterialResource* blue_material = ResourceManager::getInstance().createMaterial(6, program2, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.5f), 32.0f, BasicMaterialResource::IS_SHINY);

		mCamera = createCamera(1, Engine::getInstance().getWindowByIndex(0)->getSize(), glm::vec3(0.0f, 0.0f, 7.0f));
		mRootNode.addChild(mCamera);

		mCubes.push_back(createModel(2, cube_mesh2, blue_material));
		mCubes.push_back(createModel(3, cube_mesh, yellow_material));
		mCubes.push_back(createModel(4, cube_mesh, red_material));

		mCubes[0]->getTransform().setPosition(glm::vec3(-3.5f, 0.0f, 0.0f));
		mCubes[2]->getTransform().setPosition(glm::vec3(3.5f, 0.0f, 0.0f));

		mDirectionalLight = createDirectionalLight(5, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f), glm::vec3(0.5f));
		mRootNode.addChild(mDirectionalLight);

		for (auto cube : mCubes)
		{
			mRootNode.addChild(cube);
		}
	}

	void TestScene::update()
	{
		/* call the basic update function */

		BasicScene::update();

		static glm::f32 cameraAngle = 0.0f;
		static glm::f32 angle = 0.0f;
		static glm::f32 speed = 10.0f;

		angle += Time::getDeltaTime() * 20.0f;

		for (auto cube : mCubes)
		{
			cube->getTransform().rotateOnY(angle);
		}

		if (angle > 360.0f)
		{
			angle -= 360.0f;
		}

		if (Input::isKeyDown(GLFW_KEY_UP))
		{
			mCamera->moveForward(speed * Time::getDeltaTime());
		}
		else if(Input::isKeyDown(GLFW_KEY_DOWN))
		{
			mCamera->moveForward(-speed * Time::getDeltaTime());
		}

		if (Input::isKeyDown(GLFW_KEY_RIGHT))
		{
			cameraAngle -= Time::getDeltaTime() * 75.0f;

			mCamera->rotateOnY(cameraAngle);
		}
		else if (Input::isKeyDown(GLFW_KEY_LEFT))
		{
			cameraAngle += Time::getDeltaTime() * 75.0f;

			mCamera->rotateOnY(cameraAngle);
		}
			

		if (Input::isKeyDown(GLFW_KEY_SPACE))
		{
			SceneManager::getInstance().setMainScene(1);
		}
	}

	void TestScene::release()
	{
		/* class the basic release function */

		BasicScene::release();
	}
}
