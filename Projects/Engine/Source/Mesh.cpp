#include "Mesh.h"
#include "Program.h"
#include "Vector3.h"

namespace ai
{
	Mesh::Mesh(u32 id, u32 primitive, u32 drawType, const Flag& flag)
		: BasicResource(id, flag)
		, mNormalOffset(0)
		, mTextureOffset(0)
		, mVertexSize(sizeof(Vector3))
		, mIndicesSize(0)
		, mPrimitive(primitive)
		, mDrawType(drawType)
	{
	}

	Mesh::Mesh(u32 id, const std::string& file)
		: BasicResource(id, file)
		, mNormalOffset(0)
		, mTextureOffset(0)
		, mVertexSize(sizeof(Vector3))
		, mIndicesSize(0)
		, mPrimitive(0)
		, mDrawType(STATIC_MESH_DRAW)
	{
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::BindVbo() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mBuffers[VBO_BUFFER]);
	}

	void Mesh::BindIbo() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[IBO_BUFFER]);
	}

	u32 Mesh::GetIndicesSize() const
	{
		return mIndicesSize;
	}

	u32 Mesh::GetPrimitive() const
	{
		return mPrimitive;
	}

	u32 Mesh::GetDrawType() const
	{
		return mDrawType;
	}

	u32 Mesh::GetVertexSize() const
	{
		return mVertexSize;
	}

	void Mesh::Draw() const
	{
		glDrawElements(mPrimitive, mIndicesSize, GL_UNSIGNED_SHORT, static_cast<const void*>(0));
	}

	bool Mesh::CreateBuffers()
	{
		glGenBuffers(COUNT, &mBuffers[0]);

		if (!mBuffers[VBO_BUFFER] || !mBuffers[IBO_BUFFER])
		{
			return false;
		}

		return true;
	}

	void Mesh::CalculateVertexSize()
	{
		if (mFlag.IsSet(MESH_NORMAL_FLAG))
		{
			mNormalOffset += mVertexSize;
			mVertexSize += sizeof(Vector3);
		}
	}

	bool Mesh::Release()
	{
		if (!mBuffers[VBO_BUFFER] || !mBuffers[IBO_BUFFER])
		{
			return false;
		}

		glDeleteBuffers(COUNT, &mBuffers[0]);

		for (u32 i = 0; i < COUNT; ++i)
		{
			mBuffers[i] = 0;
		}

		return true;
	}

	void Mesh::UploadAttributes(const i32* attributes) const
	{
		i32 position = attributes[Program::AttributeIndex::POSITION_INDEX];
		i32 normal = attributes[Program::AttributeIndex::NORMAL_INDEX];

		if (position >= 0)
		{
			glEnableVertexAttribArray(position);
			glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, mVertexSize, static_cast<const void*>(0));
		}

		if (normal >= 0 && mNormalOffset > 0)
		{
			glEnableVertexAttribArray(normal);
			glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, mVertexSize, reinterpret_cast<const void*>(mNormalOffset));
		}
	}

	void Mesh::UploadData(const std::vector<f32>& vertices, const std::vector<u16>& indices)
	{
		CalculateVertexSize();

		BindVbo();
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(f32), &vertices[0], mDrawType);

		BindIbo();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u16), &indices[0], mDrawType);
	}
}
