#pragma once
#include <iostream>
#include <string>
#include "Car.h"

class CCar;

class CCarControl
{
public:
	CCarControl(std::istream& command, std::ostream& answer, CCar& car);
	bool AnswerCommand();

private:
	void GetInfoCar();
	bool SetEngineOn();
	bool SetEnjineOff();
	bool SetSpeed(int speed);
	bool SetGear(int gear);

	CCar& m_car;
	std::istream& m_command;
	std::ostream& m_answer;
};



