#ifndef _MESH_DATA_H_
#define _MESH_DATA_H_

#include "EngineUtil.h"

namespace ai
{
	struct Vector3;

	class ENGINE_API MeshData
	{
	public:
		MeshData();
		~MeshData();

		inline const std::vector<f32>& GetVertices() const;
		inline const std::vector<u16>& GetIndices() const;

		void AddVertex(const Vector3& position);
		void AddVertex(const Vector3& position, const Vector3& normal);

		void AddPoint(u16 index_0);
		void AddLine(u16 index_0, u16 index_1);
		void AddTriangle(u16 index_0, u16 index_1, u16 index_2);

		void ReserverVertices(u32 size);
		void ReserveIndices(u32 size);
		void ClearData();

	private:
		std::vector<f32> mVertices;
		std::vector<u16> mIndices;
	};
}

#endif
