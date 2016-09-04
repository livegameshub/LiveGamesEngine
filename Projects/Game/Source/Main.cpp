
/* this is the main file of the application */

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Engine.h"

using namespace ai;

int main()
{
	Engine::GetInstance().Setup("DefaultWindow");

	return 0;
}
