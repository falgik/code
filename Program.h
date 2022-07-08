#pragma once
#include "SFML/Graphics.hpp"
#include "Sorter.h"
#include "Button.h"
#include <iostream>

using namespace sf;

class Program
{
public:

	void init(Font& font)
	{
		arrays.resize(7);

		int sd = time(0);
		for (int i = 0; i < arrays.size(); i++)
			arrays[i].gen_rand_arr(sd);

		tile.setSize(Vector2f(40,40));
		tile.setFillColor(Color(127, 127, 127));
		tile.setOutlineThickness(3);
		num.setCharacterSize(20);
		num.setFont(font);
		label.setCharacterSize(20);
		label.setFont(font);

		btn_sort = Button(0, 830, 690, 50, Color(77, 77, 77), Color(95, 95, 95), Color(120, 120, 120), font, L"Запуск сортування");
		btn_genarr = Button(690, 830, 690, 50, Color(77, 77, 77), Color(95, 95, 95), Color(120, 120, 120), font, L"Новий массив");
	}

	void update(const Vector2f& curPos, const bool click)
	{
		btn_sort.update(curPos, click);
		btn_genarr.update(curPos, click);

		if (!arrays[0].sort_in_progress() &&
			!arrays[1].sort_in_progress() && 
			!arrays[2].sort_in_progress() && 
			!arrays[3].sort_in_progress() && 
			!arrays[4].sort_in_progress() && 
			!arrays[5].sort_in_progress() && 
			!arrays[6].sort_in_progress()  )
		{
			if (btn_sort.isClick())
			{
				arrays[0].selection_sort();
				arrays[1].cocktail_sort();
				arrays[2].comb_sort();
				arrays[3].insertion_sort();
				arrays[4].merge_sort();
				arrays[5].quick_sort();
				arrays[6].std_sort();
			}
			else if (btn_genarr.isClick())
			{
				int sd = time(0);
				for (int i = 0; i < arrays.size(); i++)
					arrays[i].gen_rand_arr(sd);
			}
		}

		btn_genarr.isClick();
		btn_sort.isClick();
	}

	void draw(RenderWindow& window)
	{		
		for (int i = 0; i < arrays.size(); i++)
		{
			switch (i)
			{
			case 0:
				label.setString(L"Сортування вибором");
				break;
			case 1:
				label.setString(L"Шейкерне сортування");
				break;
			case 2:
				label.setString(L"Сортування гребінцем");
				break;
			case 3:
				label.setString(L"Сортування вставками");
				break;
			case 4:
				label.setString(L"Сортування злиттям");
				break;
			case 5:
				label.setString(L"Швидке сортування");
				break;
			case 6:
				label.setString(L"std::sort()");
				break;
			}

			label.setPosition(0, 10 + i * 120);
			window.draw(label);

			label.move(300, 0);
			label.setString(L"Кількість порівнянь " + std::to_wstring(arrays[i].get_last_comparison_count()));
			window.draw(label);

			label.move(300, 0);
			label.setString(L"Кількість переміщень " + std::to_wstring(arrays[i].get_last_swap_count()));
			window.draw(label);

			label.move(300, 0);
			label.setString(L"Затрачений час " + std::to_wstring(arrays[i].get_last_sort_time()) + L" мкс" );
			window.draw(label);

			drawArray(window, arrays[i], 50 + i * 120);


			btn_sort.draw(window);
			btn_genarr.draw(window);
		}	
	}

private:

	void drawArray(RenderWindow& window, SortArr& arr, int y)
	{
		for (int i = 0; i < 30; i++)
		{
			tile.setPosition(3 + 46 * i, y);
			num.setString(std::to_string(arr[i].first));
			num.setPosition(7 + 46 * i, y + 6);

			if (arr.get_last_swap().first == i || arr.get_last_swap().second == i)
				tile.setOutlineColor(Color(0, 255, 0));
			else if (arr.get_last_comparison().first == i || arr.get_last_comparison().second == i)
				tile.setOutlineColor(Color(255, 0, 0));
			else
				tile.setOutlineColor(Color(140, 140, 140));

			if (arr[i].second)
				num.setFillColor(Color(0,255,0));
			else
				num.setFillColor(Color(255,255,255));

			window.draw(tile);
			window.draw(num);
		}
	}
	 
	std::vector<SortArr> arrays;
	RectangleShape tile;
	Text num, label;
	Button btn_sort;
	Button btn_genarr;
};

