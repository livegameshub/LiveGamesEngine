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

		const vector<f32>& getVertices() const;
		const vector<u16>& getIndices() const;

		void addVec2(const vec2& vector);
		void addVec3(const vec3& vector);

		void addVertex(const vec3& position);
		void addVertex(const vec3& position, const vec3& normal);
		void addVertex(const vec3& position, const vec2& texture);
		void addVertex(const vec3& position, const vec3& normal, const vec2& texture);

		void addPoint(u16 index_0);
		void addLine(u16 index_0, u16 index_1);
		void addTriangle(u16 index_0, u16 index_1, u16 index_2);

		void reserverVertices(u32 size);
		void reserveIndices(u32 size);
		void clearData();

	private:
		vector<f32> mVertices;
		vector<u16> mIndices;
	};
}

#endif // _MESH_DATA_H_
