#ifndef _SIMPLE_SCENE_H_
#define _SIMPLE_SCENE_H_

#include "Scene.h"
#include "Camera.h"
#include "MeshRenderer.h"

class SimpleScene : public lg::Scene
{
public:
	SimpleScene();
	SimpleScene(const glm::vec3& ambientLight);

	~SimpleScene();

	void init() override;
	void update() override;

private:
	std::vector<lg::MeshRenderer*> mPrimitives;

	lg::DirectionalLight* mDirectionalLight;
	lg::Camera* mCamera;
};

#endif // _SIMPLE_SCENE_H_
