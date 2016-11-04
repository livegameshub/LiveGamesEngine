#ifndef _SIMPLE_SCENE_H_
#define _SIMPLE_SCENE_H_

#include "Scene.h"
#include "Camera.h"
#include "MeshRenderer.h"

class SimpleScene : public lg::Scene
{
public:
	SimpleScene();
	SimpleScene(const vec3& ambientLight);

	~SimpleScene();

	void init() override;
	void update() override;

private:
	vector<lg::Node*> mPrimitives;

	lg::DirectionalLight* mDirectionalLight;
	lg::Camera* mCamera;
};

#endif // _SIMPLE_SCENE_H_
