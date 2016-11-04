#include "Camera.h"

namespace lg
{
	mat4 Camera::smOrthoMatrix;

	Camera::Camera(u32 id, i32 type)
		: Node(id, type)
		, mHasCustomViewSize(false)
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

		if (mFlag.isSet(REBUILD_ORTHO_MATRIX))
		{
			smOrthoMatrix = ortho(0.0f, mViewSize.x, mViewSize.y, 0.0f, -1.0f, 1.0f);

  			mFlag -= REBUILD_ORTHO_MATRIX; 
		}

		/* update the perspective matrix */

		if (mFlag.isSet(REBUILD_PERSPECTIVE_MATRIX))
		{
			mPerspectiveMatrix = perspective(mFov, mViewSize.x / mViewSize.y, mNearPlane, mFarPlane);

			mFlag -= REBUILD_PERSPECTIVE_MATRIX;
		}

		/* update the view matrix */

		if (mFlag.isSet(REBUILD_VIEW_MATRIX))
		{
			mViewMatrix = inverse(mTransform.getMatrix());

 			mFlag -= REBUILD_VIEW_MATRIX;
		}
	}

	void Camera::rotateOnX(f32 amount)
	{
		mTransform.rotateOnX(amount);

		mFlag += REBUILD_VIEW_MATRIX;
	}

	void Camera::rotateOnY(f32 amount)
	{
		mTransform.rotateOnY(amount);

		mFlag += REBUILD_VIEW_MATRIX;
	}

	void Camera::rotateOnZ(f32 amount)
	{
		mTransform.rotateOnZ(amount);

		mFlag += REBUILD_VIEW_MATRIX;
	}

	void Camera::moveForward(f32 amount)
	{
		mTransform.translate(VECTOR_FORWARD * inverse(mTransform.getOrientation()) * amount);

		mFlag += REBUILD_VIEW_MATRIX;
	}

	void Camera::lookAt(const vec3& target)
	{
		mViewMatrix = glm::lookAt(mTransform.getPosition(), target, VECTOR_UP);
	}

	void Camera::moveAt(const vec3& position)
	{
		mTransform.setPosition(position);

		mFlag += REBUILD_VIEW_MATRIX;
	}

	bool Camera::hasCustomViewSize() const
	{
		return mHasCustomViewSize;
	}

	void Camera::hasCustomViewSize(bool value)
	{
		mHasCustomViewSize = value;
	}

	void Camera::setFov(f32 value)
	{
		mFov = value;

		mFlag += REBUILD_PERSPECTIVE_MATRIX;
	}

	void Camera::setNearPlane(f32 value)
	{
		mNearPlane = value;

		mFlag += REBUILD_PERSPECTIVE_MATRIX;
	}

	void Camera::setFarPlane(f32 value)
	{
		mFarPlane = value;

		mFlag += REBUILD_PERSPECTIVE_MATRIX;
	}

	void Camera::setViewSize(const vec2& size)
	{
		mViewSize = size;

		mFlag.add(REBUILD_ORTHO_MATRIX | REBUILD_PERSPECTIVE_MATRIX);
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

	const vec2& Camera::getViewSize() const
	{
		return mViewSize;
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
