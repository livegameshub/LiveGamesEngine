#include "DirectionalLight.h"

namespace lg
{
	DirectionalLight::DirectionalLight(u32 id, i32 type)
		: Light(id, type)
	{
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	void DirectionalLight::setDirection(const vec3& direction)
	{
		mDirection = direction;
	}

	const vec3& DirectionalLight::getDirection() const
	{
		return mDirection;
	}
}
