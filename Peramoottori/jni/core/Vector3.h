#ifndef VECTOR3_H
#define VECTOR3_H

namespace pm
{
	/** \brief Very basic class to hold three dimensional vectors. */

	template<typename T>
	class Vector3
	{
		Vector3<T> operator<<(const Vector3<T>& v)
		{
		}

	public:

		/// Constructor for Vector3.
		Vector3(T x, T y, T z)
		{
			this.x = x;
			this.y = y;
			this.z = z;
		};

		~Vector3() {};

		/// Overloading operator +
		Vector3<T> operator + (const Vector3<T>& right)
		{
			x = x + right.x;
			y = y + right.y;
			z = z + right.z;
			return *this;
		}

		/// Overloading operator -
		Vector3<T> operator - (const Vector3<T>& right)
		{
			x = x - right.x;
			y = y - right.y;
			z = z - right.z;
			return *this;
		}

		/// Overloading operator *=
		Vector3<T> operator *= (Vector3<T>& left)
		{
			x *= left.x;
			y *= left.y;
			z *= left.z;
			return *this;
		}

		/// Overloading operator /=
		Vector3<T> operator /= (Vector3<T>& left)
		{
			x /= left.x;
			y /= left.y;
			z /= left.z;
			return *this;
		}

		/// Overloading operator +=
		Vector3<T> operator += (Vector3<T>& left)
		{
			x += left.x;
			y += left.y;
			z += left.z;
			return *this;
		}

		/// Overloading operator -=
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