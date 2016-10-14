#include "DirectionalLightNode.h"

namespace ai
{
	DirectionalLightNode::DirectionalLightNode(glm::u32 id)
		: LightNode(id, DIRECTIONAL_LIGHT)
	{
	}

	DirectionalLightNode::DirectionalLightNode(glm::u32 id, const glm::vec3& direction)
		: LightNode(id, DIRECTIONAL_LIGHT)
		, mDirection(direction)
	{
	}

	DirectionalLightNode::DirectionalLightNode(glm::u32 id, const glm::vec3& direction, const glm::vec3& diffuse)
		: LightNode(id, DIRECTIONAL_LIGHT, diffuse)
		, mDirection(direction)
	{
	}

	DirectionalLightNode::DirectionalLightNode(glm::u32 id, const glm::vec3& direction, const glm::vec3& diffuse, const glm::vec3& specular)
		: LightNode(id, DIRECTIONAL_LIGHT, diffuse, specular)
		, mDirection(direction)
	{
	}

	DirectionalLightNode::~DirectionalLightNode()
	{
	}

	void DirectionalLightNode::setDirection(const glm::vec3& direction)
	{
		mDirection = direction;
	}

	const glm::vec3& DirectionalLightNode::getDirection() const
	{
		return mDirection;
	}
}
