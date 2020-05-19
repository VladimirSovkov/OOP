#include "../../catch2/catch.hpp"
#include "../IShape/ShapeControl.h"
#include <sstream>

void ExpectOperationSuccess(const std::string& command, const std::string& answer)
{
	std::stringstream input, output;
	CShapeControl shapeControl(input, output);
	input << command;
	CHECK(shapeControl.AnswerCommand());
	CHECK(answer == output.str());
}

void ExpectOperationFailure(const std::string& command, const std::string& answer)
{
	std::stringstream input, output;
	CShapeControl shapeControl(input, output);
	input << command;
	CHECK(!shapeControl.AnswerCommand());
	CHECK(answer == output.str());
}

TEST_CASE("set shapes with correct ñommand")
{
	std::string command = "circle 0.5 1 1 ffdf00 ffee73";
	ExpectOperationSuccess(command, "");

	command = "line 0.5 0 0.5 1 ffffff";
	ExpectOperationSuccess(command, "");

	command = "rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00";
	ExpectOperationSuccess(command, "");

	command = "triangle 0.0 0.0 4.0 0.0 4.0 5.0 00ff00 ff0000";
	ExpectOperationSuccess(command, "");
}

TEST_CASE("Incorrect comand for creating shapes")
{
	std::string command = "circle 1 1 ffdf00 ffee73";
	std::string answer = "Incorrect command\ncircle 1.0 0.0 2.0 00ff00 ff0000\n";
	ExpectOperationFailure(command, answer); 
	
	command = "circle 0.5 1 1 gfdf00 gfee73";
	ExpectOperationFailure(command, answer);

	command = "circle a 1 ffdf00 ffee73";
	ExpectOperationFailure(command, answer);

	command = "line 1 ffdf00 ffee73";
	answer = "Incorrect command\nline 1.1 1.1 5.0 5.0 00ff00\n";
	ExpectOperationFailure(command, answer);

	command = "rectangle";
	answer = "Incorrect command\nrectangle 10.3 20.15 30.7 40.4 ff0000 00ff00\n";
	ExpectOperationFailure(command, answer);

	command = "triangle 0.0 4.0 0.0 4.0 5.0 00ff00 ff0000";
	answer = "Incorrect command\ntriangle 0.0 0.0 4.0 0.0 4.0 5.0 00ff00 ff0000\n";
	ExpectOperationFailure(command, answer);
}

TEST_CASE("check output infofmation about the shape")
{
	std::stringstream input, output;
	CShapeControl shapeControl(input, output);
	shapeControl.Info();
	std::stringstream answer;
	answer << "Information\n";
	answer << "line <first point> <second point> <color>\n";
	answer << "rectangle <upper left point> <width> <height> <outline color> <fill color>\n";
	answer << "circle <center point> <radius> <outline color> <fill color>\n";
	answer << "triangle <vertex 1> <vertex 2> <vertex 2> <outline color> <fill color>\n";
	CHECK(answer.str() == output.str());
}

TEST_CASE("output info the shape with the max area")
{
	std::stringstream input, output;
	CShapeControl shapeControl(input, output);
	input << "rectangle 0 3 2 1 00ff00 ff0000" << std::endl;
	shapeControl.AnswerCommand();
	input << "rectangle 0 4 4 3 000000 000000" << std::endl;
	shapeControl.AnswerCommand();
	std::stringstream answer;
	answer << "Shape: Rectangle\n";
	answer << "Area: 12.00\n";
	answer << "Perimeter: 14.00\n";
	answer << "Left top: 0.00, 4.00\n";
	answer << "Right bottom: 4.00, 1.00\n";
	answer << "Height: 3.00\n";
	answer << "Width: 4.00\n";
	answer << "Fill Color: 000000\n";
	answer << "Outline Color: 000000\n";
	shapeControl.PrintShapeWithMaxArea();
	CHECK(answer.str() == output.str());
}

TEST_CASE("output info the shape with the min perimeter")
{
	std::stringstream input, output;
	CShapeControl shapeControl(input, output);
	input << "rectangle 0 3 2 1 000000 000000" << std::endl;
	shapeControl.AnswerCommand();
	input << "rectangle 0 4 4 3 000000 000000" << std::endl;
	shapeControl.AnswerCommand();
	std::stringstream answer;
	answer << "Shape: Rectangle\n";
	answer << "Area: 2.00\n";
	answer << "Perimeter: 6.00\n";
	answer << "Left top: 0.00, 3.00\n";
	answer << "Right bottom: 2.00, 2.00\n";
	answer << "Height: 1.00\n";
	answer << "Width: 2.00\n";
	answer << "Fill Color: 000000\n";
	answer << "Outline Color: 000000\n";
	shapeControl.PrintShapeWithMinPerimeter();
	CHECK(answer.str() == output.str());
}