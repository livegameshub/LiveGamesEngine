#include "Exporter.h"

#include <fstream>
#include <freeimage/FreeImage.h>

namespace ai
{
	bool Exporter::ExportTexture(const std::string& file)
	{
		/* read the input texture */

		std::string temp_file = "Input/" + file;

		FREE_IMAGE_FORMAT format = FreeImage_GetFileType(temp_file.c_str());

		if (format == -1)
		{
			std::cout << "Could not find image" << file << std::endl;
			return false;
		}

		if (format == FIF_UNKNOWN)
		{
			std::cout << "Image format unkown" << std::endl;
			return false;
		}

		FIBITMAP* bitmap = FreeImage_Load(format, temp_file.c_str());

		int bits_per_pixel = FreeImage_GetBPP(bitmap);

		if (bits_per_pixel == 32)
		{
			std::cout << "Image is 32 bits per pixel" << std::endl;
		}
		else if (bits_per_pixel == 24)
		{
			std::cout << "Image is 24 bits per pixel" << std::endl;
		}

		int image_width = FreeImage_GetWidth(bitmap);
		int image_height = FreeImage_GetHeight(bitmap);

		std::cout << "Image: " << file << " is size: " << image_width << "x" << image_height << std::endl;

		unsigned char* textureData = FreeImage_GetBits(bitmap);

		/* write the output texture */

		std::string new_file = "Output/" + file;

		new_file.erase(new_file.find('.'), new_file.length());
		new_file.append(".texture");

		FILE * pFile;

		fopen_s(&pFile, new_file.c_str(), "wb");

		fwrite(&image_width, sizeof(int), 1, pFile);
		fwrite(&image_height, sizeof(int), 1, pFile);
		fwrite(&bits_per_pixel, sizeof(int), 1, pFile);

		fclose(pFile);

		FreeImage_Unload(bitmap);

		return true;
	}
}
