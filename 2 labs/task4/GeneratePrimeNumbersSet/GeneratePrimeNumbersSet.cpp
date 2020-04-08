#include "GeneratePrimeNumbersSet.h"
#include <vector>

using namespace std;

vector<bool> IsThisPrimeNumber(const int upperBound)
{
	int lengthVector = upperBound + 1;
	vector<bool>isPrime(lengthVector, true);
	for (int i = 2; i*i < lengthVector; i++)
	{
		if (isPrime[i])
		{
			for (int k = i*i; k < lengthVector; k += i)
			{
				isPrime[k] = false;
			}
		}
	}

	return isPrime;
}

set<int> GetPrimeNumbers(const vector<bool> isPrime)
{
	set<int> manyPrimeNumbers;
	for (unsigned int i = 2; i < isPrime.size(); i++)
	{
		if (isPrime[i])
		{
			manyPrimeNumbers.insert(i);
		}
	}

	return manyPrimeNumbers;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	vector<bool> isPrime = IsThisPrimeNumber(upperBound);
	set<int> manyPrimeNumbers = GetPrimeNumbers(isPrime);
	return manyPrimeNumbers;
}