#include "DiffuseMaterialResource.h"
#include "ProgramResource.h"
#include "DirectionalLightNode.h"

namespace ai
{
	DiffuseMaterialResource::DiffuseMaterialResource(glm::u32 id)
		: BasicMaterialResource(id, IS_LIGHTED)
		, mSpecularColor(1.0f)
		, mSpecularShininess(0.0f)
	{
	}

	DiffuseMaterialResource::DiffuseMaterialResource(glm::u32 id, const glm::vec3& diffuse, const glm::vec3& specular, glm::f32 shininess, const Flag& flag)
		: BasicMaterialResource(id, diffuse, flag | IS_LIGHTED)
		, mSpecularColor(specular)
		, mSpecularShininess(shininess)
	{
	}

	DiffuseMaterialResource::~DiffuseMaterialResource()
	{
	}

	void DiffuseMaterialResource::uploadUniforms() const
	{
		BasicMaterialResource::uploadUniforms();

		if (IsShiny())
		{
			mProgram->setUniform(UNIFORM_MATERIAL_SHININESS, mSpecularShininess);
			mProgram->setUniform(UNIFORM_MATERIAL_SPECULAR, mSpecularColor);
		}
		else
		{
			mProgram->setUniform(UNIFORM_MATERIAL_SHININESS, glm::vec3());
		}
	}

	void DiffuseMaterialResource::uploadUniforms(DirectionalLightNode* light) const
	{
		mProgram->setUniform(UNIFORM_DIRECTIONAL_LIGHT_DIFFUSE, light->getDiffuseColor());
		mProgram->setUniform(UNIFORM_DIRECTIONAL_LIGHT_DIRECTION, light->getDirection());

		if (IsShiny())
		{
			mProgram->setUniform(UNIFORM_DIRECTIONAL_LIGHT_SPECULAR, light->getSpecularColor());
		}
	}

	void DiffuseMaterialResource::setSpecularColor(const glm::vec3& color)
	{
		mSpecularColor = color;
	}

	void DiffuseMaterialResource::setSpecularShininess(glm::f32 value)
	{
		mSpecularShininess = value;
	}

	const glm::vec3& DiffuseMaterialResource::getSpecularColor() const
	{
		return mSpecularColor;
	}

	glm::f32 DiffuseMaterialResource::getSpecularShininess() const
	{
		return mSpecularShininess;
	}

	bool DiffuseMaterialResource::create()
	{
		if (!mProgram->getFlag().isSet(ProgramResource::DIFFUSE_MATERIAL_UNIFORMS))
		{
			mProgram->addUniforms({ UNIFORM_MATERIAL_SPECULAR, 
									UNIFORM_MATERIAL_SHININESS,
									UNIFORM_AMBIENT_LIGHT, 
									UNIFORM_CAMERA_POSITION, 
									UNIFORM_NORMAL,
									UNIFORM_DIRECTIONAL_LIGHT_DIFFUSE,
									UNIFORM_DIRECTIONAL_LIGHT_DIRECTION, 
									UNIFORM_DIRECTIONAL_LIGHT_SPECULAR});

			mProgram->getFlag().add(ProgramResource::DIFFUSE_MATERIAL_UNIFORMS);
		}

		return BasicMaterialResource::create();
	}
}
