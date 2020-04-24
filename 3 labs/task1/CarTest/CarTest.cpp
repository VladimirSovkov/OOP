#include "../../../catch2/catch.hpp"
#include "../Car/Car.h"

TEST_CASE("validation of the creation of default values")
{
	CCar car;
	CHECK(car.GetDrivingDirectionCar() == DrivingDirection::StandStill);
	CHECK(car.GetGear() == 0);
	CHECK(!car.GetIsEngineOn());
	CHECK(car.GetSpeed() == 0);
}

TEST_CASE("Check turn on engine")
{
	CCar car;
	CHECK(car.TurnOnEngine());
	CHECK(car.GetIsEngineOn());
}

TEST_CASE("Check turn off engine")
{
	CCar car;
	CHECK(car.TurnOffEngine());
	CHECK(!car.GetIsEngineOn());
	car.TurnOnEngine();
	CHECK(car.TurnOffEngine());
	CHECK(!car.GetIsEngineOn());
}

TEST_CASE("check for engine off in different gears")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	CHECK(!car.TurnOffEngine());
	CHECK(car.GetIsEngineOn());

	car.TurnOnEngine();
	car.SetGear(-1);
	CHECK(!car.TurnOffEngine());
	CHECK(car.GetIsEngineOn());

	car.TurnOnEngine();
	car.SetGear(0);
	CHECK(car.TurnOffEngine());
}

TEST_CASE("check for engine shutdown at speed") 
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(15);
	car.SetGear(0);
	CHECK(!car.TurnOffEngine());

	car.SetSpeed(5);
	CHECK(!car.TurnOffEngine());
}

TEST_CASE("Gear shifting with engine off")
{
	CCar car;
	CHECK(!car.SetGear(1));
	CHECK(car.GetGear() == 0);

	CHECK(!car.SetGear(-1));

	CHECK(car.SetGear(0));
}

TEST_CASE("check for correct switching with engine on at zero speed")
{
	CCar car;
	car.TurnOnEngine();
	CHECK(car.SetGear(1));
	CHECK(car.GetGear() == 1);

	CHECK(car.SetGear(-1));
	CHECK(car.GetGear() == -1);

	CHECK(car.SetGear(1));
	CHECK(car.GetGear() == 1);

	CHECK(car.SetGear(1));
	CHECK(car.GetGear() == 1);

	CHECK(!car.SetGear(5));
	CHECK(car.GetGear() == 1);
}

TEST_CASE("gear shifting at various speeds")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	CHECK(car.SetGear(2));
	CHECK(car.GetGear() == 2);

	car.SetSpeed(40);
	CHECK(car.SetGear(3));
	CHECK(car.GetGear() == 3);

	CHECK(car.SetGear(0));
	CHECK(car.GetGear() == 0);

	CHECK(car.SetGear(3));
	CHECK(car.GetGear() == 3);

	CHECK(car.SetGear(0));
	
	car.SetSpeed(0);
	car.SetGear(-1);
	car.SetSpeed(15);
	CHECK(car.SetGear(0));
}

TEST_CASE("incorrect gear shifting at speed")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	CHECK(!car.SetGear(5));
	CHECK(car.GetGear() == 1);

	CHECK(!car.SetGear(-1));
	CHECK(car.GetGear() == 1);

	car.SetSpeed(0);
	car.SetGear(-1);
	car.SetSpeed(15);
	CHECK(!car.SetGear(1));
	CHECK(car.GetGear() == -1);

	car.SetGear(0);
	CHECK(!car.SetGear(-1));
	CHECK(!car.SetGear(1));
	CHECK(!car.SetGear(6));
	CHECK(!car.SetGear(-2));
	CHECK(car.GetGear() == 0);
	
}

TEST_CASE("set speed in various gears")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	CHECK(car.SetSpeed(20));
	CHECK(car.GetSpeed() == 20);
	CHECK(car.GetDrivingDirectionCar() == DrivingDirection::Forward);
	
	car.SetGear(0);
	CHECK(car.SetSpeed(0));
	CHECK(car.GetSpeed() == 0);
	CHECK(car.GetDrivingDirectionCar() == DrivingDirection::StandStill);

	car.SetGear(-1);
	CHECK(car.SetSpeed(20));
	CHECK(car.GetSpeed() == 20);
	CHECK(car.GetDrivingDirectionCar() == DrivingDirection::Back);

	CHECK(car.SetSpeed(5));
	CHECK(car.GetSpeed() == 5);
	CHECK(car.GetDrivingDirectionCar() == DrivingDirection::Back);

	CHECK(car.SetSpeed(5));

	car.SetSpeed(0);
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(60);
	car.SetGear(5);
	CHECK(car.SetSpeed(150));
	CHECK(car.GetSpeed() == 150);
}

TEST_CASE("change of speed to an incorrect value for a given gear")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	CHECK(!car.SetSpeed(100));
	CHECK(car.GetSpeed() == 0);
	
	car.SetGear(-1);
	CHECK(!car.SetSpeed(-10));
	CHECK(car.GetSpeed() == 0);

	car.SetGear(0);
	CHECK(!car.SetSpeed(-10));
	CHECK(car.GetSpeed() == 0);

	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(60);
	car.SetGear(5);
	CHECK(!car.SetSpeed(151));
	CHECK(!car.SetSpeed(200));
}