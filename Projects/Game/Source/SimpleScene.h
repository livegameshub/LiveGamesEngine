#ifndef _SIMPLE_SCENE_H_
#define _SIMPLE_SCENE_H_

#include "Scene.h"
#include "Camera.h"
#include "Model.h"

class SimpleScene : public ai::Scene
{
public:
	SimpleScene();
	SimpleScene(const glm::vec3& ambientLight);

	~SimpleScene();

	void init() override;
	void update() override;

private:
	std::vector<ai::Model*> mPrimitives;

	ai::DirectionalLight* mDirectionalLight;
	ai::Camera* mCamera;
};

#endif // _SIMPLE_SCENE_H_
