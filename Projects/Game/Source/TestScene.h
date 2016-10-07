#ifndef _TEST_SCENE_H_
#define _TEST_SCENE_H_

#include "BasicScene.h"
#include "ProgramResource.h"
#include "MeshResource.h"
#include "CameraNode.h"
#include "ModelNode.h"
#include "MaterialResource.h"

namespace ai
{
	class TestScene : public BasicScene
	{
	public:
		TestScene();
		~TestScene();

		void init() override;
		void update() override;
		void release() override;

	private:
		CameraNode* mCamera;
		ModelNode* mCubeNode;

		MaterialResource* mMaterial;
		ProgramResource* mProgram;
		ShaderResource* mVertexShader;
		ShaderResource* mFragmentShader;
		MeshResource* mCubeMesh;
	};
}

#endif
