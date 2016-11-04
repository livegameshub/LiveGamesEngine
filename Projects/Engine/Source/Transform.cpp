#include "Transform.h"

namespace lg
{
	Transform::Transform()
		: mParent(nullptr)
		, mHasUniformScale(true)
		, mScale(1.0f)
	{
	}

	Transform::Transform(const vec3& position, const quat& orientation, const vec3& scale)
		: mParent(nullptr)
		, mHasUniformScale(true)
		, mOrientation(orientation)
		, mPosition(position)
		, mScale(scale)
		, mFlag(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::update()
	{
		if (mFlag.isSet(NEW_ROTATION_SCALE_MATRIX))
		{
			/* rebuild the matrix every time */

			mMatrix = mat4();

			mMatrix[0].x = mScale.x;
			mMatrix[1].y = mScale.y;
			mMatrix[2].z = mScale.z;

			mMatrix = mat4_cast(mOrientation) * mMatrix;

			mFlag -= NEW_ROTATION_SCALE_MATRIX;
		}

		if (mFlag.isSet(NEW_POSITION))
		{
			mMatrix[3].x = mPosition.x;
			mMatrix[3].y = mPosition.y;
			mMatrix[3].z = mPosition.z;

			mFlag -= NEW_POSITION;
		}
	}

	void Transform::reset()
	{
		mFlag.add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);

		mScale = vec3(1.0f);
		mOrientation = quat();
		mPosition = vec3();
	}

	void Transform::setParent(Transform* transform)
	{
		mParent = transform;
	}

	void Transform::translate(const vec3& amount)
	{
		mPosition += amount;

		mFlag += NEW_POSITION;
	}

	void Transform::rotate(const vec3& axis, f32 angle)
	{
		mOrientation = angleAxis(radians(angle), axis);

		mFlag.add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void Transform::rotate(const vec3& angles)
	{
		mOrientation = quat(radians(angles));

		mFlag.add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void Transform::rotateOnX(f32 angle)
	{
		rotate(VECTOR_RIGHT, angle);
	}

	void Transform::rotateOnY(f32 angle)
	{
		rotate(VECTOR_UP, angle);
	}

	void Transform::rotateOnZ(f32 angle)
	{
		rotate(-VECTOR_FORWARD, angle);
	}

	void Transform::Scale(const vec3& scale)
	{
		mScale = scale;

		mHasUniformScale = abs(mScale.x - mScale.y) <= epsilon<f32>() &&
						   abs(mScale.y - mScale.z) <= epsilon<f32>();

		mFlag.add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void Transform::setOrientation(const quat& orientation)
	{
		mOrientation = orientation;

		mFlag.add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void Transform::setPosition(const vec3& position)
	{
		mPosition = position;

		mFlag += NEW_POSITION;
	}

	void Transform::setScale(const vec3& scale)
	{
		mScale = scale;

		mFlag.add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	const quat& Transform::getOrientation() const
	{
		return mOrientation;
	}

	const vec3& Transform::getPosition() const
	{
		return mPosition;
	}

	const vec3& Transform::getScale() const
	{
		return mScale;
	}

	bool Transform::hasUniformScale() const
	{
		return mHasUniformScale;
	}

	Transform* Transform::getParent() const
	{
		return mParent;
	}

	mat4 Transform::getMatrix() const
	{
		if (mParent)
		{
			return mParent->getMatrix() * mMatrix;
		}

		return mMatrix;
	}
}
