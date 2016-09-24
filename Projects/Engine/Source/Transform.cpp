#include "Transform.h"

namespace ai
{
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

	Matrix4 Transform::GetMatrix() const
	{
		return mMatrix;
	}
}
