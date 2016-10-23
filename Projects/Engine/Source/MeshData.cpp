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
		addVec3(position);
	}

	void MeshData::addVertex(const glm::vec3& position, const glm::vec3& normal)
	{
		addVec3(position);
		addVec3(normal);
	}

	void MeshData::addvertex(const glm::vec3& position, const glm::vec2& texture)
	{
		addVec3(position);
		addVec2(texture);
	}

	void MeshData::addVertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texture)
	{
		addVec3(position);
		addVec3(normal);
		addVec2(texture);
	}

	void MeshData::addVec3(const glm::vec3& vector)
	{
		mVertices.emplace_back(vector.x);
		mVertices.emplace_back(vector.y);
		mVertices.emplace_back(vector.z);
	}

	void MeshData::addVec2(const glm::vec2& vector)
	{
		mVertices.emplace_back(vector.x);
		mVertices.emplace_back(vector.y);
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
