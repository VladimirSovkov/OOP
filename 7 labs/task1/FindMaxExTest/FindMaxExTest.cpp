#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../FindMaxEx/FindMaxEx.h"
#include "../FindMaxEx/Sportsman.h"

TEST_CASE("An empty array is compared")
{
	std::vector<int> emptyArr;
	int maxValue = 0;
	CHECK(!FindMax(emptyArr, maxValue, std::less<int>()));
}

TEST_CASE("there is one element in the array")
{
	std::vector<int> arr {1};
	int maxValue = 0;
	CHECK(FindMax(arr, maxValue, std::less<int>()));
	CHECK(maxValue == 1);
}

TEST_CASE("vector with type int") 
{
	std::vector<int> arr{ 1, 2, 5, 1, 3 };
	int maxValue = 0;
	CHECK(FindMax(arr, maxValue, std::less<int>()));
	CHECK(maxValue == 5);
}

TEST_CASE("vector with type char") 
{
	std::vector<char> arr{ 'a', 'b', 'c', 'a' };
	char maxValue = 0;
	CHECK(FindMax(arr, maxValue, std::less<char>()));
	CHECK(maxValue == 'c');
}

TEST_CASE("vector with type double") 
{
	std::vector<double> arr{ 1.0, 3.5, 4.9, 0.0};
	double maxValue = 0;
	CHECK(FindMax(arr, maxValue, std::less<double>()));
	CHECK(maxValue == 4.9);
}

TEST_CASE("vector with type string") 
{
	std::vector<std::string> arr{ "a", "ab", "abc", "c"};
	std::string maxValue = "";
	CHECK(FindMax(arr, maxValue, std::less<std::string>()));
	CHECK(maxValue == "c");
}

TEST_CASE("find maximum weight and height in an array of sportsman")
{
	std::vector<Sportsman> arr{
		{"Иванов", "Иван", "Иванович", 180, 85 },
		{"Петров", "Петр", "Алексеевич", 190, 80 },
		{"Петров", "Иван", "Николаевич", 176, 70},
		{"Иванов", "Петр", "Иванович", 178, 75},
	};
	Sportsman soughtSportsman;

	WHEN("find maximum weight")
	{
		CHECK(FindMax(arr, soughtSportsman, IsWeightOfFirstMore));
		CHECK("Иванов" == soughtSportsman.surname);
		CHECK("Иван" == soughtSportsman.name);
		CHECK("Иванович" == soughtSportsman.patronymic);
		CHECK(180 == soughtSportsman.height);
		CHECK(85 == soughtSportsman.weight);
	}

	WHEN("find maximum height")
	{
		CHECK(FindMax(arr, soughtSportsman, IsHeightOfFirstMore));
		CHECK("Петров" == soughtSportsman.surname);
		CHECK("Петр" == soughtSportsman.name);
		CHECK("Алексеевич" == soughtSportsman.patronymic);
		CHECK(190 == soughtSportsman.height);
		CHECK(80 == soughtSportsman.weight);
	}
}

