#ifndef _BASIC_MATERIAL_RESOURCE_H_
#define _BASIC_MATERIAL_RESOURCE_H_

#include "BasicResource.h"

/* some useful constants */
const std::string UNIFORM_VIEW = "u_view";
const std::string UNIFORM_MODEL = "u_model";
const std::string UNIFORM_NORMAL = "u_normal";
const std::string UNIFORM_PROJECTION = "u_projection";

const std::string UNIFORM_AMBIENT_LIGHT = "u_ambient_light";

const std::string UNIFORM_CAMERA_POSITION = "u_camera_position";

const std::string UNIFORM_MATERIAL_DIFFUSE = "u_material.diffuse";
const std::string UNIFORM_MATERIAL_SPECULAR = "u_material.specular";
const std::string UNIFORM_MATERIAL_SHININESS = "u_material.shininess";

const std::string UNIFORM_DIRECTIONAL_LIGHT_DIFFUSE = "u_directional_light.light.diffuse";
const std::string UNIFORM_DIRECTIONAL_LIGHT_SPECULAR = "u_directional_light.light.specular";
const std::string UNIFORM_DIRECTIONAL_LIGHT_DIRECTION = "u_directional_light.direction";

namespace ai
{
	class ProgramResource;

	class ENGINE_API BasicMaterialResource : public BasicResource
	{
	public:
		enum MaterialProperties : glm::u32
		{
			IS_LIGHTED = 1,
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

		bool IsLighted() const;
		bool IsTextured() const;
		bool IsShiny() const;

	protected:
		ProgramResource* mProgram;

		virtual bool create();

	private:
		glm::vec3 mDiffuseColor;

		bool release() override;
	};
}

#endif // _BASIC_MATERIAL_RESOURCE_H_
