#ifndef VECTOR2_H
#define VECTOR2_H

namespace pm
{
	/** \brief Very basic class to hold two dimensional vectors. */

	template<typename T>
	class Vector2
	{
		Vector2<T> operator<<(const Vector2<T>& v)
		{
		}

	public:

		/// Constructor for Vector2.
		Vector2(T x, T y)
		{
			this->x = x;
			this->y = y;
		};

		~Vector2() {};

		/// Overloaded operator +
		Vector2<T> operator + (const Vector2<T>& right)
		{
			x = x + right.x;
			y = y + right.y;
			return *this;
		}

		/// Overloaded operator -
		Vector2<T> operator - (const Vector2<T>& right)
		{
			x = x - right.x;
			y = y - right.y;
			return *this;
		}

		/// Overloaded operator *=
		Vector2<T> operator *= (Vector2<T>& left)
		{
			x *= left.x;
			y *= left.y;
			return *this;
		}

		/// Overloaded operator /=
		Vector2<T> operator /= (Vector2<T>& left)
		{
			x /= left.x;
			y /= left.y;
			return *this;
		}

		/// Overloaded operator +=
		Vector2<T> operator += (Vector2<T>& left)
		{
			x += left.x;
			y += left.y;
			return *this;
		}

		/// Overloaded operator -=
		Vector2<T> operator -= (Vector2<T>& left)
		{
			x -= left.x;
			y -= left.y;
			return *this;
		}

		T x, y;
	};
}

#endif