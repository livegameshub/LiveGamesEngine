#include "TestScene.h"
#include "ShaderResource.h"
#include "Engine.h"
#include "Window.h"
#include "ResourceManager.h"

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

		mVertexShader = new ShaderResource(1, ShaderResource::VERTEX_SHADER, "DiffuseShader.vs");
		mFragmentShader = new ShaderResource(2, ShaderResource::FRAGMENT_SHADER, "DiffuseShader.fs");

		mProgram = new ProgramResource(3);
		mProgram->AddShader(mVertexShader);
		mProgram->AddShader(mFragmentShader);;
		mProgram->AddUniforms({ "u_view", "u_model", "u_projection" });

		mMaterial = new MaterialResource(4);
		mMaterial->SetProgram(mProgram);

		mCubeMesh = new MeshResource(5, "Cube.mesh");
		
		ResourceManager::getInstance().AddResource(mVertexShader);
		ResourceManager::getInstance().AddResource(mFragmentShader);
		ResourceManager::getInstance().AddResource(mProgram);
		ResourceManager::getInstance().AddResource(mCubeMesh);
		ResourceManager::getInstance().AddResource(mMaterial);

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

		mProgram->SetUniform("u_projection", mCamera->getPerspecitiveMatrix());
		mProgram->SetUniform("u_view", mCamera->getViewMatrix());
		mProgram->SetUniform("u_model", glm::mat4());
		
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
