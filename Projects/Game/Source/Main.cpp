
/* this is the main file of the application */

#ifndef _DEBUG
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif // _DEBUG

#include "Engine.h"
#include "Scenes.h"
#include "TestScene.h"
#include "TestScene2.h"

int main()
{
	ai::Scenes::getInstance().addScene(new ai::TestScene(glm::vec3(0.2f)));
	ai::Scenes::getInstance().addScene(new ai::TestScene2(glm::vec3(0.2f)));
	
	ai::Engine::setup("Live Games Hub");

	return 0;
}
