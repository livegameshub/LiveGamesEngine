#ifndef _MESH_RENDERER_H_
#define _MESH_RENDERER_H_

#include "EngineUtil.h"

namespace lg
{
	class Mesh;
	class Material;

	class ENGINE_API MeshRenderer
	{
	public:
		MeshRenderer(Material* material, Mesh* mesh);
		~MeshRenderer();

		void release() const;

		void setMaterial(Material* material);
		void setMesh(Mesh* mesh);

		Material* getMaterial() const;
		Mesh* getMesh() const;

		void setEnabled(bool value);
		bool isEnabled() const;

	private:
		Material* mMaterial;
		Mesh* mMesh;

		bool mIsEnabled;
	};
}

#endif // _MESH_RENDERER_H_
