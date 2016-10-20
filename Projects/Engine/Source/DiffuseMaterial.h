#ifndef _DIFFUSE_MATERIAL_H_
#define _DIFFUSE_MATERIAL_H_

#include "Material.h"

namespace ai
{
	class DirectionalLight;

	class ENGINE_API DiffuseMaterial : public Material
	{
	public:
		DiffuseMaterial(glm::u32 id);
		DiffuseMaterial(glm::u32 id, const glm::vec3& diffuse, const glm::vec3& specular, glm::f32 shininess, const Flag& flag);

		~DiffuseMaterial();

		void uploadUniforms() const override;
		void uploadUniforms(DirectionalLight* light) const;

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

#endif // _DIFFUSE_MATERIAL_H_