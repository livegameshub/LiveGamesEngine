#ifndef _MATERIAL_RESOURCE_H_
#define _MATERIAL_RESOURCE_H_

#include "BasicResource.h"

/* some useful constants */
const std::string UNIFORM_VIEW = "u_view";
const std::string UNIFORM_MODEL = "u_model";
const std::string UNIFORM_PROJECTION = "u_projection";
const std::string UNIFORM_MATERIAL_DIFFUSE = "u_material.diffuse";

namespace ai
{
	class ProgramResource;

	class ENGINE_API MaterialResource : public BasicResource
	{
	public:
		enum MaterialProperties : glm::u32
		{
			IS_LIGTHED = 1,
			IS_TEXTURED = 2,
			IS_SHINY = 4
		};

		MaterialResource(glm::u32 id);
		MaterialResource(glm::u32 id, const Flag& flag);
		MaterialResource(glm::u32 id, const glm::vec3& diffuse, const Flag& flag);

		virtual ~MaterialResource();

		void setProgram(ProgramResource* program);
		void setDiffuseColor(const glm::vec3& color);

		ProgramResource* getProgram() const;
		const glm::vec3& getDiffuseColor() const;

	private:
		bool create() override;
		bool release() override;

		ProgramResource* mProgram;

		glm::vec3 mDiffuseColor;
	};
}

#endif
