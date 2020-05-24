#include "../../../catch2/catch.hpp"
#include "../Rational/Rational.h"
#include <sstream>

TEST_CASE("check constructor and receiving data")
{
	WHEN("CRational with positive numbers")
	{
		int numerator = 1;
		int denominator = 2;
		CRational rational (numerator, denominator);
		CHECK(rational.GetNumerator() == numerator);
		CHECK(rational.GetDenominator() == denominator);
	}

	WHEN("CRational with negative numbers")
	{
		int numerator = -1;
		int denominator = -2;
		CRational rational(numerator, denominator);
		CHECK(rational.GetNumerator() == -numerator);
		CHECK(rational.GetDenominator() == -denominator);
	}

	WHEN("construction of a rational number (0/1)")
	{
		CRational rational;
		CHECK(rational.GetNumerator() == 0);
		CHECK(rational.GetDenominator() == 1);
	}

	WHEN("construction of a rational number (value/1)")
	{
		CRational rational(2);
		CHECK(rational.GetNumerator() == 2);
		CHECK(rational.GetDenominator() == 1);
	}
}

TEST_CASE("simplify fraction when constructing")
{
	CRational rational(450, 3000);
	CHECK(rational.GetNumerator() == 3);
	CHECK(rational.GetDenominator() == 20);
}

TEST_CASE("check ToDouble")
{
	CRational rational(1, 2);
	CHECK(rational.ToDouble() == 0.5);
}

TEST_CASE("unary operators")
{
	int numerator = 1;
	int denominator = 2;
	CRational rational(numerator, denominator);
	WHEN("unary plus")
	{
		CRational positiveFraction = +rational;
		CHECK(positiveFraction.GetNumerator() == numerator);
		CHECK(positiveFraction.GetDenominator() == denominator);
	}

	WHEN("unary minus")
	{
		CRational negtiveFraction = -rational;
		CHECK(negtiveFraction.GetNumerator() == -numerator);
		CHECK(negtiveFraction.GetDenominator() == denominator);
	}
}

TEST_CASE("binary operator")
{
	CRational firstRational(1, 2);
	CRational secondRational(1, 3);

	WHEN("binary plus")
	{
		CRational answer = firstRational + secondRational;
		CHECK(answer.GetNumerator() == 5);
		CHECK(answer.GetDenominator() == 6);

		answer = firstRational + 1;
		CHECK(answer.GetNumerator() == 3);
		CHECK(answer.GetDenominator() == 2);

		answer = 1 + firstRational;
		CHECK(answer.GetNumerator() == 3);
		CHECK(answer.GetDenominator() == 2);
	}

	WHEN("binary minus")
	{
		CRational answer = firstRational - secondRational;
		CHECK(answer.GetNumerator() == 1);
		CHECK(answer.GetDenominator() == 6);

		answer = firstRational - 1;
		CHECK(answer.GetNumerator() == -1);
		CHECK(answer.GetDenominator() == 2);

		answer = 1 - firstRational;
		CHECK(answer.GetNumerator() == 1);
		CHECK(answer.GetDenominator() == 2);
	}
}

TEST_CASE("abbreviated operator with assignment")
{
	CRational firstRational(1, 2);
	CRational secondRational(1, 3);

	WHEN("operator +=")
	{
		CRational sampleRational(5, 6);
		firstRational += secondRational;
		CHECK(sampleRational == firstRational);

		firstRational += 1;
		CRational sampleInt(11, 6);
		CHECK(sampleInt == firstRational);
	}

	WHEN("operator -=")
	{
		CRational sampleRational(1, 6);
		firstRational -= secondRational;
		CHECK(sampleRational == firstRational);

		firstRational -= 1;
		CRational sampleInt(-5, 6);
		CHECK(sampleInt == firstRational);
	}

	WHEN("operator *=")
	{
		CRational sampleRational(1, 6);
		firstRational *= secondRational;
		CHECK(sampleRational == firstRational);

		firstRational *= 2;
		CRational sampleInt(2, 6);
		CHECK(sampleInt == firstRational);
	}

	WHEN("operator /=")
	{
		CRational sampleRational(3, 2);
		firstRational /= secondRational;
		CHECK(sampleRational == firstRational);

		firstRational /= 2;
		CRational sampleInt(3, 4);
		CHECK(sampleInt == firstRational);
	}
}

TEST_CASE("check operator \"*\" and \"/\"")
{
	CRational firstRational(1, 2);
	CRational secondRational(1, 3);

	WHEN("operator *")
	{
		CRational sample(1, 6);
		CRational answer = firstRational * secondRational;
		CHECK(sample == answer);
	}

	WHEN("operator /")
	{
		CRational sample(3, 2);
		CRational answer = firstRational / secondRational;
		CHECK(sample == answer);
	}
}

TEST_CASE("comparison operators")
{
	CRational firstRational(1, 2);
	CRational secondRational(1, 2);
	WHEN("equality")
	{
		CHECK(firstRational == secondRational);

		firstRational = firstRational + 1;
		CHECK(!(firstRational == secondRational));
	}

	WHEN("inequality")
	{
		secondRational += 1;
		CHECK(firstRational != secondRational);

		secondRational = secondRational - 1;
		CHECK(!(firstRational != secondRational));
	}

	WHEN("operator >")
	{
		secondRational += 1;
		CHECK(secondRational > firstRational);
	}


	WHEN("operator >=")
	{
		CHECK(secondRational >= firstRational);

		secondRational += 1;
		CHECK(secondRational >= firstRational);
	}

	WHEN("operator <=")
	{
		CHECK(firstRational <= secondRational);

		secondRational += 1;
		CHECK(firstRational <= secondRational);
	}

	WHEN("operator <")
	{
		secondRational += 1;
		CHECK(firstRational < secondRational);
	}
}

TEST_CASE("check operator <<")
{
	CRational rational(1, 2);
	std::stringstream outputStream;
	outputStream << rational;
	CHECK("1/2" == outputStream.str());
}

TEST_CASE("check operator >>")
{
	WHEN("correct line")
	{
		CRational rational;
		std::stringstream inputStream("-1/2");
		inputStream >> rational;
		CHECK(rational.GetNumerator() == -1);
		CHECK(rational.GetDenominator() == 2);
	}

	WHEN("incorrect line")
	{
		CRational rational;
		std::stringstream inputStream("-12");
		inputStream >> rational;
		CHECK(rational.GetNumerator() == 0);
		CHECK(rational.GetDenominator() == 1);
		CHECK(inputStream.fail());
	}
}

TEST_CASE("Check ToCompoundFraction")
{
	WHEN("fraction without whole")
	{
		CRational rational(1, 2);
		std::pair<int, CRational> fraction = rational.ToCompoundFraction();
		CHECK(fraction.first == 0);
		CHECK(fraction.second == rational);
	}

	WHEN("fraction with whole")
	{
		CRational rational(11, 4);
		CRational rationalWhithoutWhole(3, 4);
		std::pair<int, CRational> fraction = rational.ToCompoundFraction();
		CHECK(fraction.first == 2);
		CHECK(fraction.second == rationalWhithoutWhole);
	}
}