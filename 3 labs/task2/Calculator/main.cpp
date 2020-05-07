#include <iostream>
#include "Calculator.h"
#include "CalculatorControl.h"

using namespace std;

int main()
{
	CCalculator calculator;
	CCalculatorControl calculatorControl(cin, cout, calculator);
	while (!cin.eof())
	{
		calculatorControl.AnswerCommand();
	}
	 
	return 0;
}