#ifndef _MESH_H_
#define _MESH_H_

#include "BasicResource.h"

namespace ai
{
	class ENGINE_API Mesh : public BasicResource
	{
	public:
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

		Mesh(u32 id);
		Mesh(u32 id, const std::string& file);
		~Mesh();

		void BindVbo() const;
		void BindIbo() const;

		bool ReadDataFromFile();
		bool CreateBuffers();

		void UploadData(const f32* vertices, const u16* indices);
		void UploadAttributes(const i32* attributes) const;

		inline u32 GetVertexSize() const;
		inline u32 GetIndicesSize() const;
		inline u32 GetPrimitive() const;

		void CalculateVertexSize();

		u32 mVertexSize;
		u32 IndicesSize;
		u32 mPrimitive;

	private:
		bool Create() override;
		bool Release() override;

		u32 mBuffers[COUNT];

		u32 mNormalOffset;
		u32 mTextureOffset;
	};
}

#endif
