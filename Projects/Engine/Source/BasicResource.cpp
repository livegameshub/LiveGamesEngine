#include "BasicResource.h"

namespace ai
{
	BasicResource::BasicResource(u32 id)
		: BasicElement(id)
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

	std::string BasicResource::GetResourceFile() const
	{
		return mResourceFile;
	}

	u32 BasicResource::GetReferencesCounter() const
	{
		return mReferencesCounter;
	}
}
