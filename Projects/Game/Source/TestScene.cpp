#include "TestScene.h"
#include "ShaderResource.h"
#include "Engine.h"
#include "Window.h"
#include "ResourceManager.h"
#include "Time.h"

namespace ai
{
	TestScene::TestScene()
		: mCamera(nullptr)
		, mCubeNode(nullptr)
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

		ProgramResource* program = ResourceManager::getInstance().createProgram(3, { vertexShader, fragmentShader }, { "u_view", "u_model", "u_projection", "u_material.diffuse" });

		MaterialResource* material = ResourceManager::getInstance().createMaterial(4, program, glm::vec3(0.0f, 0.0f, 1.0f));
		MeshResource* cube_mesh = ResourceManager::getInstance().createMesh(5, "Cube.mesh");

		mCamera = createCamera(1, Engine::getInstance().getWindowByIndex(0)->GetSize(), glm::vec3(0.0f, 0.0f, 5.0f));
		mCubeNode = createModel(2, cube_mesh, material);

		mRootNode.addChild(mCamera);
		mRootNode.addChild(mCubeNode);
	}

	void TestScene::update()
	{
		/* call the basic update function */

		BasicScene::update();

		static glm::f32 angle = 0.0f;

		angle += Time::GetDeltaTime() * 20.0f;

		mCubeNode->getTransform().RotateOnY(angle);

		if (angle > 360.0f)
		{
			angle -= 360.0f;
		}
	}

	void TestScene::release()
	{
		/* class the basic release function */

		BasicScene::release();
	}
}
