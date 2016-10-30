#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "Scene.h"
#include "Texture.h"

class GameScene : public lg::Scene
{
public:
	GameScene();
	~GameScene();

	void init() override;
	void update() override;

private:
	glm::f32 mScaleFactor;
};

#endif // _GAME_SCENE_H_
