#include "ProcessVector.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

//Каждый элемент массива должен быть умножен на минимальный элемент исходного массива
void MultiplyByMinElement(std::vector<double>& arrayNumbers)
{
	if (!arrayNumbers.empty())
	{
		const double minNumber = *min_element(arrayNumbers.begin(), arrayNumbers.end());
		transform(arrayNumbers.begin(), 
			arrayNumbers.end(), 
			arrayNumbers.begin(), 
			[&minNumber](double numberVector) 
			{
				return numberVector * minNumber;
			});
	}
}
