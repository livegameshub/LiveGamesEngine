#include "MeshRenderer.h"
#include "Resources.h"
#include "Mesh.h"
#include "Material.h"

namespace lg
{
	MeshRenderer::MeshRenderer()
		: mMaterial(nullptr)
		, mMesh(nullptr)
		, mIsEnabled(true)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::release()
	{
		assert(mMaterial != nullptr);
		assert(mMesh != nullptr);

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

	void MeshRenderer::setEnabled(bool value)
	{
		mIsEnabled = value;
	}

	bool MeshRenderer::isEnabled() const
	{
		return mIsEnabled;
	}

	MeshRenderer* MeshRenderer::create(Material* material, Mesh* mesh)
	{
		MeshRenderer* renderer = new MeshRenderer();
		renderer->setMesh(mesh);
		renderer->setMaterial(material);

		return renderer;
	}
}
