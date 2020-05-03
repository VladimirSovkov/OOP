#include "../../../catch2/catch.hpp"
#include "../Car/CarControl.h"
#include <sstream>

void ExpectOperationSuccess(const std::string& command, const std::string& answer, CCar& car)
{
	std::stringstream input, output;
	CCarControl carControl(input, output, car);
	input << command;
	CHECK(carControl.AnswerCommand());
	CHECK(answer == output.str());
}

void ExpectOperationFailure(const std::string& command, const std::string& answer, CCar& car)
{
	std::stringstream input, output;
	CCarControl carControl(input, output, car);
	input << command;
	CHECK(!carControl.AnswerCommand());
	CHECK(answer == output.str());
}

TEST_CASE("entered an incorrect command")
{
	CCar car;
	ExpectOperationFailure("hello world", "Incorrect command\n", car);
	ExpectOperationFailure("Info 10", "Incorrect command\n", car);
	ExpectOperationFailure("SetSpeed ", "Incorrect command\n", car);
	ExpectOperationFailure("info", "Incorrect command\n", car);
}

TEST_CASE("verification of the information provided")
{
	CCar car;
	ExpectOperationSuccess("Info", "Engine:\tStopped\nDirection:\tStand Still\nSpeed:\t\t0\nGear:\t\t0\n", car);

	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	ExpectOperationSuccess("Info", "Engine:\tPower\nDirection:\tForward\nSpeed:\t\t20\nGear:\t\t1\n", car);
}

TEST_CASE("engine start")
{
	CCar car;
	ExpectOperationSuccess("EngineOn", "", car);
}

TEST_CASE("engine off")
{
	CCar car;
	car.TurnOnEngine();
	ExpectOperationSuccess("EngineOff", "", car);
	CHECK(!car.GetIsEngineOn());

	car.TurnOnEngine();
	car.SetGear(1);
	ExpectOperationFailure("EngineOff", "", car);
	CHECK(car.GetIsEngineOn());
	
	car.SetSpeed(10);
	car.SetGear(0);

	car.SetGear(1);
	ExpectOperationFailure("EngineOff", "", car);
}

TEST_CASE("Speed change")
{
	CCar car;
	car.TurnOnEngine();

	WHEN("Correct Speed Change")
	{
		car.SetGear(1);
		ExpectOperationSuccess("SetSpeed 20", "", car);
		CHECK(car.GetSpeed() == 20);
	}

	WHEN("it is impossible to change the speed since neutral gear")
	{
		ExpectOperationFailure("SetSpeed 20", "on the neutral gear the speed changes only to in favor of zero\n", car);
		CHECK(car.GetSpeed() == 0);
	}

	WHEN("incorrect speed range")
	{
		car.SetGear(1);
		ExpectOperationFailure("SetSpeed 100", "incorrect speed range\n", car);
		CHECK(car.GetSpeed() == 0);
	}
}

TEST_CASE("gear shifting")
{
	CCar car;
	WHEN("correct gear shifting")
	{
		car.TurnOnEngine();
		ExpectOperationSuccess("SetGear 1", "", car);
		CHECK(car.GetGear() == 1);
	}

	WHEN("transmission is incorrect speed range")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		ExpectOperationFailure("SetGear 5", "Incorrect speed range\n", car);
		CHECK(car.GetGear() == 1);
	}

	WHEN("Shifting gears on engine off")
	{
		ExpectOperationFailure("SetGear 1", "The engine is off. Switching impossible\n", car);
	}

	WHEN("shifting forward gears incorrectly when reversing")
	{
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);
		car.SetGear(0);
		ExpectOperationFailure("SetGear 1", "cannot switch to forward gear, when the car moves back\n", car);
		CHECK(car.GetGear() == 0);
	}

	WHEN("reverse gear at speed")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		ExpectOperationFailure("SetGear -1", "reverse gear not possible at speed\n", car);
		CHECK(car.GetGear() == 1);
	}
}