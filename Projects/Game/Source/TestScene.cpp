#include "TestScene.h"
#include "Shader.h"
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

		mVertexShader = new Shader(1, Shader::VERTEX_SHADER, "DiffuseShader.vs");
		mFragmentShader = new Shader(2, Shader::FRAGMENT_SHADER, "DiffuseShader.fs");

		mProgram = new Program(3);
		mProgram->AddShader(mVertexShader);
		mProgram->AddShader(mFragmentShader);;
		
		mProgram->AddUniforms({ "u_view", "u_model", "u_projection" });
	
		mCubeMesh = new MeshResource(4, "Cube.mesh");
		
		ResourceManager::getInstance().AddResource(mVertexShader);
		ResourceManager::getInstance().AddResource(mFragmentShader);
		ResourceManager::getInstance().AddResource(mProgram);
		ResourceManager::getInstance().AddResource(mCubeMesh);

		ResourceManager::addPendingItem(mProgram, true);

		mCamera = new CameraNode(1);
		mCamera->setViewSize(Engine::getInstance().GetWindowByIndex(0)->GetSize());
		mCamera->moveAt(glm::vec3(0.0f, 0.0f, 5.0f));

		mCubeNode = new ModelNode(2);
		mCubeNode->SetMesh(mCubeMesh);

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
