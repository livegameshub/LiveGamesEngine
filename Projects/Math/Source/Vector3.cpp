#include "Vector3.h"

namespace ai
{
	Vector3::Vector3()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{
	}

	Vector3::Vector3(f32 x, f32 y, f32 z)
		: x(x)
		, y(y)
		, z(z)
	{
	}

	Vector3::Vector3(f32 value)
		: x(value)
		, y(value)
		, z(value)
	{
	}

	Vector3::Vector3(const Vector3& vector)
		: x(vector.x)
		, y(vector.y)
		, z(vector.z)
	{
	}

	Vector3& Vector3::operator=(const Vector3& vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;

		return *this;
	}

	bool Vector3::operator!=(const Vector3& vector) const
	{
		return x != vector.x || y != vector.y || z != vector.z;
	}

	bool Vector3::operator==(const Vector3& vector) const
	{
		return x == vector.x && y == vector.y && z == vector.z;
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	Vector3 Vector3::operator+(const Vector3& vector) const
	{
		return Vector3(x + vector.x, y + vector.y, z + vector.z);
	}

	Vector3 Vector3::operator-(const Vector3& vector) const
	{
		return Vector3(x - vector.x, y - vector.y, z - vector.z);
	}

	Vector3 Vector3::operator*(f32 value) const
	{
		return Vector3(x * value, y * value, z * value);
	}

	Vector3 Vector3::operator/(f32 value) const
	{
		f32 one_div_value = 1.0f / value;

		return Vector3(x * one_div_value, y * one_div_value, z * one_div_value);
	}

	Vector3& Vector3::operator+=(const Vector3& vector)
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;

		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;

		return *this;
	}

	Vector3& Vector3::operator*=(f32 value)
	{
		x *= value;
		y *= value;
		z *= value;

		return *this;
	}

	Vector3& Vector3::operator/=(f32 value)
	{
		f32 one_div_value = 1.0f / value;

		x *= one_div_value;
		y *= one_div_value;
		z *= one_div_value;

		return *this;
	}

	f32 Vector3::operator*(const Vector3& vector) const
	{
		return x * vector.x + y * vector.y + z * vector.z;
	}

	void Vector3::Set(f32 x, f32 y, f32 z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Vector3::Normalize()
	{
		f32 magnitude_square = x * x + y * y + z * z;

		if (magnitude_square > 0.0f)
		{
			f32 one_div_magnitude = 1.0f / std::sqrt(magnitude_square);

			x *= one_div_magnitude;
			y *= one_div_magnitude;
			z *= one_div_magnitude;
		}
	}

	void Vector3::Zero()
	{
		x = y = z = 0.0f;
	}

	f32 Vector3::Magnitude() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	f32 Vector3::Distance(const Vector3& b) const
	{
		f32 dist_x = x - b.x;
		f32 dist_y = y - b.y;
		f32 dist_z = z - b.z;

		return std::sqrt(dist_x * dist_x + dist_y * dist_y + dist_z * dist_z);
	}

	Vector3 Vector3::CrossProduct(const Vector3& vector) const
	{
		return Vector3(y * vector.z - z * vector.y,
					   z * vector.x - x * vector.z,
					   x * vector.y - y * vector.x);
	}
}
