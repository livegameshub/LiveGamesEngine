#ifndef _TEST_SCENE_H_
#define _TEST_SCENE_H_

#include "Scene.h"
#include "Camera.h"
#include "Model.h"

class TestScene : public ai::Scene
{
public:
	TestScene();
	TestScene(const glm::vec3& ambientLight);

	~TestScene();

	void init() override;
	void update() override;
	void release() override;

private:
	std::vector<ai::Model*> mCubes;

	ai::DirectionalLight* mDirectionalLight;
	ai::Camera* mCamera;
};

#endif //_TEST_SCENE_H_
