#include "CameraNode.h"

namespace ai
{
	glm::mat4 CameraNode::smOrthoMatrix;

	CameraNode::CameraNode(glm::u32 id)
		: BasicNode(id, CAMERA_NODE)
		, mHasCustomViewSize(false)
		, mNearPlane(0.1f)
		, mFarPlane(1000.0f)
		, mFov(45.0f)
	{
	}

	CameraNode::CameraNode(glm::u32 id, glm::f32 fov, glm::f32 near, glm::f32 far)
		: BasicNode(id, CAMERA_NODE)
		, mHasCustomViewSize(false)
		, mNearPlane(near)
		, mFarPlane(far)
		, mFov(fov)
	{
	}

	CameraNode::~CameraNode()
	{
	}

	void CameraNode::update()
	{
		BasicNode::update();

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

	void CameraNode::rotateOnX(glm::f32 amount)
	{
		mTransform.RotateOnX(amount);

		mFlag += CAMERA_NEW_VIEW_MATRIX;
	}

	void CameraNode::rotateOnY(glm::f32 amount)
	{
		mTransform.RotateOnY(amount);

		mFlag += CAMERA_NEW_VIEW_MATRIX;
	}

	void CameraNode::rotateOnZ(glm::f32 amount)
	{
		mTransform.RotateOnZ(amount);

		mFlag += CAMERA_NEW_VIEW_MATRIX;
	}

	void CameraNode::moveForward(glm::f32 amount)
	{
		mTransform.translate(VECTOR_FORWARD * glm::inverse(mTransform.GetOrientation()) * amount);

		mFlag += CAMERA_NEW_VIEW_MATRIX;
	}

	void CameraNode::lookAt(const glm::vec3& target)
	{
		mViewMatrix = glm::lookAt(mTransform.GetPosition(), target, VECTOR_UP);
	}

	void CameraNode::moveAt(const glm::vec3& position)
	{
		mTransform.SetPosition(position);

		mFlag += CAMERA_NEW_VIEW_MATRIX;
	}

	bool CameraNode::hasCustomViewSize() const
	{
		return mHasCustomViewSize;
	}

	void CameraNode::hasCustomViewSize(bool value)
	{
		mHasCustomViewSize = value;
	}

	void CameraNode::setFov(glm::f32 value)
	{
		mFov = value;

		mFlag += CAMERA_NEW_PERSPECTIVE_MATRIX;
	}

	void CameraNode::setNearPlane(glm::f32 value)
	{
		mNearPlane = value;

		mFlag += CAMERA_NEW_PERSPECTIVE_MATRIX;
	}

	void CameraNode::setFarPlane(glm::f32 value)
	{
		mFarPlane = value;

		mFlag += CAMERA_NEW_PERSPECTIVE_MATRIX;
	}

	void CameraNode::setViewSize(const glm::vec2& size)
	{
		mViewSize = size;

		mFlag.Add(CAMERA_NEW_ORTHO_MATRIX | CAMERA_NEW_PERSPECTIVE_MATRIX);
	}

	const glm::mat4& CameraNode::getOrthoMatrix()
	{
		return smOrthoMatrix;
	}

	const glm::mat4& CameraNode::getPerspecitiveMatrix() const
	{
		return mPerspectiveMatrix;
	}

	const glm::mat4& CameraNode::getViewMatrix() const
	{
		return mViewMatrix;
	}

	const glm::vec2& CameraNode::getViewSize() const
	{
		return mViewSize;
	}

	glm::f32 CameraNode::getNearPlane() const
	{
		return mNearPlane;
	}

	glm::f32 CameraNode::getFarPlane() const
	{
		return mFarPlane;
	}

	glm::f32 CameraNode::getFov() const
	{
		return mFov;
	}
}
