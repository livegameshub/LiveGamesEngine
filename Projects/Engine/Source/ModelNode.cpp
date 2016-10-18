#include "ModelNode.h"
#include "Resources.h"
#include "MeshResource.h"
#include "BasicMaterial.h"

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

		Resources::getInstance().unload(mMesh);
		Resources::getInstance().unload(mMaterial);
	}

	void ModelNode::setMesh(MeshResource* mesh)
	{
		assert(mesh != nullptr);

		if (mMesh)
		{
			Resources::getInstance().unload(mMesh);
		}

		mMesh = mesh;

		Resources::getInstance().load(mMesh);
	}

	void ModelNode::setMaterial(BasicMaterial* material)
	{
		assert(material != nullptr);

		if (mMaterial)
		{
			Resources::getInstance().unload(mMaterial);
		}

		mMaterial = material;

		Resources::getInstance().load(mMaterial);
	}

	BasicMaterial* ModelNode::getMaterial() const
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
