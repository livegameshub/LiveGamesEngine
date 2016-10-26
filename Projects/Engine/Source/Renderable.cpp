#include "Renderable.h"
#include "Resources.h"
#include "Mesh.h"
#include "Material.h"

namespace lg
{
	Renderable::Renderable(glm::u32 id)
		: Node(id, RENDERABLE_NODE)
		, mMaterial(nullptr)
		, mMesh(nullptr)
		, mIsVisible(true)
	{
	}

	Renderable::Renderable(glm::u32 id, glm::i32 type)
		: Node(id, type)
		, mMaterial(nullptr)
		, mMesh(nullptr)
		, mIsVisible(true)
	{
	}

	Renderable::~Renderable()
	{
	}

	void Renderable::release()
	{
		Node::release();

		assert(mMesh != nullptr);
		assert(mMaterial != nullptr);

		Resources::getInstance().unload(mMesh);
		Resources::getInstance().unload(mMaterial);
	}

	void Renderable::setMesh(Mesh* mesh)
	{
		assert(mesh != nullptr);

		if (mMesh)
		{
			Resources::getInstance().unload(mMesh);
		}

		mMesh = mesh;

		Resources::getInstance().load(mMesh);
	}

	void Renderable::setMaterial(Material* material)
	{
		assert(material != nullptr);

		if (mMaterial)
		{
			Resources::getInstance().unload(mMaterial);
		}

		mMaterial = material;

		Resources::getInstance().load(mMaterial);
	}

	Material* Renderable::getMaterial() const
	{
		return mMaterial;
	}

	Mesh* Renderable::getMesh() const
	{
		return mMesh;
	}

	void Renderable::setVisible(bool value)
	{
		mIsVisible = value;
	}

	bool Renderable::isVisible() const
	{
		return mIsVisible;
	}
}
