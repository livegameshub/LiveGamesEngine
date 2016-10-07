#ifndef _MODEL_NODE_H_
#define _MODEL_NODE_H_

#include "BasicNode.h"
#include "MeshResource.h"
#include "MaterialResource.h"

namespace ai
{
	class ENGINE_API ModelNode : public BasicNode
	{
	public:
		ModelNode(glm::u32 id);
		~ModelNode();

		void Release() override;
		void SetMaterial(MaterialResource* material);
		void SetMesh(MeshResource* mesh);

		MaterialResource* GetMaterial() const;
		MeshResource* GetMesh() const;

		void SetVisible(bool value);
		bool IsVisible() const;

	private:
		MaterialResource* mMaterial;
		MeshResource* mMesh;

		bool mIsVisible;
	};
}

#endif
