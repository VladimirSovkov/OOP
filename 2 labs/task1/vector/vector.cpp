#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "ProcessVector.h"

using namespace std;

int main()
{
	vector<double> numbers(istream_iterator<double>(cin), (istream_iterator<double>()));

	MultiplicationOfAllElementsByTheMinimum(numbers);
	sort(numbers.begin(), numbers.end());

	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, ", "));

	return 0;
 }