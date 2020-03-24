#define CATCH_CONFIG_MAIN
#include <../../catch2/catch.hpp>
#include "vector/ProcessVector.h"


TEST_CASE("check with empty vector")
{
	std::vector<double> arrayNumbers;
	std::vector<double> outArrayNumbers;
	MultiplicationOfAllElementsByTheMinimum(arrayNumbers);

	CHECK(arrayNumbers == outArrayNumbers);
}

TEST_CASE("vector minimum number 0")
{
	std::vector<double> arrayNumbers = { 0, 43.6535, 69.3523, 74, 53.9238 };
	std::vector<double> outArrayNumbers = { 0, 0, 0, 0, 0 };
	MultiplicationOfAllElementsByTheMinimum(arrayNumbers);

	CHECK(arrayNumbers == outArrayNumbers);
}

TEST_CASE("integer and fractional numbers are passed to the input")
{
	std::vector<double> arrayNumbers = { 2, 5, 6, 45.64 };
	std::vector<double> outArrayNumbers = { 4, 10, 12, 91.28 };
	MultiplicationOfAllElementsByTheMinimum(arrayNumbers);

	CHECK(arrayNumbers == outArrayNumbers);

	arrayNumbers = { 5.34, 32.145, 54.13, 23.5 };
	outArrayNumbers = { 28.5156, 171.6543, 289.0542, 125.49 };
	MultiplicationOfAllElementsByTheMinimum(arrayNumbers);

	CHECK(arrayNumbers == outArrayNumbers);
}

