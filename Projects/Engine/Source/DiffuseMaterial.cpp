#include "DiffuseMaterial.h"
#include "Program.h"
#include "DirectionalLight.h"
#include "Resources.h"
#include "Texture.h"

namespace lg
{
	DiffuseMaterial::DiffuseMaterial(glm::u32 id, const Flag& flag)
		: Material(id, flag)
		, mSpecularColor(MATERIAL_DEFAULT_SPECULAR_COLOR)
		, mSpecularShininess(MATERIAL_DEFAULT_SHININESS)
	{
	}

	DiffuseMaterial::DiffuseMaterial(glm::u32 id, const glm::vec3& diffuse, const Flag& flag)
		: Material(id, diffuse, flag)
		, mSpecularColor(MATERIAL_DEFAULT_SPECULAR_COLOR)
		, mSpecularShininess(MATERIAL_DEFAULT_SHININESS)
	{
	}

	DiffuseMaterial::~DiffuseMaterial()
	{
	}

	void DiffuseMaterial::uploadUniforms() const
	{
		Material::uploadUniforms();

		if (IsShiny())
		{
			mProgram->setUniform(UNIFORM_MATERIAL_SHININESS, mSpecularShininess);
			mProgram->setUniform(UNIFORM_MATERIAL_SPECULAR, mSpecularColor);
		}
		else
		{
			mProgram->setUniform(UNIFORM_MATERIAL_SPECULAR, glm::vec3());
		}
	}

	void DiffuseMaterial::uploadUniforms(DirectionalLight* light) const
	{
		mProgram->setUniform(UNIFORM_DIRECTIONAL_LIGHT_DIFFUSE, light->getDiffuseColor());
		mProgram->setUniform(UNIFORM_DIRECTIONAL_LIGHT_DIRECTION, light->getDirection());

		if (IsShiny())
		{
			mProgram->setUniform(UNIFORM_DIRECTIONAL_LIGHT_SPECULAR, light->getSpecularColor());
		}
	}

	void DiffuseMaterial::setSpecularColor(const glm::vec3& color)
	{
		mSpecularColor = color;
	}

	void DiffuseMaterial::setSpecularShininess(glm::f32 value)
	{
		mSpecularShininess = value;
	}

	const glm::vec3& DiffuseMaterial::getSpecularColor() const
	{
		return mSpecularColor;
	}

	glm::f32 DiffuseMaterial::getSpecularShininess() const
	{
		return mSpecularShininess;
	}

	bool DiffuseMaterial::create()
	{
		if (!mProgram->getFlag().isSet(Program::DIFFUSE_MATERIAL))
		{
			mProgram->addUniforms({ UNIFORM_MATERIAL_SPECULAR, 
									UNIFORM_MATERIAL_SHININESS,
									UNIFORM_AMBIENT_LIGHT, 
									UNIFORM_CAMERA_POSITION, 
									UNIFORM_NORMAL,
									UNIFORM_DIRECTIONAL_LIGHT_DIFFUSE,
									UNIFORM_DIRECTIONAL_LIGHT_DIRECTION, 
									UNIFORM_DIRECTIONAL_LIGHT_SPECULAR});

			mProgram->getFlag().add(Program::DIFFUSE_MATERIAL);
		}

		return Material::create();
	}

	bool DiffuseMaterial::release()
	{
		return Material::release();
	}
}
