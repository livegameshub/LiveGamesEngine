#ifndef _EXPORTER_H_
#define _EXPORTER_H_

#include <iostream>
#include <string>
#include <glm/glm.hpp>

namespace lg
{
	class Exporter
	{
	public:
		enum MeshFlag : glm::u32
		{
			USE_NORMALS = 1,
			USE_TEXTURES = 2,
			REMOVE_DATA = 4
		};

		static bool ExportTexture(const std::string& file);
		static bool ExportModel(const std::string& file);
	};
}

#endif
