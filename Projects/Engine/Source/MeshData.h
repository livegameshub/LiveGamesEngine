#ifndef _MESH_DATA_H_
#define _MESH_DATA_H_

#include "EngineUtil.h"

namespace ai
{
	class ENGINE_API MeshData
	{
	public:
		MeshData();
		~MeshData();

		const std::vector<glm::f32>& GetVertices() const;
		const std::vector<glm::u16>& GetIndices() const;

		void AddVertex(const glm::vec3& position);
		void AddVertex(const glm::vec3& position, const glm::vec3& normal);

		void AddPoint(glm::u16 index_0);
		void AddLine(glm::u16 index_0, glm::u16 index_1);
		void AddTriangle(glm::u16 index_0, glm::u16 index_1, glm::u16 index_2);

		void ReserverVertices(glm::u32 size);
		void ReserveIndices(glm::u32 size);
		void ClearData();

	private:
		std::vector<glm::f32> mVertices;
		std::vector<glm::u16> mIndices;
	};
}

#endif
