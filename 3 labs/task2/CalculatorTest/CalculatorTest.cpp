#include "../../../catch2/catch.hpp"
#include"../Calculator/Calculator.h"
#include <optional>

TEST_CASE("CheckForAddingVariable")
{
	WHEN("incorrect variable is input")
	{
		CCalculator calculator;

		CHECK(!calculator.SetVariables("Перем"));
		CHECK(!calculator.SetVariables("!@#$%^&Perem"));
		CHECK(!calculator.SetVariables("12344"));
		CHECK(!calculator.SetVariables("12Perem12344"));
	}

	WHEN("correct variable is input")
	{
		CCalculator calculator;
		CCalculator::VariablesContainer sample;
		sample.emplace("Variable_1", std::nullopt);

		calculator.SetVariables("Variable_1");
		CHECK(sample == calculator.GetVariables());
	}

	WHEN("Identifier was declared")
	{
		CCalculator calculator;
		calculator.SetVariables("x");
		CHECK(!calculator.SetVariables("x"));
	
		calculator.SetFunction("nameFunc", "x");
		CHECK(!calculator.SetVariables("nameFunc"));
	}
}

TEST_CASE("set the value of a variable received throught number")
{
	WHEN("Incorrect Name Variable")
	{
		CCalculator calculator;
		CHECK(!calculator.SetVariableValue("1Name", 1.00));
	}

	WHEN("variable was declared")
	{
		CCalculator calculator;
		calculator.SetVariables("perem");
		
		CHECK(calculator.SetVariableValue("perem", 3.14));

		CCalculator::VariablesContainer sample;
		sample = { {"perem", 3.14} };
		CHECK(sample == calculator.GetVariables());
	}

	WHEN("variable not declared")
	{
		CCalculator calculator;
		CHECK(calculator.SetVariableValue("perem", 3.14));

		CCalculator::VariablesContainer sample;
		sample = { {"perem", 3.14} };
		CHECK(sample == calculator.GetVariables());
	}
}

TEST_CASE("set the value of the variable the passed variable")
{
	CCalculator::VariablesContainer fullSample;
	fullSample = {
		{"expVar", 3.14},
		{"impVar", 3.14}
	};

	WHEN("export variable does not exist")
	{
		CCalculator calculator;
		CHECK(!calculator.SetVariableValue("variable", "no_name"));
		CHECK(calculator.GetVariables().empty());
	}

	WHEN("import variable is incorrect")
	{
		CCalculator calculator;
		calculator.SetVariableValue("expVar", 3.14);
		CHECK(!calculator.SetVariableValue("1_inCorrect", "expVar"));

		CCalculator::VariablesContainer sample;
		sample = { {"expVar", 3.14} };
		CHECK(sample == calculator.GetVariables());
	}

	WHEN("import variable was not declared")
	{
		CCalculator calculator;
		calculator.SetVariableValue("expVar", 3.14);
		CHECK(calculator.SetVariableValue("impVar", "expVar"));

		CHECK(fullSample == calculator.GetVariables());
	}

	WHEN("empty import variable declared")
	{
		CCalculator calculator;
		calculator.SetVariableValue("expVar", 3.14);
		calculator.SetVariables("impVar");
		CHECK(calculator.SetVariableValue("impVar", "expVar"));

		CHECK(fullSample == calculator.GetVariables());
	}

	WHEN("filled import variable declared")
	{
		CCalculator calculator;
		calculator.SetVariableValue("expVar", 3.14);
		calculator.SetVariableValue("impVar", 0);
		CHECK(calculator.SetVariableValue("impVar", "expVar"));

		CHECK(fullSample == calculator.GetVariables());
	}

	WHEN("get value from function")
	{
		CCalculator calculator;
		calculator.SetVariableValue("expVar", 3.14);
		calculator.SetFunction("firstFunction", "expVar");
		CHECK(calculator.SetVariableValue("impVar", "firstFunction"));
		CHECK(fullSample == calculator.GetVariables());
	}
}

TEST_CASE("Check for add function")
{
	CCalculator calculator;
	calculator.SetVariables("x");
	calculator.SetVariables("y");
	CHECK(calculator.SetFunction("name", "x", "y", CCalculator::Operation::Addition));
	CHECK(calculator.SetFunction("new_name", "x", "name", CCalculator::Operation::Division));

	CHECK(calculator.SetFunction("Function", "name"));
	CHECK(calculator.SetFunction("Function_copy", "x"));
}

TEST_CASE("Check for correct data")
{
	CCalculator calculator;
	calculator.SetVariables("x");
	calculator.SetVariables("y");
	calculator.SetFunction("name", "x", "y", CCalculator::Operation::Addition);

	WHEN("function receiving three values")
	{
		CHECK(!calculator.SetFunction("name", "x", "y", CCalculator::Operation::Addition));
		CHECK(!calculator.SetFunction("new_name", "no", "x", CCalculator::Operation::Addition));
		CHECK(!calculator.SetFunction("!@#$%name_1", "no", "x", CCalculator::Operation::Addition));
		CHECK(!calculator.SetFunction("!@#$%name_1", "no", "no2", CCalculator::Operation::Addition));
	}

	WHEN("The function accepts an identifier reference")
	{
		CHECK(!calculator.SetFunction("name", "x"));
		CHECK(!calculator.SetFunction("1_incorrect", "name"));
		CHECK(!calculator.SetFunction("correct", "no_id"));
		CHECK(!calculator.SetFunction("no_func", "no_var"));
	}
}

TEST_CASE("Check on get value variable")
{
	CCalculator calculator;
	calculator.SetVariableValue("x", 5);
	calculator.SetVariables("y");

	CHECK(calculator.GetValue("x").value() == 5);
	CHECK(calculator.GetValue("y") == std::nullopt);
}

TEST_CASE("Check on function calculation")
{
	CCalculator calculator;
	calculator.SetVariableValue("x", 5);
	calculator.SetVariableValue("y", 2);
	calculator.SetFunction("XPlusY", "x", "y", CCalculator::Operation::Addition);
	calculator.SetFunction("XDivisionY", "x", "y", CCalculator::Operation::Division);
	calculator.SetFunction("XMultiplicationY", "x", "y", CCalculator::Operation::Multiplication);
	calculator.SetFunction("XSubtractionY", "x", "y", CCalculator::Operation::Subtraction);
	calculator.SetFunction("valuesX", "x");

	CHECK(calculator.GetValue("XPlusY").value() == 7);
	CHECK(calculator.GetValue("XDivisionY").value() == 2.5);
	CHECK(calculator.GetValue("XMultiplicationY").value() == 10);
	CHECK(calculator.GetValue("XSubtractionY").value() == 3);
	CHECK(calculator.GetValue("valuesX").value() == 5);
}