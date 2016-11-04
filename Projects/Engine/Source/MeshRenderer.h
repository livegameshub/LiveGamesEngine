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
		MeshRenderer();
		~MeshRenderer();

		void release();

		void setMaterial(Material* material);
		void setMesh(Mesh* mesh);

		Material* getMaterial() const;
		Mesh* getMesh() const;

		void setEnabled(bool value);
		bool isEnabled() const;

		static MeshRenderer* create(Material* material, Mesh* mesh);

	private:
		Material* mMaterial;
		Mesh* mMesh;

		bool mIsEnabled;
	};
}

#endif // _MESH_RENDERER_H_
