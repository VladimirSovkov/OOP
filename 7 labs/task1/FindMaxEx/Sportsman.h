#pragma once
#include <string>

struct Sportsman
{
	std::string surname;
	std::string name;
	std::string patronymic;
	double height = 0;
	double weight = 0;
};

bool IsWeightOfFirstMore(const Sportsman& first, const Sportsman& second)
{
	return first.weight < second.weight;
}

bool IsHeightOfFirstMore(const Sportsman& first, const Sportsman& second)
{
	return first.height < second.height;
}