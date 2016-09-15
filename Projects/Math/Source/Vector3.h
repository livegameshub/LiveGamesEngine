#ifndef _VECTOR_3_H_
#define _VECTOR_3_H_

#include "MathUtil.h"

namespace ai
{
	struct MATH_API Vector3
	{
		Vector3();
		Vector3(f32 x, f32 y, f32 z);
		Vector3(f32 value);

		Vector3(const Vector3& vector);
		Vector3& operator=(const Vector3& vector);

		inline bool operator!=(const Vector3& vector) const;
		inline bool operator==(const Vector3& vector) const;

		inline Vector3 operator-() const;

		inline Vector3 operator+(const Vector3& vector) const;
		inline Vector3 operator-(const Vector3& vector) const;

		inline Vector3 operator*(f32 value) const;
		inline Vector3 operator/(f32 value) const;

		inline Vector3& operator+=(const Vector3& vector);
		inline Vector3& operator-=(const Vector3& vector);

		inline Vector3& operator*=(f32 value);
		inline Vector3& operator/=(f32 value);

		inline Vector3 CrossProduct(const Vector3& vector) const;

		/* dot product */
		inline f32 operator*(const Vector3& vector) const;

		inline f32 Distance(const Vector3& b) const;
		inline f32 Magnitude() const;

		inline void Set(f32 x, f32 y, f32 z);
		inline void Normalize();
		inline void Zero();

		/* members */

		f32 x;
		f32 y;
		f32 z;
	};
}

#endif
