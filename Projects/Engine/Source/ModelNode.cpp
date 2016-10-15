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

		ResourceManager::getInstance().unload(mMesh);
		ResourceManager::getInstance().unload(mMaterial);
	}

	void ModelNode::setMesh(MeshResource* mesh)
	{
		assert(mesh != nullptr);

		if (mMesh)
		{
			ResourceManager::getInstance().unload(mMesh);
		}

		mMesh = mesh;

		ResourceManager::getInstance().load(mMesh);
	}

	void ModelNode::setMaterial(BasicMaterialResource* material)
	{
		assert(material != nullptr);

		if (mMaterial)
		{
			ResourceManager::getInstance().unload(mMaterial);
		}

		mMaterial = material;

		ResourceManager::getInstance().load(mMaterial);
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
