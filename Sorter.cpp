#include "Sorter.h"

SortArr::SortArr() :
	_sort_in_progress(false),
	last_sort_time(0),
	last_comparison_count(0),
	last_swap_count(0),
	last_comparison(-1, -1),
	last_swap(-1, -1)
{
	arr.resize(30, std::make_pair(0, false));
}

void SortArr::selection_sort()
{
	_sort_in_progress = true;
	last_sort_time = 0;
	last_comparison_count = 0;
	last_swap_count = 0;

	std::thread th([this]() {

		auto copyarr = arr;
		Clock timer;
		for (auto it = copyarr.end(); it != copyarr.begin(); std::swap((*(--it)).first, (*std::max_element(copyarr.begin(), it)).first));
		last_sort_time = timer.getElapsedTime().asMicroseconds();


		for (int i = arr.size() - 1; i >= 0; i--)
		{
			last_swap.first = -1;
			last_swap.second = -1;
			int max = i;
			for (int j = 0; j < i; j++)
			{
				if (arr[j].first > arr[max].first)
					max = j;

				last_comparison_count++;
				last_comparison.first = j;
				last_comparison.second = max;
				std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
			}

			last_comparison.first = -1;
			last_comparison.second = -1;
			std::swap(arr[i].first, arr[max].first);
			arr[i].second = true;
			last_swap_count++;
			last_swap.first = i;
			last_swap.second = max;
			std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
		}

		last_swap.first = -1;
		last_swap.second = -1;
		last_comparison.first = -1;
		last_comparison.second = -1;

		_sort_in_progress = false;

		});

	th.detach();
}

void SortArr::cocktail_sort()
{
	_sort_in_progress = true;
	last_sort_time = 0;
	last_comparison_count = 0;
	last_swap_count = 0;

	std::thread th([this]() {

		{
			auto copyarr = arr;
			int left = 0;
			int right = copyarr.size() - 1;

			Clock timer;
			while (left < right)
			{
				for (int i = left; i < right; i++)
				{
					if (copyarr[i].first > copyarr[i + 1].first)
					{
						std::swap(copyarr[i].first, copyarr[i + 1].first);
					}
				}
				right--;

				for (int i = right; i > left; i--)
				{
					if (copyarr[i].first < copyarr[i - 1].first)
					{
						std::swap(copyarr[i].first, copyarr[i - 1].first);
					}
				}
				left++;
			}
			last_sort_time = timer.getElapsedTime().asMicroseconds();
		}

		int left = 0;
		int right = arr.size() - 1;

		while (left < right)
		{
			for (int i = left; i < right; i++)
			{
				last_comparison.first = i;
				last_comparison.second = i + 1;
				last_comparison_count++;
				std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
				last_comparison.first = -1;
				last_comparison.second = -1;
				if (arr[i].first > arr[i + 1].first)
				{
					std::swap(arr[i].first, arr[i + 1].first);
					last_swap.first = i;
					last_swap.second = i + 1;
					last_swap_count++;
					std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
					last_swap.first = -1;
					last_swap.second = -1;
				}

			}
			arr[right].second = true;
			right--;

			for (int i = right; i > left; i--)
			{
				last_comparison.first = i;
				last_comparison.second = i - 1;
				last_comparison_count++;
				std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
				last_comparison.first = -1;
				last_comparison.second = -1;
				if (arr[i].first < arr[i - 1].first)
				{
					std::swap(arr[i].first, arr[i - 1].first);
					last_swap.first = i;
					last_swap.second = i - 1;
					last_swap_count++;
					std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
					last_swap.first = -1;
					last_swap.second = -1;
				}

			}
			arr[left].second = true;
			left++;

		}

		last_swap.first = -1;
		last_swap.second = -1;
		last_comparison.first = -1;
		last_comparison.second = -1;

		_sort_in_progress = false;

		});

	th.detach();

}

