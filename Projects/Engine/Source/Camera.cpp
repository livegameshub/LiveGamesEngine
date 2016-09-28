#include "Camera.h"

namespace ai
{
	glm::mat4 Camera::smOrthoMatrix;

	Camera::Camera(glm::u32 id)
		: BasicNode(id, CAMERA_NODE)
		, mHasCustomViewSize(false)
		, mNearPlane(0.1f)
		, mFarPlane(1000.0f)
		, mFov(45.0f)
	{
	}

	Camera::Camera(glm::u32 id, glm::f32 fov, glm::f32 near, glm::f32 far)
		: BasicNode(id, CAMERA_NODE)
		, mHasCustomViewSize(false)
		, mNearPlane(near)
		, mFarPlane(far)
		, mFov(fov)
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::Update()
	{
		BasicNode::Update();

		/* update the ortho matrix (for the 2d or GUI) */

		if (mFlag.IsSet(CAMERA_NEW_ORTHO_MATRIX))
		{
			smOrthoMatrix = glm::ortho(0.0f, mViewSize.x, mViewSize.y, 0.0f, -1.0f, 1.0f);

			mFlag -= CAMERA_NEW_ORTHO_MATRIX;
		}

		/* update the perspective matrix */

		if (mFlag.IsSet(CAMERA_NEW_PERSPECTIVE_MATRIX))
		{
			mPerspectiveMatrix = glm::perspective(mFov, mViewSize.x / mViewSize.y, mNearPlane, mFarPlane);

			mFlag -= CAMERA_NEW_PERSPECTIVE_MATRIX;
		}

		/* update the view matrix */

		if (mFlag.IsSet(CAMERA_NEW_VIEW_MATRIX))
		{
			mViewMatrix = glm::inverse(mTransform.GetMatrix());

			mFlag -= CAMERA_NEW_VIEW_MATRIX;
		}
	}

	void Camera::RotateOnX(glm::f32 amount)
	{
		mTransform.RotateOnX(amount);

		mFlag += CAMERA_NEW_VIEW_MATRIX;
	}

	void Camera::RotateOnY(glm::f32 amount)
	{
		mTransform.RotateOnY(amount);

		mFlag += CAMERA_NEW_VIEW_MATRIX;
	}

	void Camera::RotateOnZ(glm::f32 amount)
	{
		mTransform.RotateOnZ(amount);

		mFlag += CAMERA_NEW_VIEW_MATRIX;
	}

	void Camera::MoveForward(glm::f32 amount)
	{
		mTransform.Translate(VECTOR_FORWARD * glm::inverse(mTransform.GetOrientation()) * amount);

		mFlag += CAMERA_NEW_VIEW_MATRIX;
	}

	void Camera::LookAt(const glm::vec3& target)
	{
		mViewMatrix = glm::lookAt(mTransform.GetPosition(), target, VECTOR_UP);
	}

	void Camera::MoveAt(const glm::vec3& position)
	{
		mTransform.SetPosition(position);

		mFlag += CAMERA_NEW_VIEW_MATRIX;
	}

	bool Camera::HasCustomViewSize() const
	{
		return mHasCustomViewSize;
	}

	void Camera::HasCustomViewSize(bool value)
	{
		mHasCustomViewSize = value;
	}

	void Camera::SetFov(glm::f32 value)
	{
		mFov = value;

		mFlag += CAMERA_NEW_PERSPECTIVE_MATRIX;
	}

	void Camera::SetNearPlane(glm::f32 value)
	{
		mNearPlane = value;

		mFlag += CAMERA_NEW_PERSPECTIVE_MATRIX;
	}

	void Camera::SetFarPlane(glm::f32 value)
	{
		mFarPlane = value;

		mFlag += CAMERA_NEW_PERSPECTIVE_MATRIX;
	}

	void Camera::SetViewSize(const glm::vec2& size)
	{
		mViewSize = size;

		mFlag.Add(CAMERA_NEW_ORTHO_MATRIX | CAMERA_NEW_PERSPECTIVE_MATRIX);
	}

	const glm::mat4& Camera::GetOrthoMatrix()
	{
		return smOrthoMatrix;
	}

	const glm::mat4& Camera::GetPerspecitiveMatrix() const
	{
		return mPerspectiveMatrix;
	}

	const glm::mat4& Camera::GetViewMatrix() const
	{
		return mViewMatrix;
	}

	const glm::vec2& Camera::GetViewSize() const
	{
		return mViewSize;
	}

	glm::f32 Camera::GetNearPlane() const
	{
		return mNearPlane;
	}

	glm::f32 Camera::GetFarPlane() const
	{
		return mFarPlane;
	}

	glm::f32 Camera::GetFov() const
	{
		return mFov;
	}
}
