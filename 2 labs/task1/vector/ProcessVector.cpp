#include "ProcessVector.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//������ ������� ������� ������ ���� ������� �� ����������� ������� ��������� �������
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
