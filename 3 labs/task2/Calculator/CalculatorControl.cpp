#include "CalculatorControl.h"
#include <regex>
#include <sstream>
#include <optional>
#include <iomanip>

using namespace std;

CCalculatorControl::CCalculatorControl(std::istream& command, std::ostream& answer, CCalculator& calculator)
	:m_command(command),
	m_answer(answer),
	m_calculator(calculator)
{
}

CCalculator::Operation GetOperation(const string& operation)
{
	if (operation == "+")
	{
		return CCalculator::Operation::Addition;
	} 
	else if(operation == "-")
	{
		return CCalculator::Operation::Subtraction;
	}
	else if (operation == "*")
	{
		return CCalculator::Operation::Multiplication;
	}
	else if (operation == "/")
	{
		return CCalculator::Operation::Division;
	}
}

bool CCalculatorControl::AnswerCommand()
{
	string inputLine;
	getline(m_command, inputLine);
	smatch result;
	regex regularExpression("^(\\s*)(\\w+)(\\s*)([\\s\\S]*)?$");
	if (!regex_search(inputLine, result, regularExpression))
	{
		m_answer << "Incorrect command" << endl;
		return false;
	}
	string command = result[2];

	if (command == "var")
	{
		return VariableDeclaration(result[4]);
	}
	else if (command == "let")
	{
		return SetVariableValue(result[4]); 
	}
	else if (command == "fn")
	{
		return AddNewFunction(result[4]);
	}
	else if (command == "print")
	{
		return PrintValueIdentifier(result[4]);
	}
	else if (command == "printvars")
	{
		PrintVariables();
		return true;
	}
	else if (command == "printfns")
	{
		PrintFunction();
		return true;
	}
	else
	{
		m_answer << "Incorrect command" << endl;
		return false;
	}
}

bool CCalculatorControl::VariableDeclaration(const std::string& identifier)
{
	if (!m_calculator.SetVariables(identifier))
	{
		if (m_calculator.IsIdentifierDeclared(identifier))
		{
			m_answer << "repeat declaration of identifier" << endl;
 		}
		else
		{
			m_answer << "Incorrect identifier" << endl;
		}

		return false;
	}

	return true;
}

bool CCalculatorControl::SetVariableValue(const std::string& expression)
{
	smatch result;
	regex regularExpression("^(\\w+)(?:\\s*)(?:=)(?:\\s*)([\\+\\-\\w\\.]+)(?:\\s*)$");
	if (!regex_search(expression, result, regularExpression))
	{
		m_answer << "Incorrect command" << endl;
		return false;
	}

	string firtsIdentifier = result[1];
	string secondIdentifier = result[2];
	double value;
	istringstream streamSecondIdentifier(secondIdentifier);
	if (streamSecondIdentifier >> value)
	{
		if (!m_calculator.SetVariableValue(firtsIdentifier, value))
		{
			m_answer <<  "Incorrect identifier" << endl;
			return false;
		}
	}
	else
	{
		 if(!m_calculator.SetVariableValue(firtsIdentifier, secondIdentifier))
		 {
			 m_answer << "Incorrect identifier or Identifier " << secondIdentifier << " was not declared" << endl;
			 return false;
		 }
	}

	return true;
}

string OutputErrorWhenCreatingFunction(const CCalculator& calculator, const string& nameFunction,
	const string& firstIdentifier, const string& secondIdentifier)
{
	if (!calculator.IsIdentifierDeclared(firstIdentifier))
	{
		return "identifier \"" + firstIdentifier + "\" not declared";
	}
	else if (!secondIdentifier.empty() && !calculator.IsIdentifierDeclared(secondIdentifier))
	{
		return "identifier \"" + secondIdentifier + "\" not declared";
	}
	else if (calculator.IsIdentifierDeclared(nameFunction))
	{
		return "repeated declaration function " + nameFunction + " impossible";
	}
	else
	{ 
		return "Incorrect name function";
	}
}

bool CCalculatorControl::AddNewFunction(const std::string& expression)
{
	smatch result;
	regex regularExpression("^(\\w+)(?:\\s*)(?:=)(?:\\s*)(\\w+)(?:\\s*)(([\\+\\-\\*\\/])(?:\\s*)(\\w+)(?:\\s*))?$");
	if (!regex_search(expression, result, regularExpression))
	{
		m_answer << "Incorrect command" << endl;
		return false;
	}
	string nameFunction = result[1];
	string nameFirstIdentifier = result[2];
	string nameSecondIdentifier = result[5];

	if (nameSecondIdentifier.empty())
	{
		if (m_calculator.SetFunction(nameFunction, nameFirstIdentifier))
		{
			return true;
		}
	}
	else
	{
		CCalculator::Operation operation = GetOperation(result[4]);
		if (m_calculator.SetFunction(nameFunction, nameFirstIdentifier, nameSecondIdentifier, operation))
		{
			return true;
		}
	}

	m_answer << OutputErrorWhenCreatingFunction(m_calculator, nameFunction, nameFirstIdentifier, nameSecondIdentifier) << endl;

	return false;
}

void CCalculatorControl::PrintValueToOutputStream(const std::string& identifier) const
{
	optional<double> valueIdentifier = m_calculator.GetValue(identifier);
	if (!valueIdentifier)
	{
		m_answer << "nan" << endl;
	}
	else
	{
		m_answer << setprecision(3) << valueIdentifier.value() << endl;
	}
}

bool CCalculatorControl::PrintValueIdentifier(const std::string& identifier) const
{
	if (!m_calculator.IsIdentifierDeclared(identifier))
	{
		m_answer << "identifier \"" + identifier + "\" not declared" << endl;
		return false;
	}

	PrintValueToOutputStream(identifier);
	return true;
}

void CCalculatorControl::PrintVariables() const 
{
	CCalculator::VariablesContainer containerVariables = m_calculator.GetVariables();
	for (auto variable : containerVariables)
	{
		m_answer << variable.first << " : ";
		PrintValueToOutputStream(variable.first);
	}
}

void CCalculatorControl::PrintFunction() const
{
	CCalculator::FunctionContainer containerFunction = m_calculator.GetFunctions();
	for (auto function : containerFunction)
	{
		m_answer << function.first << " : ";
		PrintValueToOutputStream(function.first);
	}
}
