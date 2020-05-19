#include <iostream>
#include "ShapeControl.h"
#include <GLFW/glfw3.h>

int main()
{
	CShapeControl shapeControl(std::cin, std::cout);
	shapeControl.Info();

	while (!std::cin.eof() && !std::cin.fail())
	{
		shapeControl.AnswerCommand();
	}

	std::cout << "Max Area: \n";
	shapeControl.PrintShapeWithMaxArea();
	std::cout << "\nMin perimeter:" << std::endl;
	shapeControl.PrintShapeWithMinPerimeter();
	shapeControl.DrawShapes();

	return 0;
}