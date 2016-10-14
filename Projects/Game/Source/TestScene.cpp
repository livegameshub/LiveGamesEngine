#include "TestScene.h"
#include "ShaderResource.h"
#include "Engine.h"
#include "Window.h"
#include "ResourceManager.h"
#include "Time.h"
#include "Input.h"
#include "SceneManager.h"

namespace ai
{
	TestScene::TestScene()
		: mCamera(nullptr)
	{
	}

	TestScene::~TestScene()
	{
	}

	void TestScene::init()
	{
		/* call the basic init function */
		BasicScene::init();

		ShaderResource* vertexShader = ResourceManager::getInstance().createShader(1, ShaderResource::VERTEX_SHADER, "DiffuseShader.vs");
		ShaderResource* fragmentShader = ResourceManager::getInstance().createShader(2, ShaderResource::FRAGMENT_SHADER, "DiffuseShader.fs");

		ProgramResource* program = ResourceManager::getInstance().createProgram(3, { vertexShader, fragmentShader });
		MeshResource* cube_mesh = ResourceManager::getInstance().createMesh(4, "Cube.mesh");

		BasicMaterialResource* red_material = ResourceManager::getInstance().createMaterial(5, program, glm::vec3(1.0f, 0.0f, 0.0f));
		BasicMaterialResource* blue_material = ResourceManager::getInstance().createMaterial(6, program, glm::vec3(0.0f, 0.0f, 1.0f));
		BasicMaterialResource* yellow_material = ResourceManager::getInstance().createMaterial(7, program, glm::vec3(1.0f, 1.0f, 0.0f));

		mCamera = createCamera(1, Engine::getInstance().getWindowByIndex(0)->getSize(), glm::vec3(0.0f, 0.0f, 7.0f));
		mRootNode.addChild(mCamera);

		mCubes.push_back(createModel(2, cube_mesh, blue_material));
		mCubes.push_back(createModel(3, cube_mesh, yellow_material));
		mCubes.push_back(createModel(4, cube_mesh, red_material));

		mCubes[0]->getTransform().setPosition(glm::vec3(-3.5f, 0.0f, 0.0f));
		mCubes[2]->getTransform().setPosition(glm::vec3(3.5f, 0.0f, 0.0f));

		for (auto cube : mCubes)
		{
			mRootNode.addChild(cube);
		}
	}

	void TestScene::update()
	{
		/* call the basic update function */

		BasicScene::update();

		static glm::f32 angle = 0.0f;
		static glm::f32 speed = 5.0f;

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
