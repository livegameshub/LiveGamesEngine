#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Flag.h"

namespace lg
{
	class ENGINE_API Component
	{
	public:
		Component();
		Component(glm::i32 type);
		Component(glm::i32 type, const Flag& flag);
		Component(const Flag& flag);

		virtual ~Component();

		virtual void update() = 0;
		virtual void reset() = 0;

		void setFlag(const Flag& flag);
		void setType(glm::i32 type);

		const Flag& getFlag() const;
		glm::i32 getType() const;

		void setEnabled(bool value);
		bool isEnabled() const;

	protected:
		bool mIsEnabled;
		Flag mFlag;

	private:
		glm::i32 mType;
	};
}

#endif // _COMPONENT_H_
