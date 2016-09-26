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

	Transform::Transform(const Vector3& position, const Quaternion& orientation, const Vector3& scale)
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

		mScale = Vector3(1.0f);
		mOrientation.Identity();
		mPosition.Zero();
	}

	void Transform::SetParentTransform(Transform* transform)
	{
		mParentTransform = transform;
	}

	void Transform::Translate(const Vector3& amount)
	{
		mPosition += amount;

		mFlag += NEW_POSITION;
	}

	void Transform::Rotate(const Vector3& axis, f32 angle)
	{
	}

	void Transform::Rotate(const Vector3& angles)
	{
	}

	void Transform::RotateOnX(f32 angle)
	{
	}

	void Transform::RotateOnY(f32 angle)
	{
	}

	void Transform::RotateOnZ(f32 angle)
	{
	}

	void Transform::Scale(const Vector3& scale)
	{
	}

	void Transform::SetOrientation(const Quaternion& orientation)
	{
		mOrientation = orientation;
	}

	void Transform::SetPosition(const Vector3& position)
	{
		mPosition = position;

		mFlag += NEW_POSITION;
	}

	void Transform::SetScale(const Vector3& scale)
	{
		mScale = scale;
	}

	const Quaternion& Transform::GetOrientation() const
	{
		return mOrientation;
	}

	const Vector3& Transform::GetPosition() const
	{
		return mPosition;
	}

	const Vector3& Transform::GetScale() const
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

	Matrix4 Transform::GetMatrix() const
	{
		if (mParentTransform)
		{
			// TODO
			// uncomment this when you have the * operator

			//return mParentTransform->GetMatrix() * mMatrix;
		}

		return mMatrix;
	}
}
