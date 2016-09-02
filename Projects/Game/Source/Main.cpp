
/* this is the main file of the application */

#include "Random.h"
#include "Window.h"

void main()
{
	ai::Random::Seed();

	ai::Window w;

	w.Create("Miau", 800, 600, 0, true);

	system("Pause");
}
