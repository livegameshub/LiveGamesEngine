#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Flag.h"

namespace lg
{
	class ENGINE_API Component
	{
	public:
		enum ComponentType : glm::i32
		{
			TRANSFORM_COMPONENT
		};

		Component();
		Component(glm::i32 type);
		Component(glm::i32 type, const Flag& flag);
		Component(const Flag& flag);

		virtual ~Component();

		virtual void update() = 0;
		virtual void reset() = 0;

		void setFlag(const Flag& flag);
		void setComponentType(glm::i32 type);

		const Flag& getFlag() const;
		glm::i32 getComponentType() const;

		void setEnabled(bool value);
		bool isEnabled() const;

	protected:
		bool mIsEnabled;
		Flag mFlag;

	private:
		glm::i32 mComponentType;
	};
}

#endif // _COMPONENT_H_
