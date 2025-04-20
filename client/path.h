#pragma once
#include"vector2.h"

#include<vector>

class Path
{
public:
	Path(const std::vector<Vector2> point_list)
	{
		this->point_list = point_list;

		for (int i = 1; i < point_list.size(); i++)
		{
			float segement_now = (point_list[i] - point_list[i - 1]).length();

			segement_len_list.push_back(segement_now);

			total_length += segement_now;
		}
	}
	~Path()=default;
public:
	Vector2 get_position_from_progress(float progress)
	{
		if (progress <= 0)
			return point_list.front();
		if (progress >= 1)
			return point_list.back();

		float target_distance = progress * total_length;
		float now_distance = 0;
		for (int i = 0; i < segement_len_list.size(); i++)
		{
			now_distance += segement_len_list[i];
			if (now_distance >= target_distance)
			{
				float now_segement_progress = (target_distance - (now_distance - segement_len_list[i])) / segement_len_list[i];
				return point_list[i] + (point_list[i + 1] - point_list[i]) * now_segement_progress;
			}
		}
	}
private:
	float total_length = 0;
	std::vector<Vector2> point_list;
	std::vector<float>segement_len_list;
};

