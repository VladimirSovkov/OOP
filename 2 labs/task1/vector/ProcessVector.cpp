#include "ProcessVector.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//Каждый элемент массива должен быть умножен на минимальный элемент исходного массива
void MultiplicationOfAllElementsByTheMinimum(std::vector<double>& arrayNumbers)
{
	if (!arrayNumbers.empty())
	{
		const double minNumber = *min_element(arrayNumbers.begin(), arrayNumbers.end());
		for (int index = 0; index < arrayNumbers.size(); index++)
		{
			arrayNumbers[index] *= minNumber;
		}
	}
	


	
}
