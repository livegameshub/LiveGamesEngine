#include "Resource.h"

namespace lg
{
	Resource::Resource(u32 id)
		: Object(id)
		, mReferencesCounter(0)
	{
	}

	Resource::Resource(u32 id, const Flag& flag)
		: Object(id, flag)
		, mReferencesCounter(0)
	{
	}

	Resource::Resource(u32 id, const string& file)
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

	void Resource::setResourceFile(const string& file)
	{
		mResourceFile = file;
	}

	const string& Resource::getResourceFile() const
	{
		return mResourceFile;
	}

	u32 Resource::getReferencesCounter() const
	{
		return mReferencesCounter;
	}
}
