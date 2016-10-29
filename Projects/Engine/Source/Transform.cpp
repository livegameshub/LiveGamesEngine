#include "Transform.h"

namespace lg
{
	Transform::Transform()
		: Component()
		, mParentTransform(nullptr)
		, mHasUniformScale(true)
		, mScale(1.0f)
	{
	}

	Transform::Transform(const glm::vec3& position, const glm::quat& orientation, const glm::vec3& scale)
		: Component(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION)
		, mParentTransform(nullptr)
		, mHasUniformScale(true)
		, mOrientation(orientation)
		, mPosition(position)
		, mScale(scale)
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

			mMatrix = glm::mat4();

			mMatrix[0].x = mScale.x;
			mMatrix[1].y = mScale.y;
			mMatrix[2].z = mScale.z;

			mMatrix = glm::mat4_cast(mOrientation) * mMatrix;

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

		mScale = glm::vec3(1.0f);
		mOrientation = glm::quat();
		mPosition = glm::vec3();
	}

	void Transform::setParentTransform(Transform* transform)
	{
		mParentTransform = transform;
	}

	void Transform::translate(const glm::vec3& amount)
	{
		mPosition += amount;

		mFlag += NEW_POSITION;
	}

	void Transform::rotate(const glm::vec3& axis, glm::f32 angle)
	{
		mOrientation = glm::angleAxis(glm::radians(angle), axis);

		mFlag.add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void Transform::rotate(const glm::vec3& angles)
	{
		mOrientation = glm::quat(glm::radians(angles));

		mFlag.add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void Transform::rotateOnX(glm::f32 angle)
	{
		rotate(VECTOR_RIGHT, angle);
	}

	void Transform::rotateOnY(glm::f32 angle)
	{
		rotate(VECTOR_UP, angle);
	}

	void Transform::rotateOnZ(glm::f32 angle)
	{
		rotate(-VECTOR_FORWARD, angle);
	}

	void Transform::Scale(const glm::vec3& scale)
	{
		mScale = scale;

		mHasUniformScale = glm::abs(mScale.x - mScale.y) <= glm::epsilon<glm::f32>() &&
						   glm::abs(mScale.y - mScale.z) <= glm::epsilon<glm::f32>();

		mFlag.add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void Transform::setOrientation(const glm::quat& orientation)
	{
		mOrientation = orientation;

		mFlag.add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void Transform::setPosition(const glm::vec3& position)
	{
		mPosition = position;

		mFlag += NEW_POSITION;
	}

	void Transform::setScale(const glm::vec3& scale)
	{
		mScale = scale;

		mFlag.add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	const glm::quat& Transform::getOrientation() const
	{
		return mOrientation;
	}

	const glm::vec3& Transform::getPosition() const
	{
		return mPosition;
	}

	const glm::vec3& Transform::getScale() const
	{
		return mScale;
	}

	bool Transform::hasUniformScale() const
	{
		return mHasUniformScale;
	}

	Transform* Transform::getParentTransform() const
	{
		return mParentTransform;
	}

	glm::mat4 Transform::getMatrix() const
	{
		if (mParentTransform)
		{
			return mParentTransform->getMatrix() * mMatrix;
		}

		return mMatrix;
	}
}
