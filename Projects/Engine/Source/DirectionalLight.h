#ifndef _DIRECTIONAL_LIGHT_H_
#define _DIRECTIONAL_LIGHT_H_

#include "Light.h"

namespace lg
{
	class ENGINE_API DirectionalLight : public Light
	{
	public:
		DirectionalLight(glm::u32 id);
		DirectionalLight(glm::u32 id, const glm::vec3& direction);
		DirectionalLight(glm::u32 id, const glm::vec3& direction, const glm::vec3& diffuse);
		DirectionalLight(glm::u32 id, const glm::vec3& direction, const glm::vec3& diffuse, const glm::vec3& specular);

		~DirectionalLight();

		void setDirection(const glm::vec3& direction);
		const glm::vec3& getDirection() const;

	private:
		glm::vec3 mDirection;
	};
}

#endif // _DIRECTIONAL_LIGHT_H_