void SortArr::comb_sort()
{
	_sort_in_progress = true;
	last_sort_time = 0;
	last_comparison_count = 0;
	last_swap_count = 0;

	std::thread th([this]() {


		auto copyarr = arr;
		{
			Clock timer;

			int tmp;
			int n = copyarr.size();
			int s = n;
			bool swapped = true;

			while (s > 1 || swapped) {
				s /= 1.25f;

				if (s < 1)
					break;

				swapped = false;
				for (int i = 0; i + s < n; i++)
				{
					if (copyarr[i].first > copyarr[i + s].first)
					{
						std::swap(copyarr[i].first, copyarr[i + s].first);
						swapped = true;
					}
				}

			}
			last_sort_time = timer.getElapsedTime().asMicroseconds();
		}


		int tmp;
		int n = arr.size();
		int s = n;
		bool swapped = true;

		while (s > 1 || swapped) {
			s /= 1.25f;

			if (s < 1)
				break;

			swapped = false;
			for (int i = 0; i + s < n; i++)
			{
				last_comparison.first = i;
				last_comparison.second = i + s;
				last_comparison_count++;
				std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
				last_comparison.first = -1;
				last_comparison.second = -1;


				if (arr[i].first > arr[i + s].first)
				{
					std::swap(arr[i].first, arr[i + s].first);

					swapped = true;



					last_swap.first = i;
					last_swap.second = i + s;
					last_swap_count++;
					std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
					last_swap.first = -1;
					last_swap.second = -1;


				}


				for (int i = 0; i < arr.size(); i++)
				{
					if (arr[i].first == copyarr[i].first)
						arr[i].second = true;
					else
						break;
				}

				for (int i = arr.size() - 1; i >= 0; i--)
				{
					if (arr[i].first == copyarr[i].first)
						arr[i].second = true;
					else
						break;
				}

			}

		}


		last_swap.first = -1;
		last_swap.second = -1;
		last_comparison.first = -1;
		last_comparison.second = -1;

		_sort_in_progress = false;

		});

	th.detach();
}

void SortArr::insertion_sort()
{
	_sort_in_progress = true;
	last_sort_time = 0;
	last_comparison_count = 0;
	last_swap_count = 0;

	std::thread th([this]() {

		auto copyarr = arr;
		Clock timer;

		for (int i = 1; i < copyarr.size(); i++) {
			int key = copyarr[i].first;
			int j = i - 1;
			while (j >= 0 && copyarr[j].first > key) {
				copyarr[j + 1].first = copyarr[j].first;
				j--;
			}
			copyarr[++j].first = key;
		}

		last_sort_time = timer.getElapsedTime().asMicroseconds();

		for (int i = 1; i < arr.size(); i++)
		{
			int key = arr[i].first;

			int j = i - 1;

			while (j >= 0 && arr[j].first > key)
			{
				last_comparison_count++;
				last_comparison.first = j;
				std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
				last_comparison.first = -1;

				arr[j + 1].first = arr[j].first;
				j--;
				last_swap_count++;
				last_swap.first = j;
				last_swap.second = j + 1;

				std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));

				last_swap.first = -1;
				last_swap.second = -1;
			}

			arr[++j].first = key;
			last_swap_count++;

			last_swap.first = j;
			std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
			last_swap.first = -1;

			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].first == copyarr[i].first)
					arr[i].second = true;
				else
					break;
			}

		}

		last_swap.first = -1;
		last_swap.second = -1;
		last_comparison.first = -1;
		last_comparison.second = -1;

		_sort_in_progress = false;

		});

	th.detach();
}



void SortArr::Merge(std::vector<std::pair<int, bool>>& mas, int lowIndex, int middleIndex, int highIndex)
{
	int left = lowIndex;
	int right = middleIndex + 1;
	int index = 0;

	std::vector<std::pair<int, bool>> tempArray(highIndex - lowIndex + 1);
	
	while ((left <= middleIndex) && (right <= highIndex))
	{
		if (mas[left].first < mas[right].first)
		{
			tempArray[index].first = mas[left].first;
		//	std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
			left++;
		}
		else
		{
			tempArray[index].first = mas[right].first;
		//	std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
			right++;
		}

		index++;
	}

	for (int i = left; i <= middleIndex; i++)
	{
		tempArray[index].first = mas[i].first;
		index++;
	}


	for (int i = right; i <= highIndex; i++)
	{
		tempArray[index].first = mas[i].first;
		index++;
	}


	for (int i = 0; i < tempArray.size(); i++)
	{
		mas[lowIndex + i].first = tempArray[i].first;
	//	std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
	}
}



void SortArr::MergeSort(std::vector<std::pair<int, bool>>& mas, std::vector<std::pair<int, bool>> *sortarr, int lowIndex, int highIndex)
{
	if (lowIndex < highIndex)
	{
		int middleIndex = (lowIndex + highIndex) / 2;
		MergeSort(mas, sortarr, lowIndex, middleIndex);
		MergeSort(mas, sortarr, middleIndex + 1, highIndex);
		Merge(mas, lowIndex, middleIndex, highIndex);

		if (sortarr != nullptr)
			for (int i = lowIndex; i <= highIndex; i++)
				if (mas[i].first == (*sortarr)[i].first)
					mas[i].second = true;

	}
}



