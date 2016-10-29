#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Node.h"

/* default values */
#define LIGHT_DEFAULT_DIFFUSE_COLOR glm::vec3(1.0f)
#define LIGHT_DEFAULT_SPECULAR_COLOR glm::vec3(0.5f)

namespace lg
{
	class ENGINE_API Light : public Node
	{
	public:
		enum LightType : glm::u32
		{
			DIRECTIONAL_LIGHT,
			POINT_LIGHT,
			SPOT_LIGHT
		};

		Light(glm::u32 id, glm::i32 type);
		Light(glm::u32 id, glm::i32 type, const glm::vec3& diffuse, const glm::vec3& specular);

		virtual ~Light();
		
		void setDiffuseColor(const glm::vec3& color);
		void setSpecularColor(const glm::vec3& color);
		void setLightType(glm::i32 type);
		
		const glm::vec3& getDiffuseColor() const;
		const glm::vec3& getSpecularColor() const;
		glm::i32 getLightType() const;

	private:
		glm::vec3 mSpecularColor;
		glm::vec3 mDiffuseColor;

		glm::i32 mLightType;
	};
}

#endif // _LIGHT_H_
