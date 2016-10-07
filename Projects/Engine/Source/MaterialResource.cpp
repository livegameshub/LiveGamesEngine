#include "MaterialResource.h"
#include "ResourceManager.h"

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

	MaterialResource::~MaterialResource()
	{
	}

	const glm::vec3& MaterialResource::GetDiffuseColor() const
	{
		return mDiffuseColor;
	}

	ProgramResource* MaterialResource::GetProgram() const
	{
		return mProgram;
	}

	void MaterialResource::setDiffuseColor(const glm::vec3& color)
	{
		mDiffuseColor = color;
	}

	void MaterialResource::SetProgram(ProgramResource* program)
	{
		assert(program != nullptr);

		if (mProgram)
		{
			ResourceManager::addPendingItem(mProgram, false);
		}

		mProgram = program;

		ResourceManager::addPendingItem(mProgram, true);
	}

	bool MaterialResource::Create()
	{
		return true;
	}

	bool MaterialResource::Release()
	{
		assert(mProgram != nullptr);

		ResourceManager::addPendingItem(mProgram, false);

		return true;
	}

}
