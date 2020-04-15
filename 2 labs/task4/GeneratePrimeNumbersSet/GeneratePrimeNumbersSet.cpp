#include "GeneratePrimeNumbersSet.h"
#include <vector>

using namespace std;

vector<bool> CreateVectorPointToPrimeNumber(const int upperBound)
{
	if (upperBound < 0)
	{
		return {};
	}

	int lengthVector = upperBound + 1;
	vector<bool>isPrime(lengthVector, true);
	size_t sizeVector = isPrime.size();
	for (int i = 0; (i < sizeVector) && (i < 2); i++)
	{
		isPrime[i] = false;
	}
	
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

set<int> GetPrimeNumbers(const vector<bool>& isPrime)
{
	set<int> primeNumbersSet;
	for (unsigned int i = 2; i < isPrime.size(); i++)
	{
		if (isPrime[i])
		{
			primeNumbersSet.insert(primeNumbersSet.end(), i);
		}
	}
	return primeNumbersSet;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	vector<bool> isPrime = CreateVectorPointToPrimeNumber(upperBound);
	set<int> manyPrimeNumbers = GetPrimeNumbers(isPrime);
	return manyPrimeNumbers;
}