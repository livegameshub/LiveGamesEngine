#include "Exporter.h"

#include <fstream>
#include <freeimage/FreeImage.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace lg
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

		int bits = FreeImage_GetBPP(bitmap);

		if (bits == 32)
		{
			std::cout << "Image is 32 bits per pixel" << std::endl;
		}
		else if (bits == 24)
		{
			std::cout << "Image is 24 bits per pixel" << std::endl;
		}

		int image_width = FreeImage_GetWidth(bitmap);
		int image_height = FreeImage_GetHeight(bitmap);

		std::cout << "Image: " << file << " is size: " << image_width << "x" << image_height << std::endl;

		unsigned char* texture_data = FreeImage_GetBits(bitmap);

		/* write the output texture */

		std::string new_file = "Output/" + file;

		new_file.erase(new_file.find('.'), new_file.length());
		new_file.append(".texture");

		FILE * pFile;

		fopen_s(&pFile, new_file.c_str(), "wb");

		fwrite(&image_width, sizeof(int), 1, pFile);
		fwrite(&image_height, sizeof(int), 1, pFile);
		fwrite(&bits, sizeof(int), 1, pFile);

		glm::u32 image_size = image_width * image_height * (bits / 8);

		/* swap the pixels for BGRA */

		for (glm::u32 i = 0; i < image_size; i += bits / 8)
		{
			unsigned char temp = texture_data[i];

			texture_data[i] = texture_data[i + 2];
			texture_data[i + 2] = temp;
		}

		fwrite(texture_data, image_size, 1, pFile);

		fclose(pFile);

		FreeImage_Unload(bitmap);

		return true;
	}

	bool Exporter::ExportModel(const std::string& file)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile("Input/" + file, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

		if (!scene)
		{
			return false;
		}

		// export the meshes
		for (glm::u32 i = 0; i < scene->mNumMeshes; ++i)
		{
			const aiMesh* mesh = scene->mMeshes[i];

			// write the file
			std::ofstream new_file;
			new_file.setf(std::ios::fixed, std::ios::floatfield);
			std::string filename = mesh->mName.C_Str();

			new_file.open("Output/" + filename + ".mesh", std::ios::out | std::ios::binary);

			if (!new_file.is_open())
			{
				return false;
			}

			bool hasNormals;
			std::cout << "Export normals for " + filename + ".mesh? ";
			std::cin >> hasNormals;

			// check the mesh flags
			int flag = 0;
			if (mesh->HasNormals() && hasNormals)
			{
				flag |= USE_NORMALS;
			}

			if (mesh->HasTextureCoords(0))
			{
				flag |= USE_TEXTURES;
			}

			bool removeData;
			std::cout << "Remove data after loading? ";
			std::cin >> removeData;

			if (removeData)
			{
				flag |= REMOVE_DATA;
			}

			new_file << flag << std::endl;
			new_file << mesh->mPrimitiveTypes << std::endl;
			new_file << mesh->mNumVertices << std::endl;

			// write the vertices
			for (glm::u32 v = 0; v < mesh->mNumVertices; ++v)
			{
				const aiVector3D& position = mesh->mVertices[v];
				const aiVector3D& normal = mesh->mNormals[v];
				const aiVector3D& texture = mesh->mTextureCoords[0][v];

				new_file << position.x << " " << position.y << " " << position.z;

				if (flag & USE_NORMALS && hasNormals)
				{
					new_file << " " << normal.x << " " << normal.y << " " << normal.z;
				}

				if (flag & USE_TEXTURES)
				{
					new_file << " " << texture.x << " " << texture.y;
				}

				new_file << std::endl;
			}

			// write the indices
			new_file << mesh->mNumFaces * 3 << std::endl;

			for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
			{
				const aiFace& face = mesh->mFaces[j];

				// write the face into the file
				new_file << face.mIndices[0] << " " << face.mIndices[1] << " " << face.mIndices[2] << std::endl;
			}

			new_file.close();
		}

		return true;
	}
}
