#pragma once
#include <iostream>
#include "Calculator.h"

class CCalculator;

class CCalculatorControl
{
public:
	CCalculatorControl(std::istream& command, std::ostream& answer, CCalculator& calculator);
	bool AnswerCommand();

private:

	bool VariableDeclaration(const std::string& identifier);
	bool SetVariableValue(const std::string& expression);
	bool AddNewFunction(const std::string& expression);
	void PrintValueToOutputStream(const std::string& identifier) const;
	bool PrintValueIdentifier(const std::string& identifier) const;
	void PrintVariables() const;
	void PrintFunction() const ;


	std::istream& m_command;
	std::ostream& m_answer;
	CCalculator& m_calculator;
};

