#ifndef _DIFFUSE_MATERIAL_RESOURCE_H_
#define _DIFFUSE_MATERIAL_RESOURCE_H_

#include "BasicMaterialResource.h"

namespace ai
{
	class DirectionalLightNode;

	class ENGINE_API DiffuseMaterialResource : public BasicMaterialResource
	{
	public:
		DiffuseMaterialResource(glm::u32 id);
		DiffuseMaterialResource(glm::u32 id, const glm::vec3& diffuse, const glm::vec3& specular, glm::f32 shininess, const Flag& flag);

		~DiffuseMaterialResource();

		void uploadUniforms() const override;
		void uploadUniforms(DirectionalLightNode* light) const;

		void setSpecularColor(const glm::vec3& color);
		void setSpecularShininess(glm::f32 value);

		const glm::vec3& getSpecularColor() const;
		glm::f32 getSpecularShininess() const;

	private:
		bool create() override;

		glm::vec3 mSpecularColor;
		glm::f32 mSpecularShininess;
	};
}

#endif // _DIFFUSE_MATERIAL_RESOURCE_H_