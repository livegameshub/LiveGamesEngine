#include "SpriteMaterial.h"
#include "Resources.h"
#include "Texture.h"

namespace lg
{
	SpriteMaterial::SpriteMaterial(glm::u32 id, const Flag& flag)
		: Material(id, flag)
		, mDiffuseTexture(nullptr)
	{
	}

	SpriteMaterial::SpriteMaterial(glm::u32 id, const glm::vec3& diffuse)
		: Material(id, diffuse)
		, mDiffuseTexture(nullptr)
	{
	}

	SpriteMaterial::SpriteMaterial(glm::u32 id, const glm::vec3& diffuse, const Flag& flag)
		: Material(id, diffuse, flag)
		, mDiffuseTexture(nullptr)
	{
	}

	SpriteMaterial::~SpriteMaterial()
	{
	}

	void SpriteMaterial::setDiffuseTexture(Texture* texture)
	{
		assert(texture != nullptr);

		if (mDiffuseTexture)
		{
			Resources::getInstance().unload(mDiffuseTexture);
		}

		mDiffuseTexture = texture;

		Resources::getInstance().load(mDiffuseTexture);
	}

	Texture* SpriteMaterial::getDiffuseTexture() const
	{
		return mDiffuseTexture;
	}

	bool SpriteMaterial::create()
	{
		return Material::create();
	}

	bool SpriteMaterial::release()
	{
		if (mDiffuseTexture)
		{
			Resources::getInstance().unload(mDiffuseTexture);
		}

		return Material::release();
	}
}
