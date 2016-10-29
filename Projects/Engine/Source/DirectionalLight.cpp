#include "DirectionalLight.h"

namespace lg
{
	DirectionalLight::DirectionalLight(glm::u32 id, const glm::vec3& direction)
		: Light(id, DIRECTIONAL_LIGHT)
		, mDirection(direction)
	{
	}

	DirectionalLight::DirectionalLight(glm::u32 id, const glm::vec3& direction, const glm::vec3& diffuse, const glm::vec3& specular)
		: Light(id, DIRECTIONAL_LIGHT, diffuse, specular)
		, mDirection(direction)
	{
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	void DirectionalLight::setDirection(const glm::vec3& direction)
	{
		mDirection = direction;
	}

	const glm::vec3& DirectionalLight::getDirection() const
	{
		return mDirection;
	}
}
