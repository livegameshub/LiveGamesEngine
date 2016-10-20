#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Resource.h"

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
	class Program;

	class ENGINE_API Material : public Resource
	{
	public:
		enum MaterialProperties : glm::u32
		{
			IS_LIGHTED = 1,
			IS_TEXTURED = 2,
			IS_SHINY = 4
		};

		Material(glm::u32 id);
		Material(glm::u32 id, const Flag& flag);
		Material(glm::u32 id, const glm::vec3& diffuse, const Flag& flag);

		virtual ~Material();

		virtual void uploadUniforms() const;

		void setProgram(Program* program);
		void setDiffuseColor(const glm::vec3& color);
	
		Program* getProgram() const;
		const glm::vec3& getDiffuseColor() const;

		bool IsLighted() const;
		bool IsTextured() const;
		bool IsShiny() const;

	protected:
		Program* mProgram;

		virtual bool create();

	private:
		glm::vec3 mDiffuseColor;

		bool release() override;
	};
}

#endif // _MATERIAL_H_
