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
		virtual void Reset() = 0;

		void SetFlag(const Flag& flag);
		void SetComponentType(glm::i32 type);

		const Flag& GetFlag() const;
		glm::i32 GetComponentType() const;

		void SetEnabled(bool value);
		bool IsEnabled() const;

	protected:
		bool mIsEnabled;
		Flag mFlag;

	private:
		glm::i32 mComponentType;
	};
}

#endif
