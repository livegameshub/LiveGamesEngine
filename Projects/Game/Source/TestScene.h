#ifndef _TEST_SCENE_H_
#define _TEST_SCENE_H_

#include "BasicScene.h"
#include "Program.h"
#include "Mesh.h"
#include "Camera.h"

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
		Camera* mCamera;

		Program* mProgram;
		Shader* mVertexShader;
		Shader* mFragmentShader;
		Mesh* mCubeMesh;
	};
}

#endif
