#include "BasicMaterialResource.h"
#include "ResourceManager.h"
#include "ProgramResource.h"

namespace ai
{
	BasicMaterialResource::BasicMaterialResource(glm::u32 id)
		: BasicResource(id)
		, mProgram(nullptr)
		, mDiffuseColor(1.0f)
	{
	}

	BasicMaterialResource::BasicMaterialResource(glm::u32 id, const Flag& flag)
		: BasicResource(id, flag)
		, mProgram(nullptr)
		, mDiffuseColor(1.0f)
	{
	}

	BasicMaterialResource::BasicMaterialResource(glm::u32 id, const glm::vec3& diffuse, const Flag& flag)
		: BasicResource(id, flag)
		, mProgram(nullptr)
		, mDiffuseColor(diffuse)
	{
	}

	BasicMaterialResource::~BasicMaterialResource()
	{
	}

	void BasicMaterialResource::UploadUniforms() const
	{
		mProgram->setUniform(UNIFORM_MATERIAL_DIFFUSE, mDiffuseColor);
	}

	const glm::vec3& BasicMaterialResource::getDiffuseColor() const
	{
		return mDiffuseColor;
	}

	ProgramResource* BasicMaterialResource::getProgram() const
	{
		return mProgram;
	}

	void BasicMaterialResource::setDiffuseColor(const glm::vec3& color)
	{
		mDiffuseColor = color;
	}

	void BasicMaterialResource::setProgram(ProgramResource* program)
	{
		assert(program != nullptr);

		if (mProgram)
		{
			ResourceManager::getInstance().unload(mProgram);
		}

		mProgram = program;

		ResourceManager::getInstance().load(mProgram);
	}

	bool BasicMaterialResource::create()
	{
		assert(mProgram != nullptr);

		if (mProgram->getUniforms().size() == 0)
		{
			mProgram->addUniforms({ UNIFORM_VIEW, UNIFORM_PROJECTION, UNIFORM_MODEL, UNIFORM_MATERIAL_DIFFUSE });
			mProgram->initUniforms();
		}

		return true;
	}

	bool BasicMaterialResource::release()
	{
		assert(mProgram != nullptr);

		ResourceManager::getInstance().unload(mProgram);

		return true;
	}
}
