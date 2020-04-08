#include <iostream>
#include "GeneratePrimeNumbersSet.h"

using namespace std;

bool IsRangeCorrect(int number)
{
	if (number > 0 && number < 100000001)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "incorrect number of parameters" << endl;
		cout << "PrimeNumbers.exe <upperBound>" << endl;
		return 1;
	}

	int upperBound = 0; 
	if (!(upperBound = atoi(argv[1])))
	{
		cout << "parameter upperBound must be a number" << endl;
		return 1;
	}

	if (!IsRangeCorrect(upperBound))
	{
		cout << "incorrect number" << endl;
		cout << "the number must correspond to a range from 1 to 100,000,000" << endl;
		return 1;
	}

	set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);

	for (int number : primeNumbers)
	{
		cout << number << endl;
	}

	return 0;
}