#include "MeshData.h"

namespace ai
{
	MeshData::MeshData()
	{
	}

	MeshData::~MeshData()
	{
	}

	const std::vector<glm::f32>& MeshData::getVertices() const
	{
		return mVertices;
	}

	const std::vector<glm::u16>& MeshData::getIndices() const
	{
		return mIndices;
	}

	void MeshData::addVertex(const glm::vec3& position)
	{
		mVertices.emplace_back(position.x);
		mVertices.emplace_back(position.y);
		mVertices.emplace_back(position.z);
	}

	void MeshData::addVertex(const glm::vec3& position, const glm::vec3& normal)
	{
		addVertex(position);

		mVertices.emplace_back(normal.x);
		mVertices.emplace_back(normal.y);
		mVertices.emplace_back(normal.z);
	}

	void MeshData::addPoint(glm::u16 index_0)
	{
		mIndices.emplace_back(index_0);
	}

	void MeshData::addLine(glm::u16 index_0, glm::u16 index_1)
	{
		mIndices.emplace_back(index_0);
		mIndices.emplace_back(index_1);
	}

	void MeshData::addTriangle(glm::u16 index_0, glm::u16 index_1, glm::u16 index_2)
	{
		mIndices.emplace_back(index_0);
		mIndices.emplace_back(index_1);
		mIndices.emplace_back(index_2);
	}

	void MeshData::reserverVertices(glm::u32 size)
	{
		mVertices.reserve(size);
	}

	void MeshData::reserveIndices(glm::u32 size)
	{
		mIndices.reserve(size);
	}

	void MeshData::clearData()
	{
		mVertices.clear();
		mIndices.clear();
	}
}
