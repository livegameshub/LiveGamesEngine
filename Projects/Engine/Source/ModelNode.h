#ifndef _MODEL_NODE_H_
#define _MODEL_NODE_H_

#include "BasicNode.h"

namespace ai
{
	class MeshResource;
	class BasicMaterial;

	class ENGINE_API ModelNode : public BasicNode
	{
	public:
		ModelNode(glm::u32 id);
		~ModelNode();

		void release() override;
		void setMaterial(BasicMaterial* material);
		void setMesh(MeshResource* mesh);

		BasicMaterial* getMaterial() const;
		MeshResource* getMesh() const;

		void setVisible(bool value);
		bool isVisible() const;

	private:
		BasicMaterial* mMaterial;
		MeshResource* mMesh;

		bool mIsVisible;
	};
}

#endif // _MODEL_NODE_H_
