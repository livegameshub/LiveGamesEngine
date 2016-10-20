#ifndef _TEST_SCENE2_H_
#define _TEST_SCENE2_H_

#include "Scene.h"
#include "Camera.h"
#include "Model.h"

class TestScene2 : public ai::Scene
{
public:
	TestScene2();
	TestScene2(const glm::vec3& ambientLight);

	~TestScene2();

	void init() override;
	void update() override;
	void release() override;

private:
	std::vector<ai::Model*> mSpheres;

	ai::DirectionalLight* mDirectionalLight;
	ai::Camera* mCamera;
};

#endif //_TEST_SCENE2_H_
