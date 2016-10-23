#include "DiffuseMaterial.h"
#include "Program.h"
#include "DirectionalLight.h"
#include "Resources.h"
#include "Texture.h"

namespace ai
{
	DiffuseMaterial::DiffuseMaterial(glm::u32 id)
		: Material(id, IS_LIGHTED)
		, mSpecularColor(1.0f)
		, mSpecularShininess(0.0f)
		, mDiffuseTexture(nullptr)
	{
	}

	DiffuseMaterial::DiffuseMaterial(glm::u32 id, const glm::vec3& diffuse, const glm::vec3& specular, glm::f32 shininess, const Flag& flag)
		: Material(id, diffuse, flag | IS_LIGHTED)
		, mSpecularColor(specular)
		, mSpecularShininess(shininess)
		, mDiffuseTexture(nullptr)
	{
	}

	DiffuseMaterial::~DiffuseMaterial()
	{
	}

	void DiffuseMaterial::setDiffuseTexture(Texture* texture)
	{
		assert(texture != nullptr);

		if (mDiffuseTexture)
		{
			Resources::getInstance().unload(mDiffuseTexture);
		}

		mDiffuseTexture = texture;

		Resources::getInstance().load(mDiffuseTexture);
	}

	Texture* DiffuseMaterial::getDiffuseTexture() const
	{
		return mDiffuseTexture;
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
		if (!mProgram->getFlag().isSet(Program::DIFFUSE_MATERIAL_UNIFORMS))
		{
			mProgram->addUniforms({ UNIFORM_MATERIAL_SPECULAR, 
									UNIFORM_MATERIAL_SHININESS,
									UNIFORM_AMBIENT_LIGHT, 
									UNIFORM_CAMERA_POSITION, 
									UNIFORM_NORMAL,
									UNIFORM_DIRECTIONAL_LIGHT_DIFFUSE,
									UNIFORM_DIRECTIONAL_LIGHT_DIRECTION, 
									UNIFORM_DIRECTIONAL_LIGHT_SPECULAR});

			mProgram->getFlag().add(Program::DIFFUSE_MATERIAL_UNIFORMS);
		}

		return Material::create();
	}

	bool DiffuseMaterial::release()
	{
		if (mDiffuseTexture)
		{
 			Resources::getInstance().unload(mDiffuseTexture);
		}

		return Material::release();
	}
}
