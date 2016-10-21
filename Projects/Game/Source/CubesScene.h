#ifndef _CUBES_SCENE_H_
#define _CUBES_SCENE_H_

#include "Scene.h"
#include "Camera.h"
#include "Model.h"

class CubesScene : public ai::Scene
{
public:
	CubesScene();
	CubesScene(const glm::vec3& ambientLight);

	~CubesScene();

	void init() override;
	void update() override;

private:
	std::vector<ai::Model*> mCubes;

	ai::DirectionalLight* mDirectionalLight;
	ai::Camera* mCamera;
};

#endif //_CUBES_SCENE_H_
