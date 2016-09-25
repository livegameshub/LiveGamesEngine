#include "Transform.h"

namespace ai
{
	Transform::Transform()
		: BasicComponent(TRANSFORM_COMPONENT)
		, mParentTransform(nullptr)
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
	}

	void Transform::SetParentTransform(Transform* transform)
	{
		mParentTransform = transform;
	}

	void Transform::SetOrientation(const Quaternion& orientation)
	{
		mOrientation = orientation;
	}

	void Transform::SetPosition(const Vector3& position)
	{
		mPosition = position;
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

	Transform* Transform::GetParentTransform() const
	{
		return mParentTransform;
	}

	Matrix4 Transform::GetMatrix() const
	{
		return mMatrix;
	}
}
