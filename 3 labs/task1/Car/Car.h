#pragma once



class CCar
{
public:
	enum class DrivingDirection
	{
		Forward,
		Back,
		StandStill
	};

	bool TurnOnEngine(); 
	bool TurnOffEngine(); 
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	
	bool GetIsEngineOn() const; 
	DrivingDirection GetDrivingDirectionCar() const; 
	int GetGear() const; 
	int GetSpeed() const;  

private:
	bool m_isEngineOn = false;
	int m_speed = 0;
	int m_currentGearing = 0;
};

