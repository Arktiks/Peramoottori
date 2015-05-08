#ifndef VECTOR2_H
#define VECTOR2_H
#include <iostream>



namespace pm
{
	/**
	*Engines own Vector3 that can be used to make fast 2 place vectors
	*/
	template<typename T>
	class Vector3
	{
		Vector3<T> operator<<(const Vector2<T>& v)
		{
			DEBUG_INFO(("&f, &f, &f", v.x, v.y, v.z));
		}

	public:
		/// constructor for Vector 
		Vector3(T x, T y, T z)
		{
			this.x = x;
			this.y = y;
			this.z = z;
		};
		~Vector3();
		/// overloading operator +
		Vector3<T> operator + (const Vector3<T>& right)
		{
			x = x + right.x;
			y = y + right.y;
			z = z + right.z;
			return *this;
		}
		/// overloading operator -
		Vector3<T> operator - (const Vector3<T>& right)
		{
			x = x - right.x;
			y = y - right.y;
			z = z - right.z;
			return *this;
		}
		/// overloading operator *=
		Vector3<T> operator *= (Vector3<T>& left)
		{
			x *= left.x;
			y *= left.y;
			z *= left.z;
			return *this;
		}
		/// overloading operator /=
		Vector3<T> operator /= (Vector3<T>& left)
		{
			x /= left.x;
			y /= left.y;
			z /= left.z;
			return *this;
		}
		/// overloading operator +=
		Vector3<T> operator += (Vector3<T>& left)
		{
			x += left.x;
			y += left.y;
			z += left.z;
			return *this;
		}
		/// overloading operator -=
		Vector3<T> operator -= (Vector3<T>& left)
		{
			x -= left.x;
			y -= left.y;
			z -= left.y;
			return *this;
		}

		T x, y, z;

	};
}
#endif
