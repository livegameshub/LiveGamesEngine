#include "MeshData.h"
#include "Vector3.h"

namespace ai
{
	MeshData::MeshData()
	{
	}

	MeshData::~MeshData()
	{
	}

	const std::vector<f32>& MeshData::GetVertices() const
	{
		return mVertices;
	}

	const std::vector<u16>& MeshData::GetIndices() const
	{
		return mIndices;
	}

	void MeshData::AddVertex(const Vector3& position)
	{
		mVertices.emplace_back(position.x);
		mVertices.emplace_back(position.y);
		mVertices.emplace_back(position.z);
	}

	void MeshData::AddVertex(const Vector3& position, const Vector3& normal)
	{
		AddVertex(position);

		mVertices.emplace_back(normal.x);
		mVertices.emplace_back(normal.y);
		mVertices.emplace_back(normal.z);
	}

	void MeshData::AddPoint(u16 index_0)
	{
		mIndices.emplace_back(index_0);
	}

	void MeshData::AddLine(u16 index_0, u16 index_1)
	{
		mIndices.emplace_back(index_0);
		mIndices.emplace_back(index_1);
	}

	void MeshData::AddTriangle(u16 index_0, u16 index_1, u16 index_2)
	{
		mIndices.emplace_back(index_0);
		mIndices.emplace_back(index_1);
		mIndices.emplace_back(index_2);
	}

	void MeshData::ReserverVertices(u32 size)
	{
		mVertices.reserve(size);
	}

	void MeshData::ReserveIndices(u32 size)
	{
		mIndices.reserve(size);
	}

	void MeshData::ClearData()
	{
		mVertices.clear();
		mIndices.clear();
	}
}
