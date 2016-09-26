#include "Transform.h"

namespace ai
{
	Transform::Transform()
		: BasicComponent(TRANSFORM_COMPONENT)
		, mParentTransform(nullptr)
		, mScale(1.0f)
		, mHasUniformScale(true)
	{
	}

	Transform::Transform(const glm::vec3& position, const glm::quat& orientation, const glm::vec3& scale)
		: BasicComponent(TRANSFORM_COMPONENT)
		, mParentTransform(nullptr)
		, mOrientation(orientation)
		, mPosition(position)
		, mScale(scale)
		, mHasUniformScale(true)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Update()
	{
		if (mFlag.IsSet(NEW_ROTATION_SCALE_MATRIX))
		{
			/* rebuild the matrix every time */

			mMatrix = glm::mat4();

			mMatrix[0].x = mScale.x;
			mMatrix[1].y = mScale.y;
			mMatrix[2].z = mScale.z;

			mMatrix = glm::mat4_cast(mOrientation) * mMatrix;

			mFlag -= NEW_ROTATION_SCALE_MATRIX;
		}

		if (mFlag.IsSet(NEW_POSITION))
		{
			mMatrix[3].x = mPosition.x;
			mMatrix[3].y = mPosition.y;
			mMatrix[3].z = mPosition.z;

			mFlag -= NEW_POSITION;
		}
	}

	void Transform::Reset()
	{
		mFlag.Add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);

		mScale = glm::vec3(1.0f);
		mOrientation = glm::quat();
		mPosition = glm::vec3();
	}

	void Transform::SetParentTransform(Transform* transform)
	{
		mParentTransform = transform;
	}

	void Transform::Translate(const glm::vec3& amount)
	{
		mPosition += amount;

		mFlag += NEW_POSITION;
	}

	void Transform::Rotate(const glm::vec3& axis, glm::f32 angle)
	{
		mOrientation = glm::angleAxis(glm::radians(angle), axis);

		mFlag.Add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void Transform::Rotate(const glm::vec3& angles)
	{
		mOrientation = glm::quat(glm::radians(angles));

		mFlag.Add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void Transform::RotateOnX(glm::f32 angle)
	{
		Rotate(VECTOR_RIGHT, angle);
	}

	void Transform::RotateOnY(glm::f32 angle)
	{
		Rotate(VECTOR_UP, angle);
	}

	void Transform::RotateOnZ(glm::f32 angle)
	{
		Rotate(-VECTOR_FORWARD, angle);
	}

	void Transform::Scale(const glm::vec3& scale)
	{
		mScale = scale;

		mHasUniformScale = glm::abs(mScale.x - mScale.y) <= glm::epsilon<glm::f32>() &&
						   glm::abs(mScale.y - mScale.z) <= glm::epsilon<glm::f32>();

		mFlag.Add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void Transform::SetOrientation(const glm::quat& orientation)
	{
		mOrientation = orientation;

		mFlag.Add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void Transform::SetPosition(const glm::vec3& position)
	{
		mPosition = position;

		mFlag += NEW_POSITION;
	}

	void Transform::SetScale(const glm::vec3& scale)
	{
		mScale = scale;

		mFlag.Add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	const glm::quat& Transform::GetOrientation() const
	{
		return mOrientation;
	}

	const glm::vec3& Transform::GetPosition() const
	{
		return mPosition;
	}

	const glm::vec3& Transform::GetScale() const
	{
		return mScale;
	}

	bool Transform::HasUniformScale() const
	{
		return mHasUniformScale;
	}

	Transform* Transform::GetParentTransform() const
	{
		return mParentTransform;
	}

	glm::mat4 Transform::GetMatrix() const
	{
		if (mParentTransform)
		{
			return mParentTransform->GetMatrix() * mMatrix;
		}

		return mMatrix;
	}
}
