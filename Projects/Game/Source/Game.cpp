#include "Game.h"
#include "Common.h"

int lifes = 5;
int choice = 0;

void GameLoop()
{
	std::cout << "Insert your choice: ";

	int my_choice;
	std::cin >> my_choice;

	if (my_choice < choice)
	{
		std::cout << "Your choice is smaller" << std::endl;

		lifes = lifes - 1;
	}
	else if (my_choice > choice)
	{
		std::cout << "Your choice is bigger" << std::endl;

		lifes = lifes - 1;
	}
	else
	{
		std::cout << "Perfect, your scored!" << std::endl;

		StartMenu();
	}

	if (lifes == 0)
	{
		std::cout << "No luck for you this time!" << std::endl;
		std::cout << "The choice was: " << choice << std::endl;

		StartMenu();
	}
	else
	{
		GameLoop();
	}
}

void StartMenu()
{
	std::cout << "Welcome, do you want to play?" << std::endl;
	std::cout << "Options: 1 - yes, 0 - no" << std::endl;
	std::cout << "Your choice ";

	bool is_playing;
	std::cin >> is_playing;

	if (is_playing)
	{
		// get a new random every time
		choice = GetRandomValue(1, 100);

		// reset the lifes
		lifes = 5;

		GameLoop();
	}
}