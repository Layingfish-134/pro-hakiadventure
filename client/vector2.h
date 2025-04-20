#pragma once
#pragma once
#include<cmath>

class Vector2
{
public:
	Vector2() = default;
	~Vector2() = default;
	Vector2(float in_x, float in_y) :x(in_x), y(in_y)
	{
	}
public:
	float x;
	float y;
public:
	Vector2 operator+(const Vector2& other)const
	{
		return Vector2(this->x + other.x, this->y + other.y);
	}

	void operator+=(const Vector2& other)
	{
		this->x += other.x;
		this->y += other.y;
	}

	Vector2 operator-(const Vector2& other)const
	{
		return Vector2(this->x - other.x, this->y - other.y);
	}

	void operator-=(const Vector2& other)
	{
		this->x -= other.x;
		this->y -= other.y;
	}

	float operator*(const Vector2& other) const
	{
		return this->x * other.x + this->y * other.y;
	}

	Vector2 operator*(float k) const
	{
		return Vector2(k * this->x, k * this->y);
	}

	void operator*=(float k)
	{
		this->x *= k;
		this->y *= k;
	}

	Vector2 operator/(float k) const
	{
		return Vector2(this->x/k, this->y/k);
	}

	float length()
	{
		return sqrt(this->x * this->x + this->y * this->y);
	}

	Vector2 normalize()
	{
		float length = this->length();
		if (length == 0)
			return Vector2(0, 0);
		return Vector2(x / length, y / length);
	}

	bool approx(const Vector2& target)
	{
		return (*this - target).length() <= 0.0001f;
	}
};
