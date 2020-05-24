#include "Rational.h"

int GreatestCommonDivisor(int num1, int num2)
{
	num1 = abs(num1);
	num2 = abs(num2);
	while (num1 != 0 && num2 != 0)
	{
		if (num1 > num2)
			num1 = num1 % num2;
		else
			num2 = num2 % num1;
	}
	return (num1 + num2);
}

CRational::CRational()
{
	m_numerator = 0;
	m_denominator = 1;
}

CRational::CRational(int value)
{
	m_numerator = value;
	m_denominator = 1;
}

CRational::CRational(int numerator, int denominator)
	:m_numerator(numerator),
	m_denominator(denominator)
{
	if (m_denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	else if (denominator == 0)
	{
		m_numerator = 0;
		m_denominator = 1;
	}

	SimplifyFraction();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return (double(m_numerator) / double(m_denominator));
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int wholeNumber = m_numerator / m_denominator;
	int numerator = m_numerator % m_denominator;

	return std::make_pair(wholeNumber, CRational(numerator, m_denominator));
}

void CRational::SimplifyFraction()
{
	int gcd = GreatestCommonDivisor(m_numerator, m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

const CRational CRational::operator+() const
{
	return CRational(m_numerator, m_denominator);
}

const CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

const CRational& CRational::operator+=(const CRational& rational)
{
	m_numerator = (m_numerator * rational.GetDenominator()) + (rational.GetNumerator() * m_denominator);
	m_denominator *= rational.GetDenominator();
	SimplifyFraction();
	return *this;
}

const CRational& CRational::operator-=(const CRational& rational)
{
	m_numerator = (m_numerator * rational.GetDenominator()) - (rational.GetNumerator() * m_denominator);
	m_denominator *= rational.GetDenominator();
	SimplifyFraction();
	return *this;
}

const CRational& CRational::operator*=(const CRational& rational)
{
	m_numerator *= rational.GetNumerator();
	m_denominator *= rational.GetDenominator();
	SimplifyFraction();
	return *this;
}

const CRational& CRational::operator/=(const CRational& rational)
{
	m_numerator *= rational.GetDenominator();
	m_denominator *= rational.GetNumerator();
	SimplifyFraction();
	return *this;
}

bool operator==(const CRational& firstRational, const CRational& secondRational)
{
	return (firstRational.GetNumerator() == secondRational.GetNumerator()) &&
		(firstRational.GetDenominator() == secondRational.GetDenominator());
}

bool operator!=(const CRational& firstRational, const CRational& fraction2)
{
	return !(firstRational == fraction2);
}

CRational const operator+(const CRational& firstRational, const CRational secondRational)
{
	int denominator = firstRational.GetDenominator() * secondRational.GetDenominator();
	int numerator = (firstRational.GetNumerator() * secondRational.GetDenominator()) + (secondRational.GetNumerator() * firstRational.GetDenominator());
	return CRational(numerator, denominator);
}

CRational const operator-(const CRational& firstRational, const CRational secondRational)
{
	int denominator = firstRational.GetDenominator() * secondRational.GetDenominator();
	int numerator = (firstRational.GetNumerator() * secondRational.GetDenominator()) - (secondRational.GetNumerator() * firstRational.GetDenominator());
	return CRational(numerator, denominator);
}

CRational const operator*(const CRational& firstRational, const CRational secondRational)
{
	int numerator = firstRational.GetNumerator() * secondRational.GetNumerator();
	int denominator = firstRational.GetDenominator() * secondRational.GetDenominator();
	return CRational(numerator, denominator);
}

CRational const operator/(const CRational& firstRational, const CRational secondRational)
{
	int numerator = firstRational.GetNumerator() * secondRational.GetDenominator();
	int denominator = firstRational.GetDenominator() * secondRational.GetNumerator();
	return CRational(numerator, denominator);
}

bool operator>(const CRational& firstRational, const CRational& secondRational)
{
	return (firstRational.GetNumerator() * secondRational.GetDenominator()) > (secondRational.GetNumerator() * firstRational.GetDenominator());
}

bool operator<(const CRational& firstRational, const CRational& secondRational)
{
	return (firstRational.GetNumerator() * secondRational.GetDenominator()) < (secondRational.GetNumerator() * firstRational.GetDenominator());
}

bool operator>=(const CRational& firstRational, const CRational& secondRational)
{
	return (firstRational.GetNumerator() * secondRational.GetDenominator()) >= (secondRational.GetNumerator() * firstRational.GetDenominator());
}

bool operator<=(const CRational& firstRational, const CRational& secondRational)
{
	return (firstRational.GetNumerator() * secondRational.GetDenominator()) <= (secondRational.GetNumerator() * firstRational.GetDenominator());
}

std::ostream& operator<<(std::ostream& output, const CRational& rational)
{
	output << rational.GetNumerator() << "/" << rational.GetDenominator();
	return output;
}

std::istream& operator>>(std::istream& input, CRational& rational)
{
	int numerator;
	int denominator;
	if (input >> numerator && input.get() == '/' && input >> denominator)
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		input.setstate(std::ios_base::failbit);
	}
	return input;
}
