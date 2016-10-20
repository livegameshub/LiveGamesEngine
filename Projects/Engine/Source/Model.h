#ifndef _MODEL_H_
#define _MODEL_H_

#include "Node.h"

namespace ai
{
	class Mesh;
	class Material;

	class ENGINE_API Model : public Node
	{
	public:
		Model(glm::u32 id);
		~Model();

		void release() override;
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

#endif // _MODEL_H_
