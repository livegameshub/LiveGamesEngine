#ifndef _MESH_H_
#define _MESH_H_

#include "Resource.h"
#include "Graphics.h"

namespace ai
{
	class MeshData;

	class ENGINE_API Mesh : public Resource
	{
	public:
		const glm::u32 LINES_MESH = GL_LINES;
		const glm::u32 POINTS_MESH = GL_POINTS;
		const glm::u32 TRIANGLES_MESH = GL_TRIANGLES;

		const glm::u32 STATIC_MESH_DRAW = GL_STATIC_DRAW;
		const glm::u32 DYNAMIC_MESH_DRAW = GL_DYNAMIC_DRAW;

		enum MeshBuffer : glm::u32
		{
			VBO_BUFFER,
			IBO_BUFFER,
			COUNT
		};

		enum MeshFlag : glm::u32
		{
			MESH_POSITION_FLAG = 1,
			MESH_NORMAL_FLAG = 2,
			MESH_TEXTURE_FLAG = 4
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
		void uploadData(const std::vector<glm::f32>& vertices, const std::vector<glm::u16>& indices);
		void uploadAttributes(const glm::i32* attributes) const;

		glm::u32 getVertexSize() const;
		glm::u32 getIndicesSize() const;
		glm::u32 getPrimitive() const;
		glm::u32 getDrawType() const;

		static glm::u32 calculateVerticesArraySize(glm::u32 size, const Flag& flag);

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
	};
}

#endif // _MESH_H_
