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
	}

	void Transform::Rotate(const glm::vec3& angles)
	{
	}

	void Transform::RotateOnX(glm::f32 angle)
	{
	}

	void Transform::RotateOnY(glm::f32 angle)
	{
	}

	void Transform::RotateOnZ(glm::f32 angle)
	{
	}

	void Transform::Scale(const glm::vec3& scale)
	{
	}

	void Transform::SetOrientation(const glm::quat& orientation)
	{
		mOrientation = orientation;
	}

	void Transform::SetPosition(const glm::vec3& position)
	{
		mPosition = position;

		mFlag += NEW_POSITION;
	}

	void Transform::SetScale(const glm::vec3& scale)
	{
		mScale = scale;
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
