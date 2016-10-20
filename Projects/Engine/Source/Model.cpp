#include "Model.h"
#include "Resources.h"
#include "Mesh.h"
#include "Material.h"

namespace ai
{
	Model::Model(glm::u32 id) 
		: Node(id, MODEL_NODE)
		, mMaterial(nullptr)
		, mMesh(nullptr)
		, mIsVisible(true)
	{
	}

	Model::~Model()
	{
	}

	void Model::release()
	{
		Node::release();

		assert(mMesh != nullptr);
		assert(mMaterial != nullptr);

		Resources::getInstance().unload(mMesh);
		Resources::getInstance().unload(mMaterial);
	}

	void Model::setMesh(Mesh* mesh)
	{
		assert(mesh != nullptr);

		if (mMesh)
		{
			Resources::getInstance().unload(mMesh);
		}

		mMesh = mesh;

		Resources::getInstance().load(mMesh);
	}

	void Model::setMaterial(Material* material)
	{
		assert(material != nullptr);

		if (mMaterial)
		{
			Resources::getInstance().unload(mMaterial);
		}

		mMaterial = material;

		Resources::getInstance().load(mMaterial);
	}

	Material* Model::getMaterial() const
	{
		return mMaterial;
	}

	Mesh* Model::getMesh() const
	{
		return mMesh;
	}

	void Model::setVisible(bool value)
	{
		mIsVisible = value;
	}

	bool Model::isVisible() const
	{
		return mIsVisible;
	}
}
