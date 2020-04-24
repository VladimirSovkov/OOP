#include "Car.h"
#include <map>
#include <vector>

std::map <int, std::vector <int>> AllowableSpeedOnGear{
	{-1, {0, 20}},
	{0, {0, 150}},
	{1, {0, 30}},
	{2, {20, 50}},
	{3, {30, 60}},
	{4, {40, 90}},
	{5, {50, 150}},
};
const int MAX_SPEED = 150;
const int MAX_GEAR = 6;

bool CCar::TurnOnEngine()
{
	m_isEngineOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (m_currentGearing == 0 && m_speed == 0)
	{
		m_isEngineOn = false;
		return true;
	}

	return false;
}

bool IsExceptionSituationToShiftGear(const int gear, const int m_speed, const int m_currentGearing)
{
	return (gear == 0) ||
		(gear == m_currentGearing) ||
		(gear == -1 && m_speed == 0) ||
		(gear == 1 && m_currentGearing == -1 && m_speed == 0);
}

bool CCar::SetGear(int gear) 
{
	if (!m_isEngineOn && gear != 0)
	{
		return false;
	}

	if (gear == 1 && m_drivingDirectionCar == DrivingDirection::Back)
	{
		return false;
	}

	if (IsExceptionSituationToShiftGear(gear, m_speed, m_currentGearing))
	{
		m_currentGearing = gear;
		return true;
	}

	if (gear > -1 && gear < MAX_GEAR && m_currentGearing != -1)
	{ 
		int maxSpeedForGear = AllowableSpeedOnGear[gear][1];
		int minSpeedForGear = AllowableSpeedOnGear[gear][0];
		if (minSpeedForGear <= m_speed && m_speed <= maxSpeedForGear)
		{
			m_currentGearing = gear;
			return true;
		}
	}

	return false;
}

bool IsIncorrectSituationToChangeSpeed(int maxSpeedForGear,		
										int minSpeedForGear,	
										int speed, 
										int m_speed,		
										int m_currentGear)
{
	return (speed > MAX_SPEED || speed < 0) ||
		(speed > m_speed && m_currentGear == 0) ||
		(minSpeedForGear > speed || speed > maxSpeedForGear);
}

bool CCar::SetSpeed(int speed)
{
	if (m_isEngineOn == false)
	{
		return false;
	}

	int maxSpeedForGear = AllowableSpeedOnGear[m_currentGearing][1];
	int minSpeedForGear = AllowableSpeedOnGear[m_currentGearing][0];
	if (IsIncorrectSituationToChangeSpeed(maxSpeedForGear, minSpeedForGear, speed, m_speed, m_currentGearing))
	{
		return false;
	}
	
	if (speed == 0)
	{
		m_drivingDirectionCar = DrivingDirection::StandStill;
	}
	else if (m_currentGearing == -1)
	{
		m_drivingDirectionCar = DrivingDirection::Back;
	}
	else
	{
		m_drivingDirectionCar = DrivingDirection::Forward;
	}

	m_speed = speed;
	return true;
}

bool CCar::GetIsEngineOn() const
{
	return m_isEngineOn;
}

DrivingDirection CCar::GetDrivingDirectionCar() const
{
	return m_drivingDirectionCar;
}

int CCar::GetGear() const
{
	return m_currentGearing;
}

unsigned int CCar::GetSpeed() const
{
	return m_speed;
}