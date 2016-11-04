#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Node.h"

/* default values */
#define LIGHT_DEFAULT_DIFFUSE_COLOR vec3(1.0f)
#define LIGHT_DEFAULT_SPECULAR_COLOR vec3(0.5f)

namespace lg
{
	class ENGINE_API Light : public Node
	{
	public:
		Light(u32 id, i32 type);

		virtual ~Light();
		
		void setDiffuseColor(const vec3& color);
		void setSpecularColor(const vec3& color);
		
		const vec3& getDiffuseColor() const;
		const vec3& getSpecularColor() const;

	protected:
		vec3 mSpecularColor;
		vec3 mDiffuseColor;
	};
}

#endif // _LIGHT_H_
