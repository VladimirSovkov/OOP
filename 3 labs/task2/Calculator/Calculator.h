#pragma once
#include <map>
#include <string>
#include <optional>

class CCalculator
{
public:
	enum class Operation
	{
		Addition,
		Subtraction,
		Multiplication,
		Division,
	};

	struct Function
	{
		std::string nameFirstVariable;
		std::string nameSecondVariable;
		std::optional<Operation> typeOfOperation;
	};

	typedef std::map<std::string, std::optional<double>> VariablesContainer;
	typedef std::map<std::string, Function> FunctionContainer;

	bool SetVariables(const std::string& name);
	bool SetVariableValue(const std::string& name, double value);
	bool SetVariableValue(const std::string& importValueKey, const std::string& exportValueKey);

	bool SetFunction(const std::string& nameFunction,
					const std::string& nameFirstIdentifier,
					const std::string& nameSecondIdentifier,
					const CCalculator::Operation& operation);
	bool SetFunction(const std::string& nameFunction, const std::string& nameIdentifier);

	CCalculator::VariablesContainer GetVariables() const;
	CCalculator::FunctionContainer GetFunctions() const;
	std::optional<double> GetValue(const std::string& name) const;

	bool IsIdentifierDeclared(const std::string& name) const;

private:
	bool IsVariableDeclared(const std::string& name) const;
	bool IsFunctionDeclared(const std::string& name) const;

	bool IsCorrectDataToCreateVariable(const std::string& nameIdentifier) const;
	bool IsCorrectDataToCreateFunction(const std::string& nameFunction,
		const std::string& nameFirstIdentifier, const std::string& nameSecondIdentifier) const;
	bool IsCorrectDataToCreateFunction(const std::string& nameFunction, const std::string nameIdentifier) const; 

	std::optional<double> CalculateFunction(const std::string& fisrtIdentifier,
		const std::string& secondIdentifier, CCalculator::Operation operation) const;

	VariablesContainer m_containerOfVariables;
	FunctionContainer m_containerOfFunction;
};

