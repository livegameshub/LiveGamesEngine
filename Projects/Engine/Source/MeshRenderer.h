#ifndef _MESH_RENDERER_H_
#define _MESH_RENDERER_H_

#include "Node.h"

namespace lg
{
	class Mesh;
	class Material;

	class ENGINE_API MeshRenderer : public Node
	{
	public:
		MeshRenderer(glm::u32 id);
		MeshRenderer(glm::u32 id, glm::i32 type);

		virtual ~MeshRenderer();

		virtual void release();

		void setMaterial(Material* material);
		void setMesh(Mesh* mesh);

		Material* getMaterial() const;
		Mesh* getMesh() const;



	private:
		Material* mMaterial;
		Mesh* mMesh;
	};
}

#endif // _MESH_RENDERER_H_
