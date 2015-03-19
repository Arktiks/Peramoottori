#ifndef VECTOR2_H
#define VECTOR2_H

template<typename T>
class Vector2
{
	friend std::ostream operator<<(std::ostream& os, const Vector2<T>& v)
	{
		os << v.x << " , " << v.y,;
		return os;
	}

public:
	
	Vector2(T x, T y)
	{
		this.x = x;
		this.y = y;
	};
	~Vector2();

	Vector2<T> operator + (const Vector2<T>& right)
	{
		x = x + right.x;
		y = y + right.y;
		return *this;
	}
	Vector2<T> operator - (const Vector2<T>& right)
	{
		x = x - right.x;
		y = y - right.y;
		return *this;
	}
	Vector2<T> operator *= (Vector2<T>& left)
	{
		x *= left.x;
		y *= left.y;
		return *this;
	}
	Vector2<T> operator /= (Vector2<T>& left)
	{
		x /= left.x;
		y /= left.y;
		return *this;
	}
	Vector2<T> operator += (Vector2<T>& left)
	{
		x += left.x;
		y += left.y;
		return *this;
	}
	Vector2<T> operator -= (Vector2<T>& left)
	{
		x -= left.x;
		y -= left.y;
		return *this;
	}

	T x, y;

};
#endif
