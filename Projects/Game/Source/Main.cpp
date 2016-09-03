
/* this is the main file of the application */

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Engine.h"

using namespace ai;

int main()
{
	Engine& engine = Engine::GetInstance();
	
	if (engine.Setup("DefaultWindow"))
	{
		engine.Run();
	}

	return 0;
}
