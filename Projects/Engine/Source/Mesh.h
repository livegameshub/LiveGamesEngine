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
		static const u32 LINES = GL_LINES;
		static const u32 POINTS = GL_POINTS;
		static const u32 TRIANGLES = GL_TRIANGLES;

		static const u32 STATIC_DRAW = GL_STATIC_DRAW;
		static const u32 DYNAMIC_DRAW = GL_DYNAMIC_DRAW;

		enum MeshBuffer : u32
		{
			VBO_BUFFER,
			IBO_BUFFER,
			COUNT
		};

		enum MeshFlag : u32
		{
			USE_NORMALS = 1,
			USE_TEXTURES = 2,
			REMOVE_DATA = 4
		};

		Mesh(u32 id, const string& file);
		Mesh(u32 id, u32 primitive, u32 drawType, const Flag& flag);

		~Mesh();

		void draw() const;  
		void bindVbo() const;
		void bindIbo() const;

		bool createBuffers();
		bool readDataFromFile();
		void calculateVertexSize();

		void uploadData(const MeshData& meshData);
		void uploadAttributes(const i32* attributes) const;

		u32 calculateVerticesArraySize(u32 size) const;

		u32 getVertexSize() const;
		u32 getIndicesSize() const;
		u32 getPrimitive() const;
		u32 getDrawType() const;

		MeshData& getData();

	private:
		bool create() override;
		bool release() override;

		u32 mBuffers[COUNT];

		u32 mNormalOffset;
		u32 mTextureOffset;

		u32 mVertexSize;
		u32 mIndicesSize;
		u32 mPrimitive;
		u32 mDrawType;

		MeshData mData;
	};
}

#endif // _MESH_H_
