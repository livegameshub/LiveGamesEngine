#include "Light.h"

namespace ai
{
	Light::Light(glm::u32 id, glm::i32 type)
		: Node(id, LIGHT_NODE)
		, mSpecularColor(1.0f)
		, mDiffuseColor(1.0f)
		, mLightType(type)
	{
	}

	Light::Light(glm::u32 id, glm::i32 type, const glm::vec3& diffuse)
		: Node(id, LIGHT_NODE)
		, mSpecularColor(1.0f)
		, mDiffuseColor(diffuse)
		, mLightType(type)
	{
	}

	Light::Light(glm::u32 id, glm::i32 type, const glm::vec3& diffuse, const glm::vec3& specular)
		: Node(id, LIGHT_NODE)
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
