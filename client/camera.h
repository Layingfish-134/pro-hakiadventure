#pragma once
#include"vector2.h"

class Camera
{
public:
	Camera()=default;
	~Camera()=default;

public:
	void set_pos(const Vector2 pos)
	{
		position = pos;

	}

	void set_size(const Vector2 size)
	{
		this->size = size;
	}

	const Vector2& get_pos() const
	{
		return position;
	}

	const Vector2& get_size() const
	{
		return size;
	}

	void look_at(const Vector2& target)
	{
		position = target - size / 2.0f;

	}
private:
	Vector2 size;
	Vector2 position;
};
