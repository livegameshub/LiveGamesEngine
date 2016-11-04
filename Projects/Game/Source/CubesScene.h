#ifndef _CUBES_SCENE_H_
#define _CUBES_SCENE_H_

#include "Scene.h"
#include "Camera.h"
#include "MeshRenderer.h"

class CubesScene : public lg::Scene
{
public:
	CubesScene();
	CubesScene(const vec3& ambientLight);

	~CubesScene();

	void init() override;
	void update() override;

private:
	vector<lg::Node*> mCubes;

	lg::DirectionalLight* mDirectionalLight;
	lg::Camera* mCamera;
};

#endif //_CUBES_SCENE_H_
