#ifndef _BASIC_COMPONENT_H_
#define _BASIC_COMPONENT_H_

#include "Flag.h"

namespace ai
{
	class ENGINE_API BasicComponent
	{
	public:
		enum ComponentType : i32
		{
			TRANSFORM_COMPONENT
		};

		BasicComponent();
		BasicComponent(i32 type);
		BasicComponent(i32 type, const Flag& flag);
		BasicComponent(const Flag& flag);

		virtual ~BasicComponent();

		virtual void Update() = 0;
		virtual void Reset() = 0;

		inline void SetFlag(const Flag& flag);
		inline void SetType(i32 type);

		inline const Flag& GetFlag() const;
		inline i32 GetType() const;

		inline void SetEnabled(bool value);
		inline bool IsEnabled() const;

	protected:
		bool mIsEnabled;
		Flag mFlag;

	private:
		i32 mComponentType;
	};
}

#endif
