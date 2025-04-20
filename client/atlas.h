#pragma once

#include<graphics.h>
#include<vector>

class Atlas
{
public:
	Atlas()=default;
	~Atlas()=default;

public:
	void load(LPCTSTR path_template, int num)
	{
		img_list.clear();
		img_list.resize(num);

		TCHAR path_flie[256];

		for (int i = 0; i < num; i++)
		{
			_stprintf_s(path_flie,path_template,i+1);
			loadimage(&img_list[i], path_flie);
		}
	}

	void clear()
	{
		img_list.clear();
	}

	int get_size() const
	{
		return img_list.size();
	}

	IMAGE* get_image(int index)
	{
		if (index < 0 || index >= get_size())
		{
			return nullptr;
		}

		return &img_list[index];
	}

	void add_image(const IMAGE& img)
	{
		img_list.push_back(img);
	}
private:
	std::vector<IMAGE> img_list;

};
