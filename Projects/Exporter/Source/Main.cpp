#include "Exporter.h"

int main()
{
	std::string file;
	bool isTexture;

	std::cout << "Insert your file: ";
	std::cin >> file;

	std::cout << "Is texture? ";
	std::cin >> isTexture;

	ai::Exporter::ExportTexture(file);
	
	system("PAUSE");
	return 0;
}
