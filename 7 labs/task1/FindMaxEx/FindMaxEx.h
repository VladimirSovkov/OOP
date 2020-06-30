#pragma once
#include <vector>

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	maxValue = arr[0];
	for (auto element : arr)
	{
		if (less(maxValue, element))
		{
			maxValue = element;
		}
	}
	return true;
}