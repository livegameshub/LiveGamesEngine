#include "TestScene.h"
#include "ShaderResource.h"
#include "Engine.h"
#include "Window.h"
#include "ResourceManager.h"
#include "Time.h"

namespace ai
{
	TestScene::TestScene()
	{
	}

	TestScene::~TestScene()
	{
	}

	void TestScene::init()
	{
		/* call the basic init function */
		BasicScene::init();

		mVertexShader = ResourceManager::getInstance().createShader(1, ShaderResource::VERTEX_SHADER, "DiffuseShader.vs");
		mFragmentShader = ResourceManager::getInstance().createShader(2, ShaderResource::FRAGMENT_SHADER, "DiffuseShader.fs");

		mProgram = ResourceManager::getInstance().createProgram(3, mVertexShader, mFragmentShader, { "u_view", "u_model", "u_projection", "u_material.diffuse" });

		mMaterial = ResourceManager::getInstance().createMaterial(4, mProgram, glm::vec3(0.0f, 0.0f, 1.0f));
		mCubeMesh = ResourceManager::getInstance().createMesh(5, "Cube.mesh");

		mCamera = new CameraNode(1);
		mCamera->setViewSize(Engine::getInstance().GetWindowByIndex(0)->GetSize());
		mCamera->moveAt(glm::vec3(0.0f, 0.0f, 5.0f));

		mCubeNode = new ModelNode(2);
		mCubeNode->SetMesh(mCubeMesh);
		mCubeNode->SetMaterial(mMaterial);

		addNode(mCamera);
		addNode(mCubeNode);

		mRootNode.AddChild(mCamera);
		mRootNode.AddChild(mCubeNode);
	}

	void TestScene::update()
	{
		/* call the basic update function */

		BasicScene::update();

		mProgram->Use();

		/* camera */
		mProgram->SetUniform("u_projection", mCamera->getPerspecitiveMatrix());
		mProgram->SetUniform("u_view", mCamera->getViewMatrix());

		/* material */
		mProgram->SetUniform("u_material.diffuse", mMaterial->GetDiffuseColor());
		
		/* node */
		static glm::f32 angle = 0.0f;

		angle += Time::GetDeltaTime() * 20.0f;

		mCubeNode->GetTransform().RotateOnY(angle);

		if (angle > 360.0f)
		{
			angle -= 360.0f;
		}

		mProgram->SetUniform("u_model", mCubeNode->GetTransform().GetMatrix());
		
		/*mesh */
		mCubeMesh->BindVbo();
		mCubeMesh->UploadAttributes(mProgram->GetAttributes());
		mCubeMesh->BindIbo();
		mCubeMesh->Draw();
	}

	void TestScene::release()
	{
		/* class the basic release function */

		BasicScene::release();
	}
}
