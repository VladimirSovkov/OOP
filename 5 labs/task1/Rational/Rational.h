#pragma once
#include <cmath>
#include <iostream>

class CRational
{
public:
	CRational();
	CRational(int value);
	CRational(int numerator, int denominator);

	void SimplifyFraction();

	int GetNumerator()const;
	int GetDenominator()const;

	double ToDouble()const;
	std::pair<int, CRational> ToCompoundFraction()const;

	const CRational operator+() const;  
	const CRational operator-() const;
	const CRational& operator+=(const CRational& rational);
	const CRational& operator-=(const CRational& rational);
	const CRational& operator*=(const CRational& rational);
	const CRational& operator/=(const CRational& rational);

private:

	int m_numerator;
	int m_denominator;
};
CRational const operator+(const CRational& firstRational, const CRational secondRational);
CRational const operator-(const CRational& firstRational, const CRational secondRational);
CRational const operator*(const CRational& firstRational, const CRational secondRational);
CRational const operator/(const CRational& firstRational, const CRational secondRational);

bool operator ==(const CRational& firstRational, const CRational& secondRational);
bool operator !=(const CRational& firstRational, const CRational& secondRational);

bool operator>(const CRational& firstRational, const CRational& secondRational);
bool operator<(const CRational& firstRational, const CRational& secondRational);
bool operator>=(const CRational& firstRational, const CRational& secondRational);
bool operator<=(const CRational& firstRational, const CRational& secondRational);

std::ostream& operator <<(std::ostream& output, const CRational& rational);
std::istream& operator >>(std::istream& input, CRational& rational);