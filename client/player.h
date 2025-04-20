#pragma once
#include"animation.h"

class Player
{
public:
	Player(
		Atlas* atlas_idle_left,
		Atlas* atlas_idle_right,
		Atlas* atlas_idle_up,
		Atlas* atlas_idle_down,
		Atlas* atlas_run_left,
		Atlas* atlas_run_right,
		Atlas* atlas_run_up,
		Atlas* atlas_run_down)
	{
		animation_idle_down.set_loop(true);
		animation_idle_down.set_interval(0.1f);
		animation_idle_down.add_frame(atlas_idle_down);

		animation_idle_up.set_loop(true);
		animation_idle_up.set_interval(0.1f);
		animation_idle_up.add_frame(atlas_idle_up);

		animation_idle_left.set_loop(true);
		animation_idle_left.set_interval(0.1f);
		animation_idle_left.add_frame(atlas_idle_left);

		animation_idle_right.set_loop(true);
		animation_idle_right.set_interval(0.1f);
		animation_idle_right.add_frame(atlas_idle_right);

		animation_run_down.set_loop(true);
		animation_run_down.set_interval(0.1f);
		animation_run_down.add_frame(atlas_run_down);

		animation_run_up.set_loop(true);
		animation_run_up.set_interval(0.1f);
		animation_run_up.add_frame(atlas_run_up);

		animation_run_left.set_loop(true);
		animation_run_left.set_interval(0.1f);
		animation_run_left.add_frame(atlas_run_left);

		animation_run_right.set_loop(true);
		animation_run_right.set_interval(0.1f);
		animation_run_right.add_frame(atlas_run_right);

	}
	~Player()=default;

public:
	void on_update(float delta)
	{
		if (!cur_position.approx(tar_position))
			velocity = (tar_position - cur_position).normalize() * SPEED_RUN;
		else
			velocity = Vector2(0, 0);

		if ((velocity * delta).length() > (tar_position - cur_position).length())
			cur_position = tar_position;
		else
			cur_position += velocity * delta;

		if (velocity.approx(Vector2(0, 0)))
		{
			switch (facing)
			{
			case Player::Facing::Up:
				cur_animation = &animation_idle_up;
				break;
			case Player::Facing::Down:
				cur_animation = &animation_idle_down;
				break;
			case Player::Facing::Left:
				cur_animation = &animation_idle_left;
				break;
			case Player::Facing::Right:
				cur_animation = &animation_idle_right;
				break;
			default:
				break;
			}
		}
		else
		{
			if (fabs(velocity.x) >= 0.0001f)
				facing = (velocity.x > 0) ? Facing::Right : Facing::Left;
			if (fabs(velocity.y) >= 0.0001f)
				facing = (velocity.y > 0) ? Facing::Down : Facing::Up;	

			switch (facing)
			{
			case Player::Facing::Up:
				cur_animation = &animation_run_up;
				break;
			case Player::Facing::Down:
				cur_animation = &animation_run_down;
				break;
			case Player::Facing::Left:
				cur_animation = &animation_run_left;
				break;
			case Player::Facing::Right:
				cur_animation = &animation_run_right;
				break;
			default:
				break;
			}
		}

		if (!cur_animation)
			return;
		cur_animation->set_position(cur_position);
		cur_animation->on_update(delta);
	}

	void on_render(const Camera& camera)
	{
		if (!cur_animation)
			return;
		cur_animation->on_render(camera);
	}

	void set_cur_position(const Vector2& position)
	{
		cur_position = position;
	}

	const Vector2& get_position()const
	{
		return cur_position;
	}

	void set_tar_position(const Vector2& target)
	{
		tar_position = target;
	}

public:
	enum class Facing
	{
		Up,Down,Left,Right
	};
private:
	const float SPEED_RUN = 100.0f;
private:
	Vector2 cur_position;
	Vector2 tar_position;
	Vector2 velocity;

	Animation animation_idle_left;
	Animation animation_idle_right;
	Animation animation_idle_up;
	Animation animation_idle_down;

	Animation animation_run_left;
	Animation animation_run_right;
	Animation animation_run_up;
	Animation animation_run_down;

	Animation* cur_animation = nullptr;
	Facing facing = Facing::Down;
};
