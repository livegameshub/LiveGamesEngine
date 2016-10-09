#include "MeshResource.h"
#include "ProgramResource.h"
#include "MeshData.h"

namespace ai
{
	MeshResource::MeshResource(glm::u32 id, glm::u32 primitive, glm::u32 drawType, const Flag& flag)
		: BasicResource(id, flag)
		, mNormalOffset(0)
		, mTextureOffset(0)
		, mVertexSize(sizeof(glm::vec3))
		, mIndicesSize(0)
		, mPrimitive(primitive)
		, mDrawType(drawType)
	{
	}

	MeshResource::MeshResource(glm::u32 id, const std::string& file)
		: BasicResource(id, file)
		, mNormalOffset(0)
		, mTextureOffset(0)
		, mVertexSize(sizeof(glm::vec3))
		, mIndicesSize(0)
		, mPrimitive(0)
		, mDrawType(STATIC_MESH_DRAW)
	{
	}

	MeshResource::~MeshResource()
	{
	}

	void MeshResource::BindVbo() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mBuffers[VBO_BUFFER]);
	}

	void MeshResource::BindIbo() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[IBO_BUFFER]);
	}

	glm::u32 MeshResource::GetIndicesSize() const
	{
		return mIndicesSize;
	}

	glm::u32 MeshResource::GetPrimitive() const
	{
		return mPrimitive;
	}

	glm::u32 MeshResource::GetDrawType() const
	{
		return mDrawType;
	}

	bool MeshResource::ReadDataFromFile()
	{
		std::ifstream read(ASSETS_PATH + mResourceFile, std::ios::in);

		if (!read.is_open())
		{
			return false;
		}

		glm::u32 flag;
		glm::u32 vertices_size;

		read >> flag;
		read >> mPrimitive;
		read >> vertices_size;

		mFlag.Add(flag);

		//u32 reserve_size = CalculateReserveSize();

		std::vector<glm::f32> vertices;
		// TODO 
		// rezolve this reserve
		//vertices.reserve(vertices_size * reserve_size);

		for (glm::u32 i = 0; i < vertices_size; ++i)
		{
			glm::vec3 position;

			read >> position.x >> position.y >> position.z;

			vertices.emplace_back(position.x);
			vertices.emplace_back(position.y);
			vertices.emplace_back(position.z);

			if (mFlag.IsSet(MESH_NORMAL_FLAG))
			{
				glm::vec3 normal;

				read >> normal.x >> normal.y >> normal.z;

				vertices.emplace_back(normal.x);
				vertices.emplace_back(normal.y);
				vertices.emplace_back(normal.z);
			}
		}

		glm::u16 index;

		read >> mIndicesSize;

		std::vector<glm::u16> indices;
		indices.reserve(mIndicesSize);

		for (glm::u32 i = 0; i < mIndicesSize; ++i)
		{
			read >> index;

			indices.emplace_back(index);
		}

		read.close();

		/* upload the data into the Gpu memory */
		UploadData(vertices, indices);

		return true;
	}

	bool MeshResource::Create()
	{
		/* create the buffers */
		if (!CreateBuffers())
		{
			return false;
		}

		/* read the data from a file if you have it */
		if (mResourceFile.size() > 0)
		{
			return ReadDataFromFile();
		}

		return true;
	}

	glm::u32 MeshResource::GetVertexSize() const
	{
		return mVertexSize;
	}

	void MeshResource::Draw() const
	{
		glDrawElements(mPrimitive, mIndicesSize, GL_UNSIGNED_SHORT, static_cast<const void*>(0));
	}

	bool MeshResource::CreateBuffers()
	{
		glGenBuffers(COUNT, &mBuffers[0]);

		if (!mBuffers[VBO_BUFFER] || !mBuffers[IBO_BUFFER])
		{
			return false;
		}

		return true;
	}

	void MeshResource::CalculateVertexSize()
	{
		if (mFlag.IsSet(MESH_NORMAL_FLAG))
		{
			mNormalOffset += mVertexSize;
			mVertexSize += sizeof(glm::vec3);
		}
	}

	void MeshResource::UploadData(const MeshData& meshData)
	{
		UploadData(meshData.GetVertices(), meshData.GetIndices());
	}

	bool MeshResource::Release()
	{
		if (!mBuffers[VBO_BUFFER] || !mBuffers[IBO_BUFFER])
		{
			return false;
		}

		glDeleteBuffers(COUNT, &mBuffers[0]);

		for (glm::u32 i = 0; i < COUNT; ++i)
		{
			mBuffers[i] = 0;
		}

		return true;
	}

	void MeshResource::UploadAttributes(const glm::i32* attributes) const
	{
		glm::i32 position = attributes[ProgramResource::AttributeIndex::POSITION_INDEX];
		glm::i32 normal = attributes[ProgramResource::AttributeIndex::NORMAL_INDEX];

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

	void MeshResource::UploadData(const std::vector<glm::f32>& vertices, const std::vector<glm::u16>& indices)
	{
		CalculateVertexSize();

		BindVbo();
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::f32), &vertices[0], mDrawType);

		BindIbo();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::u16), &indices[0], mDrawType);
	}
}