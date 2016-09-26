#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "BasicNode.h"

namespace ai
{
	class ENGINE_API Camera : public BasicNode
	{
	public:
		enum CameraFlag : glm::u32
		{
			CAMERA_NEW_VIEW = 1,
			CAMERA_NEW_ORTHO_MATRIX = 2,
			CAMERA_NEW_PERSPECTIVE = 4
		};

		Camera(glm::u32 id);
		Camera(glm::u32 id, glm::f32 fov, glm::f32 near, glm::f32 far);

		~Camera();

		void Update() override;

	private:
		bool mHasCustomViewSize;

		static glm::mat4 smOrthoMatrix;

		glm::mat4 mPerspectiveMatrix;
		glm::mat4 mViewMatrix;

		glm::vec2 mViewSize;

		glm::f32 mNearPlane;
		glm::f32 mFarPlane;
		glm::f32 mFov;
	};
}

#endif
