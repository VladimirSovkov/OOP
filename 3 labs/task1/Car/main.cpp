#include <iostream>
#include "CarControl.h"
#include "Car.h"

using namespace std;

int main()
{
	CCar car;
	CCarControl carControl(cin, cout, car);
	while (!cin.eof())
	{
		carControl.AnswerCommand();
	}

	return 0;
}