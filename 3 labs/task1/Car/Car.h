#pragma once

enum class DrivingDirection
{
	Forward,
	Back,
	StandStill
};

class CCar
{
public:
	bool TurnOnEngine(); 
	bool TurnOffEngine(); 
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	
	bool GetIsEngineOn() const; 
	DrivingDirection GetDrivingDirectionCar() const; 
	int GetGear() const; 
	unsigned int GetSpeed() const;  

private:
	bool m_isEngineOn = false;
	DrivingDirection m_drivingDirectionCar = DrivingDirection::StandStill;
	int m_speed = 0;
	int m_currentGearing = 0;
};

