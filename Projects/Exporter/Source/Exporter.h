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
			MESH_NORMAL_FLAG = 1,
			MESH_TEXTURE_FLAG = 2,

			MESH_REMOVE_DATA_FLAG = 4
		};

		static bool ExportTexture(const std::string& file);
		static bool ExportModel(const std::string& file);
	};
}

#endif
