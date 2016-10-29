#ifndef _MESH_H_
#define _MESH_H_

#include "Resource.h"
#include "Graphics.h"
#include "MeshData.h"

namespace lg
{
	class MeshData;

	class ENGINE_API Mesh : public Resource
	{
	public:
		static const glm::u32 LINES = GL_LINES;
		static const glm::u32 POINTS = GL_POINTS;
		static const glm::u32 TRIANGLES = GL_TRIANGLES;

		static const glm::u32 STATIC_DRAW = GL_STATIC_DRAW;
		static const glm::u32 DYNAMIC_DRAW = GL_DYNAMIC_DRAW;

		enum MeshBuffer : glm::u32
		{
			VBO_BUFFER,
			IBO_BUFFER,
			COUNT
		};

		enum MeshFlag : glm::u32
		{
			USE_NORMALS = 1,
			USE_TEXTURES = 2,
			REMOVE_DATA = 4
		};

		Mesh(glm::u32 id, const std::string& file);
		Mesh(glm::u32 id, glm::u32 primitive, glm::u32 drawType, const Flag& flag);

		~Mesh();

		void draw() const;  
		void bindVbo() const;
		void bindIbo() const;

		bool createBuffers();
		bool readDataFromFile();
		void calculateVertexSize();

		void uploadData(const MeshData& meshData);
		void uploadAttributes(const glm::i32* attributes) const;

		glm::u32 calculateVerticesArraySize(glm::u32 size) const;

		glm::u32 getVertexSize() const;
		glm::u32 getIndicesSize() const;
		glm::u32 getPrimitive() const;
		glm::u32 getDrawType() const;

		MeshData& getData();

	private:
		bool create() override;
		bool release() override;

		glm::u32 mBuffers[COUNT];

		glm::u32 mNormalOffset;
		glm::u32 mTextureOffset;

		glm::u32 mVertexSize;
		glm::u32 mIndicesSize;
		glm::u32 mPrimitive;
		glm::u32 mDrawType;

		MeshData mData;
	};
}

#endif // _MESH_H_
