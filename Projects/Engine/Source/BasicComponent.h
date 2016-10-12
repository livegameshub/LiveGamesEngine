#ifndef _BASIC_COMPONENT_H_
#define _BASIC_COMPONENT_H_

#include "Flag.h"

namespace ai
{
	class ENGINE_API BasicComponent
	{
	public:
		enum ComponentType : glm::i32
		{
			TRANSFORM_COMPONENT
		};

		BasicComponent();
		BasicComponent(glm::i32 type);
		BasicComponent(glm::i32 type, const Flag& flag);
		BasicComponent(const Flag& flag);

		virtual ~BasicComponent();

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

#endif // _BASIC_COMPONENT_H_
