#include "CarControl.h"
#include <optional>
#include <regex>

using namespace std;

CCarControl::CCarControl(std::istream& command, std::ostream& answer, CCar& car)
	:m_command(command),
	m_answer(answer),
	m_car(car)
{
}

string GetDrivingDirection(const DrivingDirection& Direction)
{
	if (Direction == DrivingDirection::Back)
	{
		return "Back";
	}
	else if	(Direction == DrivingDirection::Forward)
	{
		return "Forward";
	}
	else if (Direction == DrivingDirection::StandStill)
	{
		return "Stand Still";
	}
	else
	{
		return "";
	}
}

string GetEngineStates(const CCar& car)
{
	if (car.GetIsEngineOn())
	{
		return "Power";
	}
	else
	{
		return "Stopped";
	}
}

optional<int> GetValueCommand(const string& line)
{
	if (line.empty())
	{
		return {};
	}
	return atoi(line.c_str());
}

bool CCarControl::AnswerCommand()
{
	string commandLine;
	getline(m_command, commandLine);
	smatch result;
	regex regularExpression("^(\\s*)(\\w+)(\\s*)(<\\s*(-*\\d+)\\s*>)?(\\s*)$");
	if (!regex_search(commandLine, result, regularExpression))
	{
		m_answer << "Incorrect command" << endl;
		return false;
	}
	
	optional<int> valueCommand = GetValueCommand(result[5]);
	commandLine = result[2];
	if (commandLine == "Info" && !valueCommand)
	{
		GetInfoCar();
		return true;
	}
	else if (commandLine == "EngineOn" && !valueCommand)
	{
		return SetEngineOn();
	}
	else if(commandLine == "EngineOff" && !valueCommand)
	{
		return SetEnjineOff();
	}
	else if (commandLine == "SetGear" && valueCommand)
	{
		return SetGear(valueCommand.value());
	}
	else if (commandLine == "SetSpeed" && valueCommand)
	{
		return SetSpeed(valueCommand.value());
	}
	else
	{
		m_answer << "Incorrect command" << endl;
		return false;
	}
}

void CCarControl::GetInfoCar()
{
	m_answer << "Engine:\t" << GetEngineStates(m_car) << endl;
	m_answer << "Direction:\t" << GetDrivingDirection(m_car.GetDrivingDirectionCar()) << endl;
	m_answer << "Speed:\t\t" << m_car.GetSpeed() << endl;
	m_answer << "Gear:\t\t" << m_car.GetGear() << endl;
}

bool CCarControl::SetEngineOn()
{
	return m_car.TurnOnEngine();
}

bool CCarControl::SetEnjineOff()
{
	return m_car.TurnOffEngine();
}

bool CCarControl::SetSpeed(int speed)
{
	if (m_car.SetSpeed(speed))
	{
		return true;
	}
	else
	{
		if (m_car.GetGear() == 0)
		{
			m_answer << "on the neutral gear the speed changes only to in favor of zero" << endl;
		}
		else
		{
			m_answer << "incorrect speed range" << endl;
		}
		return false;
	}
}

bool CCarControl::SetGear(int gear)
{
	if (m_car.SetGear(gear))
	{
		return true;
	}
	else
	{
		if (gear == -1)
		{
			m_answer << "reverse gear not possible at speed" << endl;
		}
		else if (gear > 0 && m_car.GetDrivingDirectionCar() == DrivingDirection::Back)
		{
			m_answer << "cannot switch to forward gear, when the car moves back" << endl;
		}
		else if (!m_car.GetIsEngineOn() && gear != 0)
		{
			m_answer << "switching off the engine is prohibited, except switching to neutral gear" << endl;
		}
		else
		{
			m_answer << "Incorrect speed range" << endl;
		}
		return false;
	}
}
