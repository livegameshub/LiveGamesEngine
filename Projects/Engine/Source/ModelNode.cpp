#include "ModelNode.h"
#include "ResourceManager.h"

namespace ai
{
	ModelNode::ModelNode(glm::u32 id) 
		: BasicNode(id, MODEL_NODE)
		, mMaterial(nullptr)
		, mMesh(nullptr)
		, mIsVisible(true)
	{
	}

	ModelNode::~ModelNode()
	{
	}

	void ModelNode::Release()
	{
		BasicNode::Release();

		assert(mMesh != nullptr);
		assert(mMaterial != nullptr);

		ResourceManager::getInstance().addPendingItem(mMesh, false);
		ResourceManager::getInstance().addPendingItem(mMaterial, false);
	}

	void ModelNode::SetMesh(MeshResource* mesh)
	{
		assert(mesh != nullptr);

		if (mMesh)
		{
			ResourceManager::getInstance().addPendingItem(mMesh, false);
		}

		mMesh = mesh;

		ResourceManager::getInstance().addPendingItem(mMesh, true);
	}

	void ModelNode::SetMaterial(MaterialResource* material)
	{
		assert(material != nullptr);

		if (mMaterial)
		{
			ResourceManager::getInstance().addPendingItem(mMaterial, false);
		}

		mMaterial = material;

		ResourceManager::getInstance().addPendingItem(mMaterial, true);
	}

	MaterialResource* ModelNode::GetMaterial() const
	{
		return mMaterial;
	}

	MeshResource* ModelNode::GetMesh() const
	{
		return mMesh;
	}

	void ModelNode::SetVisible(bool value)
	{
		mIsVisible = value;
	}

	bool ModelNode::IsVisible() const
	{
		return mIsVisible;
	}
}
