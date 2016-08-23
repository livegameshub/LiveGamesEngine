
/* this is the main file of the application */

/*
type_of_data function_name(type_of_data parameter_name)
{
}
*/

void SecondFunction();

void FirstFunction()
{
	SecondFunction();
}

void SecondFunction()
{
}

void main()
{
	FirstFunction();
	SecondFunction();
}
