#ifndef _SPRITE_MATERIAL_H_
#define _SPRITE_MATERIAL_H_

#include "Material.h"

namespace lg
{
	class Texture;

	class ENGINE_API SpriteMaterial : public Material
	{
	public:
		SpriteMaterial(glm::u32 id, const Flag& flag);
		SpriteMaterial(glm::u32 id, const glm::vec3& diffuse);
		SpriteMaterial(glm::u32 id, const glm::vec3& diffuse, const Flag& flag);

		virtual ~SpriteMaterial();

		void setDiffuseTexture(Texture* texture);
		Texture* getDiffuseTexture() const;

	protected:
		virtual bool create();
		virtual bool release();

	private:
		Texture* mDiffuseTexture;
	};
}

#endif // _SPRITE_MATERIAL_H_
