
/* this is the main file of the application */

#ifndef _DEBUG
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif // _DEBUG

#include "Engine.h"
#include "Scenes.h"
#include "CubesScene.h"
#include "SpheresScene.h"

int main()
{
	ai::Scenes::getInstance().addScene(new CubesScene(glm::vec3(0.2f)));
	ai::Scenes::getInstance().addScene(new SpheresScene(glm::vec3(0.2f)));
	
	ai::Engine::setup("Live Games Hub");

	return 0;
}
