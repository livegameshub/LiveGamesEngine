#ifndef _DIRECTIONAL_LIGHT_H_
#define _DIRECTIONAL_LIGHT_H_

#include "Light.h"

namespace lg
{
	class ENGINE_API DirectionalLight : public Light
	{
	public:
		DirectionalLight(u32 id, i32 type);
		~DirectionalLight();

		void setDirection(const vec3& direction);
		const vec3& getDirection() const;

	private:
		vec3 mDirection;
	};
}

#endif // _DIRECTIONAL_LIGHT_H_
