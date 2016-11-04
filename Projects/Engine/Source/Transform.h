#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Flag.h"

namespace lg
{
	class ENGINE_API Transform
	{
	public:
		enum TransformFlag : u32
		{
			NEW_POSITION = 1,
			NEW_ROTATION_SCALE_MATRIX = 2
		};

		Transform();
		Transform(const vec3& position, const quat& orientation, const vec3& scale);

		~Transform();

		void update();
		void reset();

		void translate(const vec3& amount);
		void Scale(const vec3& scale);

		void rotate(const vec3& axis, f32 angle);
		void rotate(const vec3& angles);
		void rotateOnX(f32 angle);
		void rotateOnY(f32 angle);
		void rotateOnZ(f32 angle);
	
		void setParent(Transform* transform);

		void setOrientation(const quat& orientation);
		void setPosition(const vec3& position);
		void setScale(const vec3& scale);

		const quat& getOrientation() const;
		const vec3& getPosition() const;
		const vec3& getScale() const;

		bool hasUniformScale() const;
		Transform* getParent() const;
		mat4 getMatrix() const;

	private:
		Transform* mParent;

		bool mHasUniformScale;

		mat4 mMatrix;
		quat mOrientation;
		vec3 mPosition;
		vec3 mScale;

		Flag mFlag;
	};
}

#endif // _TRANSFORM_H_
