#ifndef _DIFFUSE_MATERIAL_H_
#define _DIFFUSE_MATERIAL_H_

#include "Material.h"

namespace lg
{
	class DirectionalLight;

	class ENGINE_API DiffuseMaterial : public Material
	{
	public:
		DiffuseMaterial(glm::u32 id, const Flag& flag = 0);
		DiffuseMaterial(glm::u32 id, const glm::vec3& diffuse, const Flag& flag);

		~DiffuseMaterial();
		
		void setSpecularColor(const glm::vec3& color);
		void setSpecularShininess(glm::f32 value);

		const glm::vec3& getSpecularColor() const;
		glm::f32 getSpecularShininess() const;

		void uploadUniforms(DirectionalLight* light) const;
		void uploadUniforms() const override;

	private:
		bool create() override;
		bool release() override;

		glm::vec3 mSpecularColor;
		glm::f32 mSpecularShininess;
	};
}

#endif // _DIFFUSE_MATERIAL_H_