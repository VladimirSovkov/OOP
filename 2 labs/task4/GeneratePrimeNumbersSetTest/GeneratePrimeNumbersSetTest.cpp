#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../GeneratePrimeNumbersSet/GeneratePrimeNumbersSet.h"

TEST_CASE("checking range in which there are no prime numbers")
{
	std::set<int> outputValue = GeneratePrimeNumbersSet(0);
	std::set<int> sample{};
	CHECK(sample == outputValue);

	outputValue = GeneratePrimeNumbersSet(1);
	CHECK(sample == outputValue);
}

TEST_CASE("checking that the output of primes is correct")
{
	std::set<int> outputValue = GeneratePrimeNumbersSet(10);
	std::set<int> sample{ 2, 3, 5, 7 };
	CHECK(sample == outputValue);

	outputValue = GeneratePrimeNumbersSet(100);
	sample = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
	CHECK(sample  == outputValue);

	outputValue = GeneratePrimeNumbersSet(30);
	sample = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
	CHECK(sample == outputValue);
}

#if !_DEBUG

TEST_CASE("check on a large range the number of numbers")
{
	std::set<int> outputValue = GeneratePrimeNumbersSet(100000000);
	size_t sizeSet = outputValue.size();
	size_t sample = 5761455;

	CHECK(sample == sizeSet);
}

#endif

TEST_CASE("check for the creation of a vector point to prime numbers in the form of an index")
{
	std::vector<bool> outputSet = CreateVectorPointToPrimeNumber(1);
	std::vector<bool> sample{ false, false };
	CHECK(sample == outputSet);

	outputSet = CreateVectorPointToPrimeNumber(0);
	sample = { false };
	CHECK(sample == outputSet);

	outputSet = CreateVectorPointToPrimeNumber(-1);
	sample = {};
	CHECK(sample == outputSet);

	outputSet = CreateVectorPointToPrimeNumber(2);
	sample = {false, false, true};
	CHECK(sample == outputSet);
}