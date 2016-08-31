#include "Common.h"

/* this function returns a value from keyboard */
int GetValue()
{
	int value;

	std::cout << "Insert a value ";

	std::cin >> value;

	return value;
}

/* this function returns a random value */
int GetRandomValue(int min, int max)
{
	return rand() % max + min;
}
