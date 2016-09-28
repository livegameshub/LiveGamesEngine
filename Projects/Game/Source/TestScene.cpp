#include "TestScene.h"
#include <Shader.h>
#include <Engine.h>
#include <Window.h>

namespace ai
{
	TestScene::TestScene()
	{
	}

	TestScene::~TestScene()
	{
	}

	void TestScene::Init()
	{
		/* call the basic Init function */
		BasicScene::Init();

		mVertexShader = new Shader(1, Shader::VERTEX_SHADER, "DiffuseShader.vs");
		mFragmentShader = new Shader(2, Shader::FRAGMENT_SHADER, "DiffuseShader.fs");

		mProgram = new Program(3);
		mProgram->AddShader(mVertexShader);
		mProgram->AddShader(mFragmentShader);;
		
		mProgram->AddUniforms({ "u_view", "u_model", "u_projection" });
		mProgram->Load();

		mCubeMesh = new Mesh(4, "Cube.mesh");
		mCubeMesh->Load();

		mCamera = new Camera(1);
		mCamera->SetViewSize(Engine::GetInstance().GetWindowByIndex(0)->GetSize());
		mCamera->MoveAt(glm::vec3(0.0f, 0.0f, 5.0f));

		mRootNode.AddChild(mCamera);
	}

	void TestScene::Update()
	{
		/* call the basic Update function */

		BasicScene::Update();

		mProgram->Use();

		mProgram->SetUniform("u_projection", mCamera->GetPerspecitiveMatrix());
		mProgram->SetUniform("u_view", mCamera->GetViewMatrix());
		mProgram->SetUniform("u_model", glm::mat4());
		
		mCubeMesh->BindVbo();
		mCubeMesh->UploadAttributes(mProgram->GetAttributes());
		mCubeMesh->BindIbo();
		mCubeMesh->Draw();
	}

	void TestScene::Release()
	{
		/* class the basic Release function */

		BasicScene::Release();
	}
}
