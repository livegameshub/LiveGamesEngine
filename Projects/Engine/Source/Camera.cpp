#include "Camera.h"

namespace lg
{
	mat4 Camera::smOrthoMatrix;

	Camera::Camera(u32 id, i32 type)
		: Node(id, type)
		, mHasCustomSize(false)
		, mNearPlane(0.1f)
		, mFarPlane(1000.0f)
		, mFov(45.0f)
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::update()
	{
		Node::update();

		/* update the ortho matrix (for the 2d or GUI) */

		if (mFlag.isSet(ORTHO_MATRIX))
		{
			smOrthoMatrix = ortho(0.0f, mSize.x, mSize.y, 0.0f, -1.0f, 1.0f);

  			mFlag -= ORTHO_MATRIX; 
		}

		/* update the perspective matrix */

		if (mFlag.isSet(PERSPECTIVE_MATRIX))
		{
			mPerspectiveMatrix = perspective(mFov, mSize.x / mSize.y, mNearPlane, mFarPlane);

			mFlag -= PERSPECTIVE_MATRIX;
		}

		/* update the view matrix */

		if (mFlag.isSet(VIEW_MATRIX))
		{
			mViewMatrix = inverse(mTransform.getMatrix());

 			mFlag -= VIEW_MATRIX;
		}
	}

	void Camera::rotateOnX(f32 amount)
	{
		mTransform.rotateOnX(amount);

		mFlag += VIEW_MATRIX;
	}

	void Camera::rotateOnY(f32 amount)
	{
		mTransform.rotateOnY(amount);

		mFlag += VIEW_MATRIX;
	}

	void Camera::rotateOnZ(f32 amount)
	{
		mTransform.rotateOnZ(amount);

		mFlag += VIEW_MATRIX;
	}

	void Camera::moveForward(f32 amount)
	{
		mTransform.translate(VECTOR_FORWARD * inverse(mTransform.getOrientation()) * amount);

		mFlag += VIEW_MATRIX;
	}

	void Camera::lookAt(const vec3& target)
	{
		mViewMatrix = glm::lookAt(mTransform.getPosition(), target, VECTOR_UP);
	}

	void Camera::moveAt(const vec3& position)
	{
		mTransform.setPosition(position);

		mFlag += VIEW_MATRIX;
	}

	bool Camera::hasCustomSize() const
	{
		return mHasCustomSize;
	}

	void Camera::hasCustomSize(bool value)
	{
		mHasCustomSize = value;
	}

	void Camera::setFov(f32 value)
	{
		mFov = value;

		mFlag += PERSPECTIVE_MATRIX;
	}

	void Camera::setNearPlane(f32 value)
	{
		mNearPlane = value;

		mFlag += PERSPECTIVE_MATRIX;
	}

	void Camera::setFarPlane(f32 value)
	{
		mFarPlane = value;

		mFlag += PERSPECTIVE_MATRIX;
	}

	void Camera::setSize(const vec2& size)
	{
		mSize = size;

		mFlag.add(ORTHO_MATRIX | PERSPECTIVE_MATRIX);
	}

	const mat4& Camera::getOrthoMatrix()
	{
		return smOrthoMatrix;
	}

	const mat4& Camera::getPerspecitiveMatrix() const
	{
		return mPerspectiveMatrix;
	}

	const mat4& Camera::getViewMatrix() const
	{
		return mViewMatrix;
	}

	const vec2& Camera::getSize() const
	{
		return mSize;
	}

	f32 Camera::getNearPlane() const
	{
		return mNearPlane;
	}

	f32 Camera::getFarPlane() const
	{
		return mFarPlane;
	}

	f32 Camera::getFov() const
	{
		return mFov;
	}
}
