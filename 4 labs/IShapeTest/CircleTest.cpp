#include "../../catch2/catch.hpp"
#include "../IShape/Circle.h"
#include "MockCanvas.h"

TEST_CASE("Check in get value")
{
	CPoint circleÑenter(3, 4);
	double radius = 3.0;
	uint32_t outlineColor = 0xff0000;
	uint32_t fillColor = 0x00ff00;
	CCircle circle(circleÑenter, radius, outlineColor, fillColor);
	double area = PI * pow(radius, 2);
	double Perimetr = 2 * PI * radius;

	CHECK(circle.GetCenter() == circleÑenter);
	CHECK(circle.GetRadius() == radius);
	CHECK(circle.GetOutlineColor() == outlineColor);
	CHECK(circle.GetFillColor() == fillColor);
	CHECK(circle.GetArea() == area);
	CHECK(circle.GetPerimeter() == Perimetr);
}

TEST_CASE("check output ToString")
{
	CPoint circleÑenter(3, 4);
	CCircle circle(circleÑenter, 3.0, 0x00ff00, 0xff0000);
	std::stringstream output;
	output << "Shape: Circle\n";
	output << "Area: 28.27\n";
	output << "Perimeter: 18.85\n";
	output << "Centre: 3.00, 4.00\n";
	output << "Radius: 3.00\n";
	output << "Fill Color: ff0000\n";
	output << "Outline Color: 00ff00\n";
	CHECK(circle.ToString() == output.str());
}

TEST_CASE()
{
	CPoint center(3, 3);

	CCircle circle(center, 2, 0x000000, 0x000000);
	CMockCanvas canvas;
	circle.Draw(canvas);

	std::vector<CMockCanvas::MethodCanvas> sample =
	{
		CMockCanvas::MethodCanvas::DrawCircle,
		CMockCanvas::MethodCanvas::FillCircle
	};

	CHECK(sample == canvas.GetMethodList());
}