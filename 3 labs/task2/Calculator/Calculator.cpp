#include "Calculator.h"
#include <regex>

using namespace std;

bool IsCorrectNameIdentifier(const std::string& name)
{
	smatch result;
	regex regularExpression("^[\\w]+$");
	if (!regex_search(name, result, regularExpression))
	{
		return false;
	}
	return !(isdigit(name[0]));
}

bool CCalculator::IsIdentifierDeclared(const std::string& name) const
{
	return IsVariableDeclared(name) || IsFunctionDeclared(name);
}

bool CCalculator::SetVariables(const std::string& name)
{
	if (IsCorrectDataToCreateVariable(name))
	{
		m_containerOfVariables.emplace(name, std::nullopt);
		return true;
	}
	return false;
}

bool CCalculator::IsCorrectDataToCreateVariable(const std::string& nameIdentifier) const
{
	return IsCorrectNameIdentifier(nameIdentifier) && !IsIdentifierDeclared(nameIdentifier);
}

bool CCalculator::IsCorrectDataToCreateFunction(const std::string& nameFunction,
		const std::string& nameFirstIdentifier, const std::string& nameSecondIdentifier) const 
{
	return (IsCorrectNameIdentifier(nameFunction) && !IsIdentifierDeclared(nameFunction)) &&
		   (IsCorrectNameIdentifier(nameFirstIdentifier) && IsIdentifierDeclared(nameFirstIdentifier)) &&
		   (IsCorrectNameIdentifier(nameSecondIdentifier) && IsIdentifierDeclared(nameSecondIdentifier));
}

bool CCalculator::IsCorrectDataToCreateFunction(const std::string& nameFunction, const std::string nameIdentifier) const
{
	return (IsCorrectNameIdentifier(nameFunction) && !IsIdentifierDeclared(nameFunction)) &&
		(IsCorrectNameIdentifier(nameIdentifier) && IsIdentifierDeclared(nameIdentifier));
}

bool CCalculator::SetFunction(const std::string& nameFunction, 
							const std::string& nameFirstIdentifier, 
							const std::string& nameSecondIdentifier, 
							const CCalculator::Operation& operation)
{
	if (!IsCorrectDataToCreateFunction(nameFunction, nameFirstIdentifier, nameSecondIdentifier))
	{
		return false;
	}
	
	CCalculator::Function function;
	function.nameFirstVariable = nameFirstIdentifier;
	function.nameSecondVariable = nameSecondIdentifier;
	function.typeOfOperation = operation;
	m_containerOfFunction.emplace(nameFunction, function);
	
	return true;
}

bool CCalculator::SetFunction(const string& nameFunction, const string& nameIdentifier)
{
	if (!IsCorrectDataToCreateFunction(nameFunction, nameIdentifier))
	{
		return false;
	}

	Function function;
	function.nameFirstVariable = nameIdentifier;
	function.nameSecondVariable = "";
	function.typeOfOperation = {};
	m_containerOfFunction.emplace(nameFunction, function);

	return true;
}

bool CCalculator::SetVariableValue(const string& name, double value)
{
	if (IsCorrectNameIdentifier(name))
	{
		SetVariables(name);
		m_containerOfVariables[name] = value;
		return true;
	}

	return false;
}

std::optional<double>CCalculator::CalculateFunction(const std::string& firstIdentifier,
	const std::string& secondIdentifier, CCalculator::Operation operation) const
{
	optional<double> firstValue = GetValue(firstIdentifier);
	optional<double> secondValue = GetValue(secondIdentifier);
	if (!firstValue || !secondValue)
	{
		return {};
	}

	if (operation == CCalculator::Operation::Addition)
	{
		return firstValue.value() + secondValue.value();
	} 
	else if (operation == CCalculator::Operation::Subtraction)
	{
		return firstValue.value() - secondValue.value();
	} 
	else if (operation == CCalculator::Operation::Multiplication)
	{
		return firstValue.value() * secondValue.value();
	}
	else if (operation == CCalculator::Operation::Division)
	{
		return firstValue.value() / secondValue.value();
	}
	else
	{
		return {};
	}
}

std::optional<double> CCalculator::GetValue(const std::string& name) const
{
	if (IsVariableDeclared(name))
	{
		return m_containerOfVariables.at(name);
	}

	if (IsFunctionDeclared(name))
	{
		Function function = m_containerOfFunction.at(name);
		if (function.nameSecondVariable.empty())
		{
			return GetValue(function.nameFirstVariable);
		}
		else
		{
			return CalculateFunction(function.nameFirstVariable,
				function.nameSecondVariable, function.typeOfOperation.value());
		}
	}
	return {};
}

bool CCalculator::IsVariableDeclared(const std::string& name) const 
{
	return !(m_containerOfVariables.find(name) == m_containerOfVariables.end());
}

bool CCalculator::IsFunctionDeclared(const std::string& name) const 
{
	return !(m_containerOfFunction.find(name) == m_containerOfFunction.end());
}

bool CCalculator::SetVariableValue(const std::string& importValueKey, const std::string& exportValueKey)
{
	if (!IsIdentifierDeclared(exportValueKey))
	{
		return false;
	}
	optional<double> valueKey = GetValue(exportValueKey);
	
	if (!IsIdentifierDeclared(importValueKey))
	{
		if (!SetVariables(importValueKey))
		{
			return false;
		}
	}
	
	m_containerOfVariables[importValueKey] = valueKey;
	return true;
}

CCalculator::VariablesContainer CCalculator::GetVariables() const
{
	return m_containerOfVariables;
}

CCalculator::FunctionContainer CCalculator::GetFunctions() const
{
	return m_containerOfFunction;
}