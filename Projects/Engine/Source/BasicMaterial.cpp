#include "BasicMaterial.h"
#include "Resources.h"
#include "ProgramResource.h"

namespace ai
{
	BasicMaterial::BasicMaterial(glm::u32 id)
		: BasicResource(id)
		, mProgram(nullptr)
		, mDiffuseColor(1.0f)
	{
	}

	BasicMaterial::BasicMaterial(glm::u32 id, const Flag& flag)
		: BasicResource(id, flag)
		, mProgram(nullptr)
		, mDiffuseColor(1.0f)
	{
	}

	BasicMaterial::BasicMaterial(glm::u32 id, const glm::vec3& diffuse, const Flag& flag)
		: BasicResource(id, flag)
		, mProgram(nullptr)
		, mDiffuseColor(diffuse)
	{
	}

	BasicMaterial::~BasicMaterial()
	{
	}

	void BasicMaterial::uploadUniforms() const
	{
		mProgram->setUniform(UNIFORM_MATERIAL_DIFFUSE, mDiffuseColor);
	}

	const glm::vec3& BasicMaterial::getDiffuseColor() const
	{
		return mDiffuseColor;
	}

	ProgramResource* BasicMaterial::getProgram() const
	{
		return mProgram;
	}

	void BasicMaterial::setDiffuseColor(const glm::vec3& color)
	{
		mDiffuseColor = color;
	}

	void BasicMaterial::setProgram(ProgramResource* program)
	{
		assert(program != nullptr);

		if (mProgram)
		{
			Resources::getInstance().unload(mProgram);
		}

		mProgram = program;

		Resources::getInstance().load(mProgram);
	}

	bool BasicMaterial::create()
	{
		assert(mProgram != nullptr);

		if (!mProgram->getFlag().isSet(ProgramResource::BASIC_MATERIAL_UNIFORMS))
		{
			mProgram->addUniforms({ UNIFORM_VIEW, 
									UNIFORM_PROJECTION, 
									UNIFORM_MODEL, 
									UNIFORM_MATERIAL_DIFFUSE });

			mProgram->initUniforms();

			mProgram->getFlag().add(ProgramResource::BASIC_MATERIAL_UNIFORMS);
		}

		return true;
	}

	bool BasicMaterial::release()
	{
		assert(mProgram != nullptr);

		Resources::getInstance().unload(mProgram);

		return true;
	}

	bool BasicMaterial::IsLighted() const
	{
		return mFlag.isSet(IS_LIGHTED);
	}

	bool BasicMaterial::IsTextured() const
	{
		return mFlag.isSet(IS_TEXTURED);
	}

	bool BasicMaterial::IsShiny() const
	{
		return mFlag.isSet(IS_SHINY);
	}
}
