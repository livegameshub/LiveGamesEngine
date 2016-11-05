#ifndef _EXPORTER_H_
#define _EXPORTER_H_

#include <string>
#include <iostream>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

namespace lg
{
	class Exporter
	{
	public:
		enum MeshFlag : u32
		{
			USE_NORMALS = 1,
			USE_TEXTURES = 2,
			REMOVE_DATA = 4
		};

		static bool ExportTexture(const string& file);
		static bool ExportModel(const string& file);
		static bool ExportFont(const string& file);

	private:
		static void WriteTextureFile(const string& file, unsigned char* data, i32 width, i32 height, i32 bits, i32 format);
	};
}

#endif
