#ifndef _LIGHT_NODE_H_
#define _LIGHT_NODE_H_

#include "BasicNode.h"

namespace ai
{
	class ENGINE_API LightNode : public BasicNode
	{
	public:
		enum LightType : glm::u32
		{
			DIRECTIONAL_LIGHT,
			POINT_LIGHT,
			SPOT_LIGHT
		};

		LightNode(glm::u32 id, glm::i32 type);
		LightNode(glm::u32 id, glm::i32 type, const glm::vec3& diffuse);
		LightNode(glm::u32 id, glm::i32 type, const glm::vec3& diffuse, const glm::vec3& specular);

		virtual ~LightNode();
		
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

#endif
