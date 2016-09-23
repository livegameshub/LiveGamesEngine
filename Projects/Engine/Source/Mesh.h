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
		const u32 LINES_MESH = GL_LINES;
		const u32 POINTS_MESH = GL_POINTS;
		const u32 TRIANGLES_MESH = GL_TRIANGLES;

		const u32 STATIC_MESH_DRAW = GL_STATIC_DRAW;
		const u32 DYNAMIC_MESH_DRAW = GL_DYNAMIC_DRAW;

		enum MeshBuffer : u32
		{
			VBO_BUFFER,
			IBO_BUFFER,
			COUNT
		};

		enum MeshFlag : u32
		{
			MESH_POSITION_FLAG = 1,
			MESH_NORMAL_FLAG = 2,
			MESH_TEXTURE_FLAG = 4
		};

		Mesh(u32 id, const std::string& file);
		Mesh(u32 id, u32 primitive, u32 drawType, const Flag& flag);
		~Mesh();

		void Draw() const;  

		void BindVbo() const;
		void BindIbo() const;

		bool CreateBuffers();
		bool ReadDataFromFile();

		void CalculateVertexSize();
		
		void UploadData(const MeshData& meshData);
		void UploadData(const std::vector<f32>& vertices, const std::vector<u16>& indices);
		void UploadAttributes(const i32* attributes) const;

		inline u32 GetVertexSize() const;
		inline u32 GetIndicesSize() const;
		inline u32 GetPrimitive() const;
		inline u32 GetDrawType() const;

	private:
		bool Create() override;
		bool Release() override;

		u32 mBuffers[COUNT];

		u32 mNormalOffset;
		u32 mTextureOffset;

		u32 mVertexSize;
		u32 mIndicesSize;
		u32 mPrimitive;
		u32 mDrawType;
	};
}

#endif
