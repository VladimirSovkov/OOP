#include "../../../catch2/catch.hpp"
#include "../Calculator/CalculatorControl.h"
#include <sstream>

void ExpectOperationSuccess(const std::string& command, const std::string& answer, CCalculator& calculator)
{
	std::stringstream input, output;
	CCalculatorControl calculatorControl(input, output, calculator);
	input << command;
	CHECK(calculatorControl.AnswerCommand());
	CHECK(answer == output.str());
}

void ExpectOperationFailure(const std::string& command, const std::string& answer, CCalculator& calculator)
{
	std::stringstream input, output;
	CCalculatorControl calculatorControl(input, output, calculator);
	input << command;
	CHECK(!calculatorControl.AnswerCommand());
	CHECK(answer == output.str());
}

TEST_CASE("transmitted incorrect command")
{
	CCalculator calculator;

	ExpectOperationFailure("no_command", "Incorrect command\n", calculator);
	ExpectOperationFailure("var a = b", "Incorrect identifier\n", calculator);
	ExpectOperationFailure("fn Function", "Incorrect command\n", calculator);
}

TEST_CASE("Check on set variable")
{
	CCalculator calculator;

	WHEN("correct adding variable")
	{
		ExpectOperationSuccess("var x", "", calculator);
		CCalculator::VariablesContainer sample = { {"x", std::nullopt} };
		CHECK(calculator.GetVariables() == sample);
	}

	WHEN("this variable is declared")
	{
		calculator.SetVariables("x");
		ExpectOperationFailure("var x", "repeat declaration of identifier\n", calculator);
		CCalculator::VariablesContainer sample = { {"x", std::nullopt} };
		CHECK(calculator.GetVariables() == sample);
	}

	WHEN("incorrect identifier")
	{
		ExpectOperationFailure("var 1_var", "Incorrect identifier\n", calculator);
	}
}

TEST_CASE("Check set value variable")
{
	CCalculator calculator;

	WHEN("correct adding variable")
	{
		ExpectOperationSuccess("let x = -3", "", calculator);
		ExpectOperationSuccess("let y = x", "", calculator);

		CCalculator::VariablesContainer sample =
		{ 
			{"x", -3},
			{"y", -3}
		};
		CHECK(calculator.GetVariables() == sample);
	}
	
	WHEN("values written incorrectly")
	{
		ExpectOperationFailure("let 1_x = 5", "Incorrect identifier\n", calculator);
		ExpectOperationFailure("let x = y", "Incorrect identifier or Identifier y was not declared\n", calculator);
	}
}

TEST_CASE("Check on adding function")
{
	CCalculator calculator;
	calculator.SetVariableValue("x", 5);
	calculator.SetVariableValue("y", 2);
	WHEN("Correct adding function")
	{
		ExpectOperationSuccess("fn XPlusY=x+y", "", calculator);
		ExpectOperationSuccess("fn valueXPlusY = XPlusY", "", calculator);
	}

	WHEN("Incorrect name function")
	{
		ExpectOperationFailure("fn 1_Function = x", "Incorrect name function\n", calculator);
	}
	
	WHEN("Function was declared")
	{
		calculator.SetFunction("Function", "x");
		ExpectOperationFailure("fn Function = x", "repeated declaration function Function impossible\n", calculator);
	}

	WHEN("identifiers were not declared")
	{
		ExpectOperationFailure("fn function = x+no_var", "identifier \"no_var\" not declared\n", calculator);
		ExpectOperationFailure("fn function = no_var + x", "identifier \"no_var\" not declared\n", calculator);
	}
}

TEST_CASE("Check on a print values identifier")
{
	CCalculator calculator;

	WHEN("Print values identifier")
	{
		calculator.SetVariableValue("y", 4);
		calculator.SetVariableValue("x", 5.123456);
		calculator.SetFunction("XPlusY", "x", "y", CCalculator::Operation::Addition);
		ExpectOperationSuccess("print x", "5.12\n", calculator);
		ExpectOperationSuccess("print XPlusY", "9.12\n", calculator);
	}

	WHEN("Print identifier no value")
	{
		calculator.SetVariables("y");
		calculator.SetVariableValue("x", 5.123456);
		calculator.SetFunction("XPlusY", "x", "y", CCalculator::Operation::Addition);
		ExpectOperationSuccess("print XPlusY", "nan\n", calculator);
		ExpectOperationSuccess("print y", "nan\n", calculator);
	}

	WHEN("Print not declared identifier")
	{
		ExpectOperationFailure("print x", "identifier \"x\" not declared\n", calculator);
	}
}

TEST_CASE("Print all name and values variables")
{
	std::stringstream input, output;
	CCalculator calculator;
	calculator.SetVariables("g");
	calculator.SetVariables("b");
	calculator.SetVariableValue("a", 1);
	calculator.SetVariableValue("c", 3);
	calculator.SetVariableValue("d", 4.12345);
	CCalculatorControl calculatorControl(input, output, calculator);
	input << "printvars" << std::endl;
	calculatorControl.AnswerCommand();

	CHECK(output.str() == "a : 1\nb : nan\nc : 3\nd : 4.12\ng : nan\n");
}

TEST_CASE("Print all name and values function")
{
	std::stringstream input, output;
	CCalculator calculator;
	calculator.SetVariables("b");
	calculator.SetVariableValue("a", 1);
	calculator.SetVariableValue("c", 3.5);
	calculator.SetFunction("APlusC", "a", "c", CCalculator::Operation::Addition);
	calculator.SetFunction("valueC", "c");
	calculator.SetFunction("CPlusB", "c", "b", CCalculator::Operation::Addition);
	CCalculatorControl calculatorControl(input, output, calculator);
	input << "printfns" << std::endl;
	calculatorControl.AnswerCommand();

	CHECK(output.str() == "APlusC : 4.5\nCPlusB : nan\nvalueC : 3.5\n");
}