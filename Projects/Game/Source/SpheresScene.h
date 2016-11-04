#ifndef _SPHERES_SCENE_H_
#define _SPHERES_SCENE_H_

#include "Scene.h"
#include "Camera.h"
#include "MeshRenderer.h"

class SpheresScene : public lg::Scene
{
public:
	SpheresScene();
	SpheresScene(const vec3& ambientLight);

	~SpheresScene();

	void init() override;
	void update() override;

private:
	vector<lg::Node*> mSpheres;

	lg::DirectionalLight* mDirectionalLight;
	lg::Camera* mCamera;
};

#endif //_SPHERES_SCENE_H_
