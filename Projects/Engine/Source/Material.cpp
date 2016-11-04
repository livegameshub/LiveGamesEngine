#include "Material.h"
#include "Resources.h"
#include "Program.h"
#include "Texture.h"

namespace lg
{
	Material::Material(u32 id, const Flag& flag)
		: Resource(id, flag)
		, mDiffuseTexture(nullptr)
		, mProgram(nullptr)
		, mDiffuseColor(MATERIAL_DEFAULT_DIFFUSE_COLOR)
	{
	}

	Material::Material(u32 id, const vec3& diffuse, const Flag& flag)
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

	const vec3& Material::getDiffuseColor() const
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
			Resources::instance().unload(mDiffuseTexture);
		}

		mDiffuseTexture = texture;

		Resources::instance().load(mDiffuseTexture);
	}

	Texture* Material::getDiffuseTexture() const
	{
		return mDiffuseTexture;
	}

	void Material::setDiffuseColor(const vec3& color)
	{
		mDiffuseColor = color;
	}

	void Material::setProgram(Program* program)
	{
		assert(program != nullptr);

		if (mProgram)
		{
			Resources::instance().unload(mProgram);
		}

		mProgram = program;

		Resources::instance().load(mProgram);
	}

	bool Material::create()
	{
		assert(mProgram != nullptr);

		if (!mProgram->getFlag().isSet(Program::BASIC_MATERIAL))
		{
			mProgram->addUniforms({ UNIFORM_VIEW, 
									UNIFORM_PROJECTION, 
									UNIFORM_MODEL, 
									UNIFORM_MATERIAL_DIFFUSE });

			mProgram->initUniforms();

			mProgram->getFlag().add(Program::BASIC_MATERIAL);
		}

		return true;
	}

	bool Material::release()
	{
		assert(mProgram != nullptr);
		Resources::instance().unload(mProgram);
	
		if (mDiffuseTexture)
		{
			// unload the texture
			Resources::instance().unload(mDiffuseTexture);
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
