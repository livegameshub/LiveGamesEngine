#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Node.h"

namespace lg
{
	class ENGINE_API Camera : public Node
	{
	public:
		enum CameraFlag : u32
		{
			REBUILD_VIEW_MATRIX = 1,
			REBUILD_ORTHO_MATRIX = 2,
			REBUILD_PERSPECTIVE_MATRIX = 4
		};

		Camera(u32 id, i32 type);
		~Camera();

		void update() override;

		void rotateOnX(f32 amount);
		void rotateOnY(f32 amount);
		void rotateOnZ(f32 amount);
		void moveForward(f32 amount);

		void lookAt(const vec3& target);
		void moveAt(const vec3& position);
		
		bool hasCustomViewSize() const;
		void hasCustomViewSize(bool value);

		void setFov(f32 value);
		void setNearPlane(f32 value);
		void setFarPlane(f32 value);
		void setViewSize(const vec2& size);

		static const mat4& getOrthoMatrix();
		const mat4& getPerspecitiveMatrix() const;
		const mat4& getViewMatrix() const;

		const vec2& getViewSize() const;
		f32 getNearPlane() const;
		f32 getFarPlane() const;
		f32 getFov() const;

	private:
		bool mHasCustomViewSize;

		static mat4 smOrthoMatrix;

		mat4 mPerspectiveMatrix;
		mat4 mViewMatrix;

		vec2 mViewSize;

		f32 mNearPlane;
		f32 mFarPlane;
		f32 mFov;
	};
}

#endif // _CAMERA_H_
