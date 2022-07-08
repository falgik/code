#pragma once
#include <vector>
#include <stack>
#include <thread>
#include <chrono>
#include <algorithm>
#include "SFML/Graphics.hpp"

using namespace sf;

#define SORT_DELAY 200


class SortArr
{
public:
	SortArr(); 

	void selection_sort();

	void cocktail_sort();

	void comb_sort();

	void insertion_sort();

	void merge_sort();

	void quick_sort();
	
	void std_sort();

	std::pair<int, bool> operator[](int index) const;
	
	void gen_rand_arr(int seed);

	bool sort_in_progress() const;

	int get_last_sort_time() const;

	int get_last_comparison_count() const;

	int get_last_swap_count() const;

	std::pair<int, int> get_last_comparison() const;

	std::pair<int, int> get_last_swap() const;
	
private:

	void Merge(std::vector<std::pair<int, bool>>& mas, int lowIndex, int middleIndex, int highIndex);

	void MergeSort(std::vector<std::pair<int, bool>>& mas, std::vector<std::pair<int, bool>>* sortarr, int lowIndex, int highIndex);

	bool _sort_in_progress;
	int last_sort_time;
	int last_comparison_count;
	int last_swap_count;
	std::pair<int, int> last_comparison;
	std::pair<int, int> last_swap;
	std::vector<std::pair<int, bool>> arr;
};

