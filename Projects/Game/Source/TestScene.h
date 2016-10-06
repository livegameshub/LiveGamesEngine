#ifndef _TEST_SCENE_H_
#define _TEST_SCENE_H_

#include "BasicScene.h"
#include "Program.h"
#include "MeshResource.h"
#include "CameraNode.h"
#include "ModelNode.h"

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

		Program* mProgram;
		Shader* mVertexShader;
		Shader* mFragmentShader;
		MeshResource* mCubeMesh;
	};
}

#endif
