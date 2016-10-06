#include "TransformComponent.h"

namespace ai
{
	TransformComponent::TransformComponent()
		: BasicComponent(TRANSFORM_COMPONENT)
		, mParentTransform(nullptr)
		, mScale(1.0f)
		, mHasUniformScale(true)
	{
	}

	TransformComponent::TransformComponent(const glm::vec3& position, const glm::quat& orientation, const glm::vec3& scale)
		: BasicComponent(TRANSFORM_COMPONENT, NEW_ROTATION_SCALE_MATRIX | NEW_POSITION)
		, mParentTransform(nullptr)
		, mOrientation(orientation)
		, mPosition(position)
		, mScale(scale)
		, mHasUniformScale(true)
	{
	}

	TransformComponent::~TransformComponent()
	{
	}

	void TransformComponent::Update()
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

	void TransformComponent::Reset()
	{
		mFlag.Add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);

		mScale = glm::vec3(1.0f);
		mOrientation = glm::quat();
		mPosition = glm::vec3();
	}

	void TransformComponent::SetParentTransform(TransformComponent* transform)
	{
		mParentTransform = transform;
	}

	void TransformComponent::Translate(const glm::vec3& amount)
	{
		mPosition += amount;

		mFlag += NEW_POSITION;
	}

	void TransformComponent::Rotate(const glm::vec3& axis, glm::f32 angle)
	{
		mOrientation = glm::angleAxis(glm::radians(angle), axis);

		mFlag.Add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void TransformComponent::Rotate(const glm::vec3& angles)
	{
		mOrientation = glm::quat(glm::radians(angles));

		mFlag.Add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void TransformComponent::RotateOnX(glm::f32 angle)
	{
		Rotate(VECTOR_RIGHT, angle);
	}

	void TransformComponent::RotateOnY(glm::f32 angle)
	{
		Rotate(VECTOR_UP, angle);
	}

	void TransformComponent::RotateOnZ(glm::f32 angle)
	{
		Rotate(-VECTOR_FORWARD, angle);
	}

	void TransformComponent::Scale(const glm::vec3& scale)
	{
		mScale = scale;

		mHasUniformScale = glm::abs(mScale.x - mScale.y) <= glm::epsilon<glm::f32>() &&
						   glm::abs(mScale.y - mScale.z) <= glm::epsilon<glm::f32>();

		mFlag.Add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void TransformComponent::SetOrientation(const glm::quat& orientation)
	{
		mOrientation = orientation;

		mFlag.Add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	void TransformComponent::SetPosition(const glm::vec3& position)
	{
		mPosition = position;

		mFlag += NEW_POSITION;
	}

	void TransformComponent::SetScale(const glm::vec3& scale)
	{
		mScale = scale;

		mFlag.Add(NEW_ROTATION_SCALE_MATRIX | NEW_POSITION);
	}

	const glm::quat& TransformComponent::GetOrientation() const
	{
		return mOrientation;
	}

	const glm::vec3& TransformComponent::GetPosition() const
	{
		return mPosition;
	}

	const glm::vec3& TransformComponent::GetScale() const
	{
		return mScale;
	}

	bool TransformComponent::HasUniformScale() const
	{
		return mHasUniformScale;
	}

	TransformComponent* TransformComponent::GetParentTransform() const
	{
		return mParentTransform;
	}

	glm::mat4 TransformComponent::GetMatrix() const
	{
		if (mParentTransform)
		{
			return mParentTransform->GetMatrix() * mMatrix;
		}

		return mMatrix;
	}
}
