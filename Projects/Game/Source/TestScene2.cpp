#include "TestScene2.h"
#include "ShaderResource.h"
#include "Engine.h"
#include "Window.h"
#include "Resources.h"
#include "Time.h"
#include "Input.h"
#include "Scenes.h"
#include "DiffuseMaterial.h"
#include "DirectionalLightNode.h"

namespace ai
{
	TestScene2::TestScene2()
		: mDirectionalLight(nullptr)
		, mCamera(nullptr)
	{
	}

	TestScene2::TestScene2(const glm::vec3& ambientLight)
		: BasicScene(ambientLight)
		, mDirectionalLight(nullptr)
		, mCamera(nullptr)
	{
	}

	TestScene2::~TestScene2()
	{
	}

	void TestScene2::init()
	{
		/* call the basic init function */
		BasicScene::init();

		// meshes

		MeshResource* sphere_mesh = Resources::getInstance().createMesh(20, "Sphere.mesh");

		// materials

		BasicMaterial* red_material = static_cast<BasicMaterial*>(Resources::getInstance().getResource(5));
		DiffuseMaterial* yellow_material = static_cast<DiffuseMaterial*>(Resources::getInstance().getResource(7));
		DiffuseMaterial* blue_material = static_cast<DiffuseMaterial*>(Resources::getInstance().getResource(6));

		// camera 

		mCamera = createCamera(1, Engine::getInstance().getWindowByIndex(0)->getSize(), glm::vec3(0.0f, 0.0f, 7.0f));
		mRootNode.addChild(mCamera);

		// models

		mSpheres.push_back(createModel(20, sphere_mesh, blue_material));
		mSpheres.push_back(createModel(21, sphere_mesh, yellow_material));
		mSpheres.push_back(createModel(22, sphere_mesh, red_material));

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

	void TestScene2::update()
	{
		/* call the basic update function */

		BasicScene::update();

		static glm::f32 cameraAngle = 0.0f;
		static glm::f32 speed = 10.0f;

		if (Input::isKeyDown(GLFW_KEY_UP))
		{
			mCamera->moveForward(speed * Time::getDeltaTime());
		}
		else if (Input::isKeyDown(GLFW_KEY_DOWN))
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
	}

	void TestScene2::release()
	{
		/* class the basic release function */

		BasicScene::release();
	}
}
