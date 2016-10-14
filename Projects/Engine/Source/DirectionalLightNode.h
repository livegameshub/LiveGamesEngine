#ifndef _DIRECTIONAL_LIGHT_NODE_H_
#define _DIRECTIONAL_LIGHT_NODE_H_

#include "LightNode.h"

namespace ai
{
	class ENGINE_API DirectionalLightNode : public LightNode
	{
	public:
		DirectionalLightNode(glm::u32 id);
		DirectionalLightNode(glm::u32 id, const glm::vec3& direction);
		DirectionalLightNode(glm::u32 id, const glm::vec3& direction, const glm::vec3& diffuse);
		DirectionalLightNode(glm::u32 id, const glm::vec3& direction, const glm::vec3& diffuse, const glm::vec3& specular);

		~DirectionalLightNode();

		void setDirection(const glm::vec3& direction);
		const glm::vec3& getDirection() const;

	private:
		glm::vec3 mDirection;
	};
}

#endif
