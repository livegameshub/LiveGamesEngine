#include "MeshData.h"

namespace ai
{
	MeshData::MeshData()
	{
	}

	MeshData::~MeshData()
	{
	}

	const std::vector<glm::f32>& MeshData::GetVertices() const
	{
		return mVertices;
	}

	const std::vector<glm::u16>& MeshData::GetIndices() const
	{
		return mIndices;
	}

	void MeshData::AddVertex(const glm::vec3& position)
	{
		mVertices.emplace_back(position.x);
		mVertices.emplace_back(position.y);
		mVertices.emplace_back(position.z);
	}

	void MeshData::AddVertex(const glm::vec3& position, const glm::vec3& normal)
	{
		AddVertex(position);

		mVertices.emplace_back(normal.x);
		mVertices.emplace_back(normal.y);
		mVertices.emplace_back(normal.z);
	}

	void MeshData::AddPoint(glm::u16 index_0)
	{
		mIndices.emplace_back(index_0);
	}

	void MeshData::AddLine(glm::u16 index_0, glm::u16 index_1)
	{
		mIndices.emplace_back(index_0);
		mIndices.emplace_back(index_1);
	}

	void MeshData::AddTriangle(glm::u16 index_0, glm::u16 index_1, glm::u16 index_2)
	{
		mIndices.emplace_back(index_0);
		mIndices.emplace_back(index_1);
		mIndices.emplace_back(index_2);
	}

	void MeshData::ReserverVertices(glm::u32 size)
	{
		mVertices.reserve(size);
	}

	void MeshData::ReserveIndices(glm::u32 size)
	{
		mIndices.reserve(size);
	}

	void MeshData::ClearData()
	{
		mVertices.clear();
		mIndices.clear();
	}
}
