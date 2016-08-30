
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

void SecondTestFunction()
{
	int a;
	int b;

	bool isTrue;

	std::cout << "insert value of a: ";
	std::cin >> a;

	std::cout << "insert value of b: ";
	std::cin >> b;

	std::cout << "a: " << a << " b: " << b << std::endl;

	std::cin >> isTrue;

	std::cout << "isTrue: " << isTrue << std::endl;
}

// this function returns a value from keyboard
int GetValue()
{
	int value;

	std::cout << "Insert a value ";

	std::cin >> value;

	return value;
}

int Sum(int a, int b)
{
	int c = a + b;

	return c;
}

int Difference(int a, int b)
{
	return a - b;
}

void ThirdTestFunction()
{
	int a = GetValue();
	int b = GetValue();

	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;

	int sum = Sum(a, b);
	std::cout << "Sum is: " << sum << std::endl;

	//int difference = a - b;
	std::cout << "Difference is: " << Difference(a, b) << std::endl;

	int multiply = a * b;
	std::cout << "Multiply is: " << multiply << std::endl;

	int divide = a / b;
	std::cout << "Divide is: " << divide << std::endl;

	// !!! this works just with integer (int)

	// this will give you the rest
	int modulo_divide = a % b;
	std::cout << "Modulo is: " << modulo_divide << std::endl;
}

void main()
{
	//TestFunction();
	//SecondTestFunction();

	ThirdTestFunction();

	system("Pause");
}
