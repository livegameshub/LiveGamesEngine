
/* this is the main file of the application */

#ifndef _DEBUG
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif // _DEBUG

#include "Engine.h"
#include "SceneManager.h"
#include "TestScene.h"

int main()
{
	ai::SceneManager::getInstance().addScene(new ai::TestScene());
	
	ai::Engine::setup("Live Games Hub");

	return 0;
}
