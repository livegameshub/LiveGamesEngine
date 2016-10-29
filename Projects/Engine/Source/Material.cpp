#include "Material.h"
#include "Resources.h"
#include "Program.h"
#include "Texture.h"

namespace lg
{
	Material::Material(glm::u32 id, const Flag& flag)
		: Resource(id, flag)
		, mDiffuseTexture(nullptr)
		, mProgram(nullptr)
		, mDiffuseColor(MATERIAL_DEFAULT_DIFFUSE_COLOR)
	{
	}

	Material::Material(glm::u32 id, const glm::vec3& diffuse, const Flag& flag)
		: Resource(id, flag)
		, mDiffuseTexture(nullptr)
		, mProgram(nullptr)
		, mDiffuseColor(diffuse)
	{
	}

	Material::~Material()
	{
	}

	void Material::uploadUniforms() const
	{
		mProgram->setUniform(UNIFORM_MATERIAL_DIFFUSE, mDiffuseColor);
	}

	const glm::vec3& Material::getDiffuseColor() const
	{
		return mDiffuseColor;
	}

	Program* Material::getProgram() const
	{
		return mProgram;
	}

	void Material::setDiffuseTexture(Texture* texture)
	{
		assert(texture != nullptr);

		if (mDiffuseTexture)
		{
			Resources::getInstance().unload(mDiffuseTexture);
		}

		mDiffuseTexture = texture;

		Resources::getInstance().load(mDiffuseTexture);
	}

	Texture* Material::getDiffuseTexture() const
	{
		return mDiffuseTexture;
	}

	void Material::setDiffuseColor(const glm::vec3& color)
	{
		mDiffuseColor = color;
	}

	void Material::setProgram(Program* program)
	{
		assert(program != nullptr);

		if (mProgram)
		{
			Resources::getInstance().unload(mProgram);
		}

		mProgram = program;

		Resources::getInstance().load(mProgram);
	}

	bool Material::create()
	{
		assert(mProgram != nullptr);

		if (!mProgram->getFlag().isSet(Program::BASIC_MATERIAL_UNIFORMS))
		{
			mProgram->addUniforms({ UNIFORM_VIEW, 
									UNIFORM_PROJECTION, 
									UNIFORM_MODEL, 
									UNIFORM_MATERIAL_DIFFUSE });

			mProgram->initUniforms();

			mProgram->getFlag().add(Program::BASIC_MATERIAL_UNIFORMS);
		}

		return true;
	}

	bool Material::release()
	{
		assert(mProgram != nullptr);
		Resources::getInstance().unload(mProgram);
	
		if (mDiffuseTexture)
		{
			// unload the texture
			Resources::getInstance().unload(mDiffuseTexture);
		}

		return true;
	}

	bool Material::IsLighted() const
	{
		return mFlag.isSet(IS_LIGHTED);
	}

	bool Material::IsTextured() const
	{
		return mFlag.isSet(IS_TEXTURED);
	}

	bool Material::IsShiny() const
	{
		return mFlag.isSet(IS_SHINY);
	}
}
