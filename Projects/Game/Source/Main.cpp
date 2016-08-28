
/* this is the main file of the application */

#include <iostream>

void TestFunction()
{
	/* types of data */

	int population = 15;

	int size;
	size = 5;

	float price = 3.5f;

	float bonus;
	bonus = 7.899f;

	double kilograms = 4.5;

	double volume;
	volume = 3.2;

	bool isTrue = false;

	bool isSleeping;
	isSleeping = true;

	char character = 'a';

	char letter;
	letter = 'l';

	/* output things in the console */

	std::cout << "The population value is: " << population << "\n";
	std::cout << "The price is: " << price << std::endl;
	std::cout << "The value of isTrue is: " << isTrue << std::endl;
	std::cout << "The character is: " << character << std::endl;;
}

void main()
{
	TestFunction();

	system("Pause");
}
