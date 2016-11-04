#include "MeshData.h"

namespace lg
{
	MeshData::MeshData()
	{
	}

	MeshData::~MeshData()
	{
	}

	const vector<f32>& MeshData::getVertices() const
	{
		return mVertices;
	}

	const vector<u16>& MeshData::getIndices() const
	{
		return mIndices;
	}

	void MeshData::addVertex(const vec3& position)
	{
		addVec3(position);
	}

	void MeshData::addVertex(const vec3& position, const vec3& normal)
	{
		addVec3(position);
		addVec3(normal);
	}

	void MeshData::addVertex(const vec3& position, const vec2& texture)
	{
		addVec3(position);
		addVec2(texture);
	}

	void MeshData::addVertex(const vec3& position, const vec3& normal, const vec2& texture)
	{
		addVec3(position);
		addVec3(normal);
		addVec2(texture);
	}

	void MeshData::addVec3(const vec3& vector)
	{
		mVertices.emplace_back(vector.x);
		mVertices.emplace_back(vector.y);
		mVertices.emplace_back(vector.z);
	}

	void MeshData::addVec2(const vec2& vector)
	{
		mVertices.emplace_back(vector.x);
		mVertices.emplace_back(vector.y);
	}

	void MeshData::addPoint(u16 index_0)
	{
		mIndices.emplace_back(index_0);
	}

	void MeshData::addLine(u16 index_0, u16 index_1)
	{
		mIndices.emplace_back(index_0);
		mIndices.emplace_back(index_1);
	}

	void MeshData::addTriangle(u16 index_0, u16 index_1, u16 index_2)
	{
		mIndices.emplace_back(index_0);
		mIndices.emplace_back(index_1);
		mIndices.emplace_back(index_2);
	}

	void MeshData::reserverVertices(u32 size)
	{
		mVertices.reserve(size);
	}

	void MeshData::reserveIndices(u32 size)
	{
		mIndices.reserve(size);
	}

	void MeshData::clearData()
	{
		mVertices.clear();
		mIndices.clear();
	}
}
