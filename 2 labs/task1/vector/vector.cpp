#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "ProcessVector.h"
#include <iomanip>

using namespace std;

int main()
{
	vector<double> numbers(istream_iterator<double>(cin), (istream_iterator<double>()));

	MultiplicationOfAllElementsByTheMinimum(numbers);
	sort(numbers.begin(), numbers.end());

	cout << fixed << setprecision(3);
	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, ", "));

	return 0;
 }