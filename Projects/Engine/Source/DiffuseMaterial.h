#ifndef _DIFFUSE_MATERIAL_H_
#define _DIFFUSE_MATERIAL_H_

#include "Material.h"

namespace lg
{
	class DirectionalLight;

	class ENGINE_API DiffuseMaterial : public Material
	{
	public:
		DiffuseMaterial(u32 id, const Flag& flag = 0);
		DiffuseMaterial(u32 id, const vec3& diffuse, const Flag& flag);

		~DiffuseMaterial();
		
		void setSpecularColor(const vec3& color);
		void setSpecularShininess(f32 value);

		const vec3& getSpecularColor() const;
		f32 getSpecularShininess() const;

		void uploadUniforms(DirectionalLight* light) const;
		void uploadUniforms() const override;

	private:
		bool create() override;
		bool release() override;

		vec3 mSpecularColor;
		f32 mSpecularShininess;
	};
}

#endif // _DIFFUSE_MATERIAL_H_