void SortArr::merge_sort()
{
	_sort_in_progress = true;
	last_sort_time = 0;
	last_comparison_count = 0;
	last_swap_count = 0;

	std::thread th([this]() {

		auto copyarr = arr;
	
		Clock timer;
		MergeSort(copyarr, nullptr,  0, copyarr.size() - 1);
		last_sort_time = timer.getElapsedTime().asMicroseconds();

		MergeSort(arr, &copyarr,  0, arr.size() - 1);

		last_swap.first = -1;
		last_swap.second = -1;
		last_comparison.first = -1;
		last_comparison.second = -1;

		_sort_in_progress = false;

		});

	th.detach();
}

void SortArr::quick_sort()
{
	_sort_in_progress = true;
	last_sort_time = 0;
	last_comparison_count = 0;
	last_swap_count = 0;


	std::thread th([this]() {

		auto copyarr = arr;

		{
			auto partition1 = [](std::vector<std::pair<int, bool>>& arr, int left, int right) {

				auto val = arr[(left + right) / 2];
				int i = left;
				int j = right;

				while (i <= j)
				{
					while (arr[i] < val) i++;
					while (arr[j] > val) j--;

					if (i >= j)	break;

					std::swap(arr[i++].first, arr[j--].first);
				}
				return j;
			};

			std::stack<std::pair<int, int>> st1;


			Clock timer;

			st1.push({ 0, copyarr.size() - 1 });

			while (!st1.empty())
			{
				auto cur = st1.top();
				st1.pop();
				if (cur.first < cur.second)
				{
					auto q = partition1(copyarr, cur.first, cur.second);
					st1.push({ cur.first, q });
					st1.push({ q + 1, cur.second });
				}
			}

			last_sort_time = timer.getElapsedTime().asMicroseconds();
		}

		
			auto partition = [&](std::vector<std::pair<int, bool>>& mas, int left, int right) {

				int val = mas[(left + right) / 2].first;
				int i = left;
				int j = right;

				while (i <= j)
				{
					last_comparison_count += 2;
					while (mas[i].first < val)
					{
						last_comparison_count++;

						last_comparison.first = i;
						std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
						last_comparison.first = -1;

						i++;
					}
					while (mas[j].first > val)
					{
						last_comparison_count++;

						last_comparison.first = j;
						std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
						last_comparison.first = -1;

						j--;
					}

					if (i >= j)	break;

					std::swap(mas[i++].first, mas[j--].first);


					for (int h = 0; h < copyarr.size(); h++)
					{
						if (arr[h].first == copyarr[h].first)
							arr[h].second = true;

					}

					last_swap_count++;
					last_swap.first = i;
					last_swap.second = j;
					std::this_thread::sleep_for(std::chrono::milliseconds(SORT_DELAY));
					last_swap.first = -1;
					last_swap.second = -1;

				}
				return j;
			};

			std::stack<std::pair<int, int>> st;

			st.push({ 0, arr.size() - 1 });

			while (!st.empty())
			{
				auto cur = st.top();
				st.pop();
				if (cur.first < cur.second)
				{
					auto q = partition(arr, cur.first, cur.second);
					st.push({ cur.first, q });
					st.push({ q + 1, cur.second });
				}
			}

		last_swap.first = -1;
		last_swap.second = -1;
		last_comparison.first = -1;
		last_comparison.second = -1;

		_sort_in_progress = false;

		});

	th.detach();

}

void SortArr::std_sort()
{
	_sort_in_progress = true;
	last_sort_time = 0;
	last_comparison_count = 0;
	last_swap_count = 0;

	std::thread th([this]() {

		Clock timer;

		std::sort(arr.begin(), arr.end());

		last_sort_time = timer.getElapsedTime().asMicroseconds();

		for (auto& el : arr)
			el.second = true;

		_sort_in_progress = false;

		});

	th.detach();
}

std::pair<int, bool> SortArr::operator[](int index) const
{
	return arr[index];
}

void SortArr::gen_rand_arr(int seed)
{
	srand(seed);
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i].first = rand() % 100;
		arr[i].second = false;
	}
}

bool SortArr::sort_in_progress() const
{
	return _sort_in_progress;
}

int SortArr::get_last_sort_time() const
{
	return last_sort_time;
}

int SortArr::get_last_comparison_count() const
{
	return last_comparison_count;
}

int SortArr::get_last_swap_count() const
{
	return last_swap_count;
}

std::pair<int, int> SortArr::get_last_comparison() const
{
	return last_comparison;
}

std::pair<int, int> SortArr::get_last_swap() const
{
	return last_swap;
}