
/* this is the main file of the application */

#ifndef _DEBUG
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif // _DEBUG

#include "Engine.h"
#include "Scenes.h"
#include "CubesScene.h"
#include "SpheresScene.h"
#include "SimpleScene.h"
#include "GameScene.h"

int main()
{
	lg::Scenes::instance().addScene(new CubesScene(vec3(0.2f)));
	lg::Scenes::instance().addScene(new SpheresScene(vec3(0.2f)));
	lg::Scenes::instance().addScene(new SimpleScene(vec3(0.2f)));
	lg::Scenes::instance().addScene(new GameScene());

	lg::Engine::setup("Live Games Hub");

	return 0;
}
