#include "Exporter.h"

#include <fstream>
#include <freeimage/FreeImage.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <ft2build.h>
#include FT_FREETYPE_H  

#include <glew/glew.h>

namespace lg
{
	bool Exporter::ExportTexture(const string& file)
	{
		/* read the input texture */

		string temp_file = "Input/" + file;

		FREE_IMAGE_FORMAT format = FreeImage_GetFileType(temp_file.c_str());

		if (format == -1)
		{
			cout << "Could not find image" << file << endl;
			return false;
		}

		if (format == FIF_UNKNOWN)
		{
			cout << "Image format unkown" << endl;
			return false;
		}

		FIBITMAP* bitmap = FreeImage_Load(format, temp_file.c_str());

		int texture_format = 0;
		int bits = FreeImage_GetBPP(bitmap);

		if (bits == 32)
		{
			texture_format = GL_RGBA;
			cout << "Image is 32 bits per pixel" << endl;
		}
		else if (bits == 24)
		{
			texture_format = GL_RGB;
			cout << "Image is 24 bits per pixel" << endl;
		}

		int image_width = FreeImage_GetWidth(bitmap);
		int image_height = FreeImage_GetHeight(bitmap);

		cout << "Image: " << file << " is size: " << image_width << "x" << image_height << endl;

		unsigned char* texture_data = FreeImage_GetBits(bitmap);

		u32 image_size = image_width * image_height * (bits / 8);

		/* swap the pixels for RGBA */

		for (u32 i = 0; i < image_size; i += bits / 8)
		{
			unsigned char temp = texture_data[i];

			texture_data[i] = texture_data[i + 2];
			texture_data[i + 2] = temp;
		}

		string new_file = "Output/" + file;

		new_file.erase(new_file.find('.'), new_file.length());
		new_file.append(".texture");

		/* write the output texture */
		WriteTextureFile(new_file, texture_data, image_width, image_height, bits, texture_format);

		FreeImage_Unload(bitmap);

		return true;
	}

	bool Exporter::ExportModel(const string& file)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile("Input/" + file, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

		if (!scene)
		{
			return false;
		}

		// export the meshes
		for (u32 i = 0; i < scene->mNumMeshes; ++i)
		{
			const aiMesh* mesh = scene->mMeshes[i];

			// write the file
			ofstream new_file;
			new_file.setf(ios::fixed, ios::floatfield);
			string filename = mesh->mName.C_Str();

			new_file.open("Output/" + filename + ".mesh", ios::out | ios::binary);

			if (!new_file.is_open())
			{
				return false;
			}

			bool hasNormals;
			cout << "Export normals for " + filename + ".mesh? ";
			cin >> hasNormals;

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
			cout << "Remove data after loading? ";
			cin >> removeData;

			if (removeData)
			{
				flag |= REMOVE_DATA;
			}

			new_file << flag << endl;
			new_file << mesh->mPrimitiveTypes << endl;
			new_file << mesh->mNumVertices << endl;

			// write the vertices
			for (u32 v = 0; v < mesh->mNumVertices; ++v)
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

				new_file << endl;
			}

			// write the indices
			new_file << mesh->mNumFaces * 3 << endl;

			for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
			{
				const aiFace& face = mesh->mFaces[j];

				// write the face into the file
				new_file << face.mIndices[0] << " " << face.mIndices[1] << " " << face.mIndices[2] << endl;
			}

			new_file.close();
		}

		return true;
	}

	bool Exporter::ExportFont(const string& file)
	{
		string new_file = "Input/" + file;

		FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			cout << "ERROR::FREETYPE: Could not init FreeType Library" << endl;
			return false;
		}

		FT_Face face;
		if (FT_New_Face(ft, new_file.c_str(), 0, &face))
		{
			cout << "ERROR::FREETYPE: Failed to load font" << endl;
			return false;
		}

		int font_size;
		cout << "Insert the font size ";
		cin >> font_size;

		FT_Set_Pixel_Sizes(face, 0, font_size);

		string font_file = "Output/" + file;
		font_file.erase(font_file.find('.'), font_file.length());
		font_file.append(".font");

		FILE * pFile;
		fopen_s(&pFile, font_file.c_str(), "wb");

		// write the numbers of the character
		i32 number_of_chars = 1;
		fwrite(&number_of_chars, sizeof(int), 1, pFile);

		// look after every character
		//for (u32 c = 0; c < 128; ++c)
		{
			if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
			{
				cout << "ERROR::FREETYTPE: Failed to load Glyph" << endl;
				return false;
			}

			const FT_Bitmap& character = face->glyph->bitmap;

			ivec2 size = ivec2(character.width, character.rows);
			ivec2 bearing = ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
			u32 advance = face->glyph->advance.x;

			fwrite(&size, sizeof(ivec2), 1, pFile);
			fwrite(&bearing, sizeof(ivec2), 1, pFile);
			fwrite(&advance, sizeof(u32), 1, pFile);

			string output_file = "Output/" + file;
			output_file.erase(output_file.find('.'), output_file.length());
			output_file.append(".texture");

			WriteTextureFile(output_file, character.buffer, character.width, character.rows, 8, GL_RED);
		}

		fclose(pFile);

		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		return true;
	}

	void Exporter::WriteTextureFile(const string& file, unsigned char* data, i32 width, i32 height, i32 bits, i32 format)
	{
		FILE * pFile;

		fopen_s(&pFile, file.c_str(), "wb");

		fwrite(&width, sizeof(int), 1, pFile);
		fwrite(&height, sizeof(int), 1, pFile);
		fwrite(&bits, sizeof(int), 1, pFile);
		fwrite(&format, sizeof(int), 1, pFile);

		fwrite(data, width * height * (bits / 8), 1, pFile);

		fclose(pFile);
	}
}
