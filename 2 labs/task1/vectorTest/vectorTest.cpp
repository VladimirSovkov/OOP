#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "vector/ProcessVector.h"

using namespace std;

TEST_CASE("return all vector values multiplied by the minimum number")
{
	vector<double> arrayNumbers;
	vector<double> outArrayNumbers;
	MultiplicationOfAllElementsByTheMinimum(arrayNumbers);

	CHECK(arrayNumbers == outArrayNumbers);

	arrayNumbers = { 0, 43.6535, 69.3523, 74, 53.9238 };
	outArrayNumbers = { 0, 0, 0, 0, 0 };
	MultiplicationOfAllElementsByTheMinimum(arrayNumbers);
	
	CHECK(arrayNumbers == outArrayNumbers);
 
	arrayNumbers = { 2, 5, 6, 45.64 };
	outArrayNumbers = { 4, 10, 12, 91.28 };
	MultiplicationOfAllElementsByTheMinimum(arrayNumbers);

	CHECK(arrayNumbers == outArrayNumbers);

	arrayNumbers = { 5.34, 32.145, 54.13, 23.5 };
	outArrayNumbers = { 28.5156, 171.6543, 289.0542, 125.49 };
	MultiplicationOfAllElementsByTheMinimum(arrayNumbers);

	CHECK(arrayNumbers == outArrayNumbers);
}

