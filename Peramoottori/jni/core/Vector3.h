#ifndef VECTOR2_H
#define VECTOR2_H
#include <iostream>
template<typename T>
class Vector3
{
	friend std::ostream operator<<(std::ostream& os , const Vector3<T>& v)
	{
		os << v.x << " , " << v.y, << " , " << v.z;
		return os;
	}

public:
	
	Vector3(T x, T y, T z)
	{
		this.x = x;
		this.y = y;
		this.z = z;
	};
	~Vector3();

	Vector3<T> operator + (const Vector3<T>& right)
	{
		x = x + right.x;
		y = y + right.y;
		z = z + right.z;
		return *this;
	}
	Vector3<T> operator - (const Vector3<T>& right)
	{
		x = x - right.x;
		y = y - right.y;
		z = z - right.z;
		return *this;
	}
	Vector3<T> operator *= (Vector3<T>& left)
	{
		x *= left.x;
		y *= left.y;
		z *= left.z;
		return *this;
	}
	Vector3<T> operator /= (Vector3<T>& left)
	{
		x /= left.x;
		y /= left.y;
		z /= left.z;
		return *this;
	}
	Vector3<T> operator += (Vector3<T>& left)
	{
		x += left.x;
		y += left.y;
		z += left.z;
		return *this;
	}
	Vector3<T> operator -= (Vector3<T>& left)
	{
		x -= left.x;
		y -= left.y;
		z -= left.y;
		return *this;
	}

	T x, y, z;

};
#endif
