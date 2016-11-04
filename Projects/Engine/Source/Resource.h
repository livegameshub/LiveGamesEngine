#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "Object.h"

namespace lg
{
	class ENGINE_API Resource : public Object
	{
	public:
		Resource(u32 id);
		Resource(u32 id, const Flag& flag);
		Resource(u32 id, const string& file);
		
		virtual ~Resource();

		const string& getResourceFile() const;
		void setResourceFile(const string& file);

		u32 getReferencesCounter() const;

		bool unload();
		bool load();

	protected:
		string mResourceFile;

	private:
		virtual bool create() = 0;
		virtual bool release() = 0;

		u32 mReferencesCounter;
	};
}

#endif // _RESOURCE_H_
