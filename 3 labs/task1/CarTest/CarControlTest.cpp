#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Car/CarControl.h"

TEST_CASE("entered an invalid command"){
	WHEN("Enter any word")
	{
		CCar car;
		std::istringstream command ("no_command");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);

		CHECK(!carControl.AnswerCommand());
		CHECK(answer.str() == "Incorrect command\n");
	}

	WHEN("I enter a word similar not a command")
	{
		CCar car;
		std::istringstream command("info");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(!carControl.AnswerCommand());
		CHECK(answer.str() == "Incorrect command\n");
	}

	WHEN("I enter a word similar not a command")
	{
		CCar car;
		std::istringstream command("SetGear <10");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(!carControl.AnswerCommand());
		CHECK(answer.str() == "Incorrect command\n");
	}

	WHEN("I enter a word similar not a command")
	{
		CCar car;
		std::istringstream command("SetSpeed 10>");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(!carControl.AnswerCommand());
		CHECK(answer.str() == "Incorrect command\n");
	}

	WHEN("I enter a word similar not a command")
	{
		CCar car;
		std::istringstream command("SetSpeed >10<");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(!carControl.AnswerCommand());
		CHECK(answer.str() == "Incorrect command\n");
	}

	WHEN("Command without value")
	{
		CCar car;
		std::istringstream command("Info <10>");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(!carControl.AnswerCommand());
		CHECK(answer.str() == "Incorrect command\n");
	}

	WHEN("Command with value")
	{
		CCar car;
		std::istringstream command("SetSpeed ");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(!carControl.AnswerCommand());
		CHECK(answer.str() == "Incorrect command\n");
	}
}

TEST_CASE("verification of the information provided")
{
	WHEN("Checking Information on default Values")
	{
		CCar car;
		std::istringstream command("Info");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(carControl.AnswerCommand());
		CHECK(answer.str() == "Engine:\tStopped\nDirection:\tStand Still\nSpeed:\t\t0\nGear:\t\t0\n");
	}
	
	WHEN("checking information after changing the state of the car")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		std::istringstream command("Info");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(carControl.AnswerCommand());
		CHECK(answer.str() == "Engine:\tPower\nDirection:\tForward\nSpeed:\t\t20\nGear:\t\t1\n");
	}
}

TEST_CASE("engine start")
{
	CCar car;
	std::istringstream command("EngineOn");
	std::ostringstream answer;
	CCarControl carControl(command, answer, car);
	CHECK(carControl.AnswerCommand());
	CHECK(car.GetIsEngineOn());
}

TEST_CASE("engine off")
{
	CCar car;
	car.TurnOnEngine();
	WHEN("correct engine off")
	{
		car.TurnOnEngine();
		std::istringstream command("EngineOff");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(carControl.AnswerCommand());
		CHECK(!car.GetIsEngineOn());
	}

	WHEN("The engine cannot turn off due to gaer")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		std::istringstream command("EngineOff");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(!carControl.AnswerCommand());
		CHECK(car.GetIsEngineOn());
	}

	WHEN("The engine cannot turn off due to speed")
	{
		car.SetGear(1);
		car.SetSpeed(10);
		car.SetGear(0);
		std::istringstream command("EngineOff");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(!carControl.AnswerCommand());
		CHECK(car.GetIsEngineOn());
	}

	WHEN("The engine cannot turn off due to speed and gear")
	{
		car.SetGear(1);
		car.SetSpeed(10);
		std::istringstream command("EngineOff");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(!carControl.AnswerCommand());
		CHECK(car.GetIsEngineOn());
	}
}

TEST_CASE("Speed change")
{
	CCar car;
	WHEN("Correct Speed Change")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		std::istringstream command("SetSpeed <20>");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(carControl.AnswerCommand());
		CHECK(car.GetSpeed() == 20);
	}

	WHEN("it is impossible to change the speed since neutral gear")
	{
		car.TurnOnEngine();
		std::istringstream command("SetSpeed <20>");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(!carControl.AnswerCommand());
		CHECK(answer.str() == "on the neutral gear the speed changes only to in favor of zero\n");
		CHECK(car.GetSpeed() == 0);
	}

	WHEN("incorrect speed range")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		std::istringstream command("SetSpeed <100>");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(!carControl.AnswerCommand());
		CHECK(answer.str() == "incorrect speed range\n");
		CHECK(car.GetSpeed() == 0);
	}
}

TEST_CASE("gear shifting")
{
	CCar car;
	WHEN("correct gear shifting")
	{
		car.TurnOnEngine();
		std::istringstream command("SetGear <1>");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(carControl.AnswerCommand());
		CHECK(car.GetGear() == 1);
	}

	WHEN("transmission is incorrect speed range")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		std::istringstream command("SetGear <5>");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(!carControl.AnswerCommand());
		CHECK(answer.str() == "Incorrect speed range\n");
		CHECK(car.GetGear() == 1);
	}

	WHEN("Shifting gears on engine off")
	{
		std::istringstream command("SetGear <1>");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(!carControl.AnswerCommand());
		CHECK(answer.str() == "switching off the engine is prohibited, except switching to neutral gear\n");
	}

	WHEN("shifting forward gears incorrectly when reversing")
	{
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);
		car.SetGear(0);
		std::istringstream command("SetGear <1>");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(!carControl.AnswerCommand());
		CHECK(answer.str() == "cannot switch to forward gear, when the car moves back\n");
		CHECK(car.GetGear() == 0);
	}

	WHEN("reverse gear at speed")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		std::istringstream command("SetGear <-1>");
		std::ostringstream answer;
		CCarControl carControl(command, answer, car);
		CHECK(!carControl.AnswerCommand());
		CHECK(answer.str() == "reverse gear not possible at speed\n");
		CHECK(car.GetGear() == 1);
	}
}