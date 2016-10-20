#include "Material.h"
#include "Resources.h"
#include "Program.h"

namespace ai
{
	Material::Material(glm::u32 id)
		: Resource(id)
		, mProgram(nullptr)
		, mDiffuseColor(1.0f)
	{
	}

	Material::Material(glm::u32 id, const Flag& flag)
		: Resource(id, flag)
		, mProgram(nullptr)
		, mDiffuseColor(1.0f)
	{
	}

	Material::Material(glm::u32 id, const glm::vec3& diffuse, const Flag& flag)
		: Resource(id, flag)
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
