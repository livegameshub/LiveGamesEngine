#include "Exporter.h"

int main()
{
	int option;
	std::string file;
	
	std::cout << "Insert your file: ";
	std::cin >> file;

	std::cout << "1 - Texture" << std::endl;
	std::cout << "2 - Model" << std::endl;
	std::cout << "3 - Font" << std::endl;

	std::cin >> option;

	switch(option)
	{
		case 1:
		{
			lg::Exporter::ExportTexture(file);
			break;
		}
		case 2:
		{
			lg::Exporter::ExportModel(file);
			break;
		}
		case 3:
		{
			lg::Exporter::ExportFont(file);
			break;
		}
	}

	system("PAUSE");
	return 0;
}
