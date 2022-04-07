#pragma once
#include <cmath>

struct Vector3 {
	float x;
	float y;
	float z;

	//added this. inlined because simple
	Vector3 operator+(const Vector3& v)
	{
		Vector3 added;
		added.x = x + v.x;
		added.y = y + v.y;
		added.z = z + v.z;

		return added;
	}

	Vector3& operator +=(const Vector3& v)
	{
		x = x + v.x;
		y = y + v.y;
		z = z + v.z;

		return *this;
	}
	Vector3 operator-(const Vector3& v)
	{
		Vector3 sub;
		sub.x = x - v.x;
		sub.y = y - v.y;
		sub.z = z - v.z;

		return sub;
	}
	Vector3 operator*(float scale)
	{
		Vector3 velocity;
		velocity.x = x*scale;
		velocity.y = y*scale;
		velocity.z = z*scale;

		return velocity;
	}
	Vector3& normalize()
	{
		float magSqrd = x*x + y*y + z*z;
		float mag = sqrt(magSqrd);
		x /= mag;
		y /= mag;
		z /= mag;

		return *this;
	}

	float mag()
	{
		float magSqrd = x*x + y*y + z*z;
		float mag = sqrt(magSqrd);

		return mag;
	}

	Vector3 conjugate()
	{
		Vector3 conj = {-x, -y, -z};
	}
};