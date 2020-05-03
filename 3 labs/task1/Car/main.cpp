#include <iostream>
#include "CarControl.h"
#include "Car.h"

using namespace std;

int main()
{
	CCar superCarKalina;
	CCarControl carControl(cin, cout, superCarKalina);
	while (!cin.eof())
	{
		carControl.AnswerCommand();
	}

	return 0;
}