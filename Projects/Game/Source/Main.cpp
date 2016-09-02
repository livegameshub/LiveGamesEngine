
/* this is the main file of the application */

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Random.h"
#include "Window.h"

int main()
{
	ai::Random::Seed();

	ai::Window w;

	w.Create("TestWindow", 800, 600, 0, true);

	while (!w.IsClosing())
	{
		w.SwapBuffers();

		ai::Window::HandleEvents();
	}

	ai::Window::ReleaseApi();

	return 0;
}
