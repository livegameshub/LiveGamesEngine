#include "Camera.h"

namespace lg
{
	glm::mat4 Camera::smOrthoMatrix;

	Camera::Camera(glm::u32 id)
		: Node(id, CAMERA)
		, mHasCustomViewSize(false)
		, mNearPlane(0.1f)
		, mFarPlane(1000.0f)
		, mFov(45.0f)
	{
	}

	Camera::Camera(glm::u32 id, glm::f32 fov, glm::f32 near, glm::f32 far)
		: Node(id, CAMERA)
		, mHasCustomViewSize(false)
		, mNearPlane(near)
		, mFarPlane(far)
		, mFov(fov)
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
			smOrthoMatrix = glm::ortho(0.0f, mViewSize.x, mViewSize.y, 0.0f, -1.0f, 1.0f);

  			mFlag -= REBUILD_ORTHO_MATRIX; 
		}

		/* update the perspective matrix */

		if (mFlag.isSet(REBUILD_PERSPECTIVE_MATRIX))
		{
			mPerspectiveMatrix = glm::perspective(mFov, mViewSize.x / mViewSize.y, mNearPlane, mFarPlane);

			mFlag -= REBUILD_PERSPECTIVE_MATRIX;
		}

		/* update the view matrix */

		if (mFlag.isSet(REBUILD_VIEW_MATRIX))
		{
			mViewMatrix = glm::inverse(mTransform.getMatrix());

 			mFlag -= REBUILD_VIEW_MATRIX;
		}
	}

	void Camera::rotateOnX(glm::f32 amount)
	{
		mTransform.rotateOnX(amount);

		mFlag += REBUILD_VIEW_MATRIX;
	}

	void Camera::rotateOnY(glm::f32 amount)
	{
		mTransform.rotateOnY(amount);

		mFlag += REBUILD_VIEW_MATRIX;
	}

	void Camera::rotateOnZ(glm::f32 amount)
	{
		mTransform.rotateOnZ(amount);

		mFlag += REBUILD_VIEW_MATRIX;
	}

	void Camera::moveForward(glm::f32 amount)
	{
		mTransform.translate(VECTOR_FORWARD * glm::inverse(mTransform.getOrientation()) * amount);

		mFlag += REBUILD_VIEW_MATRIX;
	}

	void Camera::lookAt(const glm::vec3& target)
	{
		mViewMatrix = glm::lookAt(mTransform.getPosition(), target, VECTOR_UP);
	}

	void Camera::moveAt(const glm::vec3& position)
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

	void Camera::setFov(glm::f32 value)
	{
		mFov = value;

		mFlag += REBUILD_PERSPECTIVE_MATRIX;
	}

	void Camera::setNearPlane(glm::f32 value)
	{
		mNearPlane = value;

		mFlag += REBUILD_PERSPECTIVE_MATRIX;
	}

	void Camera::setFarPlane(glm::f32 value)
	{
		mFarPlane = value;

		mFlag += REBUILD_PERSPECTIVE_MATRIX;
	}

	void Camera::setViewSize(const glm::vec2& size)
	{
		mViewSize = size;

		mFlag.add(REBUILD_ORTHO_MATRIX | REBUILD_PERSPECTIVE_MATRIX);
	}

	const glm::mat4& Camera::getOrthoMatrix()
	{
		return smOrthoMatrix;
	}

	const glm::mat4& Camera::getPerspecitiveMatrix() const
	{
		return mPerspectiveMatrix;
	}

	const glm::mat4& Camera::getViewMatrix() const
	{
		return mViewMatrix;
	}

	const glm::vec2& Camera::getViewSize() const
	{
		return mViewSize;
	}

	glm::f32 Camera::getNearPlane() const
	{
		return mNearPlane;
	}

	glm::f32 Camera::getFarPlane() const
	{
		return mFarPlane;
	}

	glm::f32 Camera::getFov() const
	{
		return mFov;
	}
}
