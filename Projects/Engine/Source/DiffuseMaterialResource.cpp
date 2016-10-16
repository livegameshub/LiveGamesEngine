#include "DiffuseMaterialResource.h"

namespace ai
{
	DiffuseMaterialResource::DiffuseMaterialResource(glm::u32 id)
		: BasicMaterialResource(id)
		, mSpecularColor(1.0f)
		, mSpecularShininess(0.0f)
	{
	}

	DiffuseMaterialResource::DiffuseMaterialResource(glm::u32 id, const glm::vec3& diffuse, const glm::vec3& specular, glm::f32 shininess, const Flag& flag)
		: BasicMaterialResource(id, diffuse, flag)
		, mSpecularColor(specular)
		, mSpecularShininess(shininess)
	{
	}

	DiffuseMaterialResource::~DiffuseMaterialResource()
	{
	}

	void DiffuseMaterialResource::uploadUniforms() const
	{
		BasicMaterialResource::uploadUniforms();
	}

	void DiffuseMaterialResource::setSpecularColor(const glm::vec3& color)
	{
		mSpecularColor = color;
	}

	void DiffuseMaterialResource::setSpecularShininess(glm::f32 value)
	{
		mSpecularShininess = value;
	}

	const glm::vec3& DiffuseMaterialResource::getSpecularColor() const
	{
		return mSpecularColor;
	}

	glm::f32 DiffuseMaterialResource::getSpecularShininess() const
	{
		return mSpecularShininess;
	}

	bool DiffuseMaterialResource::create()
	{
		return BasicMaterialResource::create();
	}
}
