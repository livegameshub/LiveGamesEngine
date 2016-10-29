#include "MeshRenderer.h"
#include "Resources.h"
#include "Mesh.h"
#include "Material.h"

namespace lg
{
	MeshRenderer::MeshRenderer(glm::u32 id)
		: Node(id, RENDERABLE_NODE, IS_VISIBLE)
		, mMaterial(nullptr)
		, mMesh(nullptr)
	{
	}

	MeshRenderer::MeshRenderer(glm::u32 id, glm::i32 type)
		: Node(id, type, IS_VISIBLE)
		, mMaterial(nullptr)
		, mMesh(nullptr)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::release()
	{
		Node::release();

		assert(mMesh != nullptr);
		assert(mMaterial != nullptr);

		Resources::getInstance().unload(mMesh);
		Resources::getInstance().unload(mMaterial);
	}

	void MeshRenderer::setMesh(Mesh* mesh)
	{
		assert(mesh != nullptr);

		if (mMesh)
		{
			Resources::getInstance().unload(mMesh);
		}

		mMesh = mesh;

		Resources::getInstance().load(mMesh);
	}

	void MeshRenderer::setMaterial(Material* material)
	{
		assert(material != nullptr);

		if (mMaterial)
		{
			Resources::getInstance().unload(mMaterial);
		}

		mMaterial = material;

		Resources::getInstance().load(mMaterial);
	}

	Material* MeshRenderer::getMaterial() const
	{
		return mMaterial;
	}

	Mesh* MeshRenderer::getMesh() const
	{
		return mMesh;
	}
}
