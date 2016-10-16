#ifndef _BASIC_MATERIAL_RESOURCE_H_
#define _BASIC_MATERIAL_RESOURCE_H_

#include "BasicResource.h"

/* some useful constants */
const std::string UNIFORM_VIEW = "u_view";
const std::string UNIFORM_MODEL = "u_model";
const std::string UNIFORM_PROJECTION = "u_projection";
const std::string UNIFORM_MATERIAL_DIFFUSE = "u_material.diffuse";

namespace ai
{
	class ProgramResource;

	class ENGINE_API BasicMaterialResource : public BasicResource
	{
	public:
		enum MaterialProperties : glm::u32
		{
			IS_LIGTHED = 1,
			IS_TEXTURED = 2,
			IS_SHINY = 4
		};

		BasicMaterialResource(glm::u32 id);
		BasicMaterialResource(glm::u32 id, const Flag& flag);
		BasicMaterialResource(glm::u32 id, const glm::vec3& diffuse, const Flag& flag);

		virtual ~BasicMaterialResource();

		virtual void uploadUniforms() const;

		void setProgram(ProgramResource* program);
		void setDiffuseColor(const glm::vec3& color);
	
		ProgramResource* getProgram() const;
		const glm::vec3& getDiffuseColor() const;

	protected:
		virtual bool create();

	private:
		bool release() override;

		ProgramResource* mProgram;

		glm::vec3 mDiffuseColor;
	};
}

#endif // _BASIC_MATERIAL_RESOURCE_H_
