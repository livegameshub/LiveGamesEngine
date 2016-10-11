#include "BasicResource.h"

namespace ai
{
	BasicResource::BasicResource(glm::u32 id)
		: BasicElement(id)
		, mReferencesCounter(0)
	{
	}

	BasicResource::BasicResource(glm::u32 id, const Flag& flag)
		: BasicElement(id, flag)
		, mReferencesCounter(0)
	{
	}

	BasicResource::BasicResource(glm::u32 id, const std::string& file)
		: BasicElement(id)
		, mResourceFile(file)
		, mReferencesCounter(0)
	{
	}

	BasicResource::~BasicResource()
	{
	}

	bool BasicResource::load()
	{
		if (!mReferencesCounter)
		{
			if (!create())
			{
				return false;
			}
		}

		++mReferencesCounter;

		return true;
	}

	bool BasicResource::unload()
	{
		if (!mReferencesCounter)
		{
			return false;
		}

		if (mReferencesCounter == 1)
		{
			if (!release())
			{
				return false;
			}
		}

		--mReferencesCounter;

		return true;
	}

	void BasicResource::setResourceFile(const std::string& file)
	{
		mResourceFile = file;
	}

	std::string BasicResource::getResourceFile() const
	{
		return mResourceFile;
	}

	glm::u32 BasicResource::getReferencesCounter() const
	{
		return mReferencesCounter;
	}
}
