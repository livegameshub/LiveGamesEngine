#include "Light.h"

namespace lg
{
	Light::Light(glm::u32 id, glm::i32 type)
		: Node(id, LIGHT)
		, mSpecularColor(LIGHT_DEFAULT_SPECULAR_COLOR)
		, mDiffuseColor(LIGHT_DEFAULT_DIFFUSE_COLOR)
		, mLightType(type)
	{
	}

	Light::Light(glm::u32 id, glm::i32 type, const glm::vec3& diffuse, const glm::vec3& specular)
		: Node(id, LIGHT)
		, mSpecularColor(specular)
		, mDiffuseColor(diffuse)
		, mLightType(type)
	{
	}

	Light::~Light()
	{
	}

	void Light::setLightType(glm::i32 type)
	{
		mLightType = type;
	}

	void Light::setDiffuseColor(const glm::vec3& color)
	{
		mDiffuseColor = color;
	}

	void Light::setSpecularColor(const glm::vec3& color)
	{
		mSpecularColor = color;
	}

	const glm::vec3& Light::getDiffuseColor() const
	{
		return mDiffuseColor;
	}

	const glm::vec3& Light::getSpecularColor() const
	{
		return mSpecularColor;
	}

	glm::i32 Light::getLightType() const
	{
		return mLightType;
	}
}
