#ifndef _MESH_DATA_H_
#define _MESH_DATA_H_

#include "EngineUtil.h"

namespace lg
{
	class ENGINE_API MeshData
	{
	public:
		MeshData();
		~MeshData();

		const std::vector<glm::f32>& getVertices() const;
		const std::vector<glm::u16>& getIndices() const;

		void addVec2(const glm::vec2& vector);
		void addVec3(const glm::vec3& vector);

		void addVertex(const glm::vec3& position);
		void addVertex(const glm::vec3& position, const glm::vec3& normal);
		void addvertex(const glm::vec3& position, const glm::vec2& texture);
		void addVertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texture);

		void addPoint(glm::u16 index_0);
		void addLine(glm::u16 index_0, glm::u16 index_1);
		void addTriangle(glm::u16 index_0, glm::u16 index_1, glm::u16 index_2);

		void reserverVertices(glm::u32 size);
		void reserveIndices(glm::u32 size);
		void clearData();

	private:
		std::vector<glm::f32> mVertices;
		std::vector<glm::u16> mIndices;
	};
}

#endif // _MESH_DATA_H_
