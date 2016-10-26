#include "Resource.h"

namespace lg
{
	Resource::Resource(glm::u32 id)
		: Object(id)
		, mReferencesCounter(0)
	{
	}

	Resource::Resource(glm::u32 id, const Flag& flag)
		: Object(id, flag)
		, mReferencesCounter(0)
	{
	}

	Resource::Resource(glm::u32 id, const std::string& file)
		: Object(id)
		, mResourceFile(file)
		, mReferencesCounter(0)
	{
	}

	Resource::~Resource()
	{
	}

	bool Resource::load()
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

	bool Resource::unload()
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

	void Resource::setResourceFile(const std::string& file)
	{
		mResourceFile = file;
	}

	const std::string& Resource::getResourceFile() const
	{
		return mResourceFile;
	}

	glm::u32 Resource::getReferencesCounter() const
	{
		return mReferencesCounter;
	}
}
