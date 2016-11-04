#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Resource.h"
#include "MaterialUtil.h"

namespace lg
{
	class Texture;
	class Program;

	class ENGINE_API Material : public Resource
	{
	public:
		enum MaterialProperties : u32
		{
			IS_LIGHTED = 1,
			IS_TEXTURED = 2,
			IS_SHINY = 4
		};

		Material(u32 id, const Flag& flag = 0);
		Material(u32 id, const vec3& diffuse, const Flag& flag = 0);

		virtual ~Material();

		bool IsLighted() const;
		bool IsTextured() const;
		bool IsShiny() const;

		void setProgram(Program* program);
		void setDiffuseTexture(Texture* texture);
		void setDiffuseColor(const vec3& color);
	
		Program* getProgram() const;
		Texture* getDiffuseTexture() const;
		const vec3& getDiffuseColor() const;

		virtual void uploadUniforms() const;

	protected:
		virtual bool create();
		virtual bool release();

		Texture* mDiffuseTexture;
		Program* mProgram;

	private:
		vec3 mDiffuseColor;
	};
}

#endif // _MATERIAL_H_
