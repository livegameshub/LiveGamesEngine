
/* this is the main file of the application */

#ifndef _DEBUG
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Engine.h"
#include "SceneManager.h"
#include "TestScene.h"

int main()
{
	ai::SceneManager::GetInstance().AddScene(new ai::TestScene());
	
	ai::Engine::Setup("Live Games Hub");

	return 0;
}
