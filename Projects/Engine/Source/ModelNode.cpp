#include "ModelNode.h"
#include "ResourceManager.h"

namespace ai
{
	ModelNode::ModelNode(glm::u32 id) 
		: BasicNode(id, MODEL_NODE)
		, mMesh(nullptr)
	{
	}

	ModelNode::~ModelNode()
	{
	}

	void ModelNode::Release()
	{
		BasicNode::Release();

		assert(mMesh != nullptr);

		mMesh->Unload();
	}

	void ModelNode::SetMesh(MeshResource* mesh)
	{
		assert(mesh != nullptr);

		if (mMesh)
		{
			ResourceManager::addPendingItem(mMesh, false);
		}

		mMesh = mesh;

		ResourceManager::addPendingItem(mMesh, true);
	}

	MeshResource* ModelNode::GetMesh() const
	{
		return mMesh;
	}
}
