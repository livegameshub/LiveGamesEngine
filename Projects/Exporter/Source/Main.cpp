#include "Exporter.h"

int main()
{
	int option;
	string file;

	bool tryAgain = true;
	
	while (tryAgain)
	{
		cout << "Insert your file: ";
		cin >> file;

		cout << "1 - Texture" << endl;
		cout << "2 - Model" << endl;
		cout << "3 - Font" << endl;

		cin >> option;

		switch (option)
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

		cout << "Export another file? ";
		cin >> tryAgain;
	}

	system("PAUSE");
	return 0;
}
