#ifndef _MESH_H_
#define _MESH_H_

#include "BasicResource.h"
#include "Graphics.h"

namespace ai
{
	class MeshData;

	class ENGINE_API Mesh : public BasicResource
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

		void Draw() const;  

		void BindVbo() const;
		void BindIbo() const;

		bool CreateBuffers();
		bool ReadDataFromFile();

		void CalculateVertexSize();
		
		void UploadData(const MeshData& meshData);
		void UploadData(const std::vector<glm::f32>& vertices, const std::vector<glm::u16>& indices);
		void UploadAttributes(const glm::i32* attributes) const;

		inline glm::u32 GetVertexSize() const;
		inline glm::u32 GetIndicesSize() const;
		inline glm::u32 GetPrimitive() const;
		inline glm::u32 GetDrawType() const;

	private:
		bool Create() override;
		bool Release() override;

		glm::u32 mBuffers[COUNT];

		glm::u32 mNormalOffset;
		glm::u32 mTextureOffset;

		glm::u32 mVertexSize;
		glm::u32 mIndicesSize;
		glm::u32 mPrimitive;
		glm::u32 mDrawType;
	};
}

#endif
