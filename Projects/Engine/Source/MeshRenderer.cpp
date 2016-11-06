#include "MeshRenderer.h"
#include "Resources.h"
#include "Mesh.h"
#include "Material.h"

namespace lg
{
	MeshRenderer::MeshRenderer(Material* material, Mesh* mesh)
		: mMaterial(nullptr)
		, mMesh(nullptr)
		, mIsEnabled(true)
	{
		setMaterial(material);
		setMesh(mesh);
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::release() const
	{
		assert(mMaterial != nullptr);
		assert(mMesh != nullptr);

		Resources::instance().unload(mMesh);
		Resources::instance().unload(mMaterial);
	}

	void MeshRenderer::setMesh(Mesh* mesh)
	{
		assert(mesh != nullptr);

		if (mMesh)
		{
			Resources::instance().unload(mMesh);
		}

		mMesh = mesh;

		Resources::instance().load(mMesh);
	}

	void MeshRenderer::setMaterial(Material* material)
	{
		assert(material != nullptr);

		if (mMaterial)
		{
			Resources::instance().unload(mMaterial);
		}

		mMaterial = material;

		Resources::instance().load(mMaterial);
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
}
