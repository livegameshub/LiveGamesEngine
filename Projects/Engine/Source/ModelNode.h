#ifndef _MODEL_NODE_H_
#define _MODEL_NODE_H_

#include "BasicNode.h"
#include "MeshResource.h"

namespace ai
{
	class ENGINE_API ModelNode : public BasicNode
	{
	public:
		ModelNode(glm::u32 id);
		~ModelNode();

		void Release() override;
		void SetMesh(MeshResource* mesh);

		MeshResource* GetMesh() const;

	private:
		MeshResource* mMesh;
	};
}

#endif
