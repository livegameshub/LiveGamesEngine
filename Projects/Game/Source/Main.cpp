
/* this is the main file of the application */

#ifndef _DEBUG
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Engine.h"

int main()
{
	ai::Engine::Setup("Live Games Hub", "Assets/");

	return 0;
}
