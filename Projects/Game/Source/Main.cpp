
/* this is the main file of the application */

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Application.h"

using namespace ai;

int main()
{
	Application::Start("Live Games Hub");

	return 0;
}
