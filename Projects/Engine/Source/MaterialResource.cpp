#include "MaterialResource.h"
#include "ResourceManager.h"
#include "ProgramResource.h"

namespace ai
{
	MaterialResource::MaterialResource(glm::u32 id)
		: BasicResource(id)
		, mProgram(nullptr)
		, mDiffuseColor(1.0f)
	{
	}

	MaterialResource::MaterialResource(glm::u32 id, const Flag& flag)
		: BasicResource(id, flag)
		, mProgram(nullptr)
		, mDiffuseColor(1.0f)
	{
	}

	MaterialResource::MaterialResource(glm::u32 id, const glm::vec3& diffuse, const Flag& flag)
		: BasicResource(id, flag)
		, mProgram(nullptr)
		, mDiffuseColor(diffuse)
	{
	}

	MaterialResource::~MaterialResource()
	{
	}

	const glm::vec3& MaterialResource::getDiffuseColor() const
	{
		return mDiffuseColor;
	}

	ProgramResource* MaterialResource::getProgram() const
	{
		return mProgram;
	}

	void MaterialResource::setDiffuseColor(const glm::vec3& color)
	{
		mDiffuseColor = color;
	}

	void MaterialResource::setProgram(ProgramResource* program)
	{
		assert(program != nullptr);

		if (mProgram)
		{
			ResourceManager::getInstance().addPendingItem(mProgram, false);
		}

		mProgram = program;

		ResourceManager::getInstance().addPendingItem(mProgram, true);
	}

	bool MaterialResource::create()
	{
		assert(mProgram != nullptr);

		if (mProgram->getUniforms().size() == 0)
		{
			mProgram->addUniforms({ UNIFORM_VIEW, UNIFORM_PROJECTION, UNIFORM_MODEL,
									UNIFORM_MATERIAL_DIFFUSE });

			mProgram->initUniforms();
		}

		return true;
	}

	bool MaterialResource::release()
	{
		assert(mProgram != nullptr);

		ResourceManager::getInstance().addPendingItem(mProgram, false);

		return true;
	}
}
