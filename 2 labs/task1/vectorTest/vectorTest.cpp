#define CATCH_CONFIG_MAIN
#include <../../catch2/catch.hpp>
#include "vector/ProcessVector.h"

TEST_CASE("testing with an empty vector")
{
	std::vector<double> arrayNumbers = {};
	std::vector<double> outArrayNumbers = {};
	MultiplyByMinElement(arrayNumbers);

	CHECK(arrayNumbers == outArrayNumbers);
}

TEST_CASE("integer and fractional numbers are passed to the input")
{
	std::vector<double> arrayNumbers = { 0, 43.6535, 69.3523, 74, 53.9238 };
	std::vector<double> outArrayNumbers = { 0, 0, 0, 0, 0 };
	MultiplyByMinElement(arrayNumbers);

	CHECK(arrayNumbers == outArrayNumbers);

	arrayNumbers = { 2, 5, 6, 45.64 };
	outArrayNumbers = { 4, 10, 12, 91.28 };
	MultiplyByMinElement(arrayNumbers);

	CHECK(arrayNumbers == outArrayNumbers);

	arrayNumbers = { 5.34, 32.145, 54.13, 23.5 };
	outArrayNumbers = { 28.5156, 171.6543, 289.0542, 125.49 };
	MultiplyByMinElement(arrayNumbers);

	CHECK(arrayNumbers == outArrayNumbers);
}

