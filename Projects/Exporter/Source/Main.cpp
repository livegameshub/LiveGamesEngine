#include "Exporter.h"

int main()
{
	std::string file;
	bool isTexture;
	bool isModel;

	std::cout << "Insert your file: ";
	std::cin >> file;

	std::cout << "Is a texture? ";
	std::cin >> isTexture;

	if (isTexture)
	{
		ai::Exporter::ExportTexture(file);
	}
	else
	{
		std::cout << "Is a model? ";
		std::cin >> isModel;

		if (isModel)
		{
			ai::Exporter::ExportModel(file);
		}
	}

	system("PAUSE");
	return 0;
}
