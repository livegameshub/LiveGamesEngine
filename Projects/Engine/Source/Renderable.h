#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include "Node.h"

namespace lg
{
	class Mesh;
	class Material;

	class ENGINE_API Renderable : public Node
	{
	public:
		Renderable(glm::u32 id);
		Renderable(glm::u32 id, glm::i32 type);

		virtual ~Renderable();

		virtual void release();

		void setMaterial(Material* material);
		void setMesh(Mesh* mesh);

		Material* getMaterial() const;
		Mesh* getMesh() const;

		void setVisible(bool value);
		bool isVisible() const;

	private:
		Material* mMaterial;
		Mesh* mMesh;

		bool mIsVisible;
	};
}

#endif // _RENDERABLE_H_
