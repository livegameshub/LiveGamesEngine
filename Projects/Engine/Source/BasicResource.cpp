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

	bool BasicResource::Load()
	{
		if (!mReferencesCounter)
		{
			if (!Create())
			{
				return false;
			}
		}

		++mReferencesCounter;

		return true;
	}

	bool BasicResource::Unload()
	{
		if (!mReferencesCounter)
		{
			return false;
		}

		if (mReferencesCounter == 1)
		{
			if (!Release())
			{
				return false;
			}
		}

		--mReferencesCounter;

		return true;
	}

	void BasicResource::SetResourceFile(const std::string& file)
	{
		mResourceFile = file;
	}

	std::string BasicResource::getResourceFile() const
	{
		return mResourceFile;
	}

	glm::u32 BasicResource::GetReferencesCounter() const
	{
		return mReferencesCounter;
	}
}
