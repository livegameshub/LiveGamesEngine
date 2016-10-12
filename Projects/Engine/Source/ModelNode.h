#ifndef _MODEL_NODE_H_
#define _MODEL_NODE_H_

#include "BasicNode.h"

namespace ai
{
	class MeshResource;
	class MaterialResource;

	class ENGINE_API ModelNode : public BasicNode
	{
	public:
		ModelNode(glm::u32 id);
		~ModelNode();

		void release() override;
		void setMaterial(MaterialResource* material);
		void setMesh(MeshResource* mesh);

		MaterialResource* getMaterial() const;
		MeshResource* getMesh() const;

		void setVisible(bool value);
		bool isVisible() const;

	private:
		MaterialResource* mMaterial;
		MeshResource* mMesh;

		bool mIsVisible;
	};
}

#endif // _MODEL_NODE_H_
