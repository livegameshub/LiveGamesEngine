#include "ModelNode.h"
#include "ResourceManager.h"
#include "MeshResource.h"
#include "BasicMaterialResource.h"

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

	void ModelNode::release()
	{
		BasicNode::release();

		assert(mMesh != nullptr);
		assert(mMaterial != nullptr);

		ResourceManager::getInstance().addItemToUnload(mMesh);
		ResourceManager::getInstance().addItemToUnload(mMaterial);
	}

	void ModelNode::setMesh(MeshResource* mesh)
	{
		assert(mesh != nullptr);

		if (mMesh)
		{
			ResourceManager::getInstance().addItemToUnload(mMesh);
		}

		mMesh = mesh;

		ResourceManager::getInstance().addItemToLoad(mMesh);
	}

	void ModelNode::setMaterial(BasicMaterialResource* material)
	{
		assert(material != nullptr);

		if (mMaterial)
		{
			ResourceManager::getInstance().addItemToUnload(mMaterial);
		}

		mMaterial = material;

		ResourceManager::getInstance().addItemToLoad(mMaterial);
	}

	BasicMaterialResource* ModelNode::getMaterial() const
	{
		return mMaterial;
	}

	MeshResource* ModelNode::getMesh() const
	{
		return mMesh;
	}

	void ModelNode::setVisible(bool value)
	{
		mIsVisible = value;
	}

	bool ModelNode::isVisible() const
	{
		return mIsVisible;
	}
}
