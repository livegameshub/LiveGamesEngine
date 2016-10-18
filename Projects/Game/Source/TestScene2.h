#ifndef _TEST_SCENE2_H_
#define _TEST_SCENE2_H_

#include "BasicScene.h"
#include "CameraNode.h"
#include "ModelNode.h"

namespace ai
{
	class TestScene2 : public BasicScene
	{
	public:
		TestScene2();
		TestScene2(const glm::vec3& ambientLight);

		~TestScene2();

		void init() override;
		void update() override;
		void release() override;

	private:
		std::vector<ModelNode*> mSpheres;

		DirectionalLightNode* mDirectionalLight;
		CameraNode* mCamera;
	};
}

#endif //_TEST_SCENE_H_
