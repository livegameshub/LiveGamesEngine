#include "Mesh.h"
#include "Program.h"
#include "MeshData.h"

namespace ai
{
	Mesh::Mesh(glm::u32 id, glm::u32 primitive, glm::u32 drawType, const Flag& flag)
		: Resource(id, flag)
		, mNormalOffset(0)
		, mTextureOffset(0)
		, mVertexSize(sizeof(glm::vec3))
		, mIndicesSize(0)
		, mPrimitive(primitive)
		, mDrawType(drawType)
	{
	}

	Mesh::Mesh(glm::u32 id, const std::string& file)
		: Resource(id, file)
		, mNormalOffset(0)
		, mTextureOffset(0)
		, mVertexSize(sizeof(glm::vec3))
		, mIndicesSize(0)
		, mPrimitive(0)
		, mDrawType(STATIC_MESH_DRAW)
	{
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::bindVbo() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mBuffers[VBO_BUFFER]);
	}

	void Mesh::bindIbo() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[IBO_BUFFER]);
	}

	glm::u32 Mesh::getIndicesSize() const
	{
		return mIndicesSize;
	}

	glm::u32 Mesh::getPrimitive() const
	{
		return mPrimitive;
	}

	glm::u32 Mesh::getDrawType() const
	{
		return mDrawType;
	}

	MeshData& Mesh::getData()
	{
		return mData;
	}

	glm::u32 Mesh::calculateVerticesArraySize(glm::u32 size) const
	{
		glm::u32 reserve_size = 3;

		if (mFlag.isSet(MESH_NORMAL_FLAG))
		{
			reserve_size += 3;
		}

		return size * reserve_size;
	}

	bool Mesh::readDataFromFile()
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

		mFlag.add(flag);

		mData.reserverVertices(calculateVerticesArraySize(vertices_size));

		for (glm::u32 i = 0; i < vertices_size; ++i)
		{
			glm::vec3 position;

			read >> position.x >> position.y >> position.z;

			mData.addVec3(position);

			if (mFlag.isSet(MESH_NORMAL_FLAG))
			{
				glm::vec3 normal;

				read >> normal.x >> normal.y >> normal.z;

				mData.addVec3(normal);
			}
		}

		glm::u16 index;
		glm::u32 indices_size;

		read >> indices_size;

		mData.reserveIndices(indices_size);

		for (glm::u32 i = 0; i < indices_size; ++i)
		{
			read >> index;

			mData.addPoint(index);
		}

		read.close();

		return true;
	}

	bool Mesh::create()
	{
		/* create the buffers */
		if (!createBuffers())
		{
			return false;
		}

		/* read the data from a file if you have it */
		if (mResourceFile.size() > 0)
		{
			if (!readDataFromFile())
			{
				return false;
			}
		}

		/* upload the data into the Gpu memory */
		uploadData(mData);

		/* clear the data if is not needed */
		if (mFlag.isSet(MESH_REMOVE_DATA_FLAG))
		{
			mData.clearData();
		}

		return true;
	}

	glm::u32 Mesh::getVertexSize() const
	{
		return mVertexSize;
	}

	void Mesh::draw() const
	{
		glDrawElements(mPrimitive, mIndicesSize, GL_UNSIGNED_SHORT, static_cast<const void*>(0));
	}

	bool Mesh::createBuffers()
	{
		glGenBuffers(COUNT, &mBuffers[0]);

		if (!mBuffers[VBO_BUFFER] || !mBuffers[IBO_BUFFER])
		{
			return false;
		}

		return true;
	}

	void Mesh::calculateVertexSize()
	{
		if (mFlag.isSet(MESH_NORMAL_FLAG))
		{
			mNormalOffset += mVertexSize;
			mVertexSize += sizeof(glm::vec3);
		}
	}

	void Mesh::uploadData(const MeshData& meshData)
	{
		calculateVertexSize();

		bindVbo();
		glBufferData(GL_ARRAY_BUFFER, meshData.getVertices().size() * sizeof(glm::f32), &meshData.getVertices()[0], mDrawType);

		bindIbo();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData.getIndices().size() * sizeof(glm::u16), &meshData.getIndices()[0], mDrawType);

		mIndicesSize = meshData.getIndices().size();
	}

	bool Mesh::release()
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

	void Mesh::uploadAttributes(const glm::i32* attributes) const
	{
		glm::i32 position = attributes[Program::AttributeIndex::POSITION_INDEX];
		glm::i32 normal = attributes[Program::AttributeIndex::NORMAL_INDEX];

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
}
