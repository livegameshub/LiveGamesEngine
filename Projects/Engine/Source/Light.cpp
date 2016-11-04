#include "Light.h"

namespace lg
{
	Light::Light(u32 id, i32 type)
		: Node(id, type)
		, mSpecularColor(LIGHT_DEFAULT_SPECULAR_COLOR)
		, mDiffuseColor(LIGHT_DEFAULT_DIFFUSE_COLOR)
	{
	}

	Light::~Light()
	{
	}

	void Light::setDiffuseColor(const vec3& color)
	{
		mDiffuseColor = color;
	}

	void Light::setSpecularColor(const vec3& color)
	{
		mSpecularColor = color;
	}

	const vec3& Light::getDiffuseColor() const
	{
		return mDiffuseColor;
	}

	const vec3& Light::getSpecularColor() const
	{
		return mSpecularColor;
	}
}
