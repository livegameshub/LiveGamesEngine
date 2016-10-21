#ifndef _SPHERES_SCENE_H_
#define _SPHERES_SCENE_H_

#include "Scene.h"
#include "Camera.h"
#include "Model.h"

class SpheresScene : public ai::Scene
{
public:
	SpheresScene();
	SpheresScene(const glm::vec3& ambientLight);

	~SpheresScene();

	void init() override;
	void update() override;

private:
	std::vector<ai::Model*> mSpheres;

	ai::DirectionalLight* mDirectionalLight;
	ai::Camera* mCamera;
};

#endif //_SPHERES_SCENE_H_