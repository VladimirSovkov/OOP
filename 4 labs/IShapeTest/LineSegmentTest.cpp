#include "../../catch2/catch.hpp"
#include "../IShape/LineSegment.h"
#include "MockCanvas.h"

TEST_CASE("check output values LineSegment")
{
	CPoint startPoint(0, 0);
	CPoint endPoint(3, 4);
	CLineSegment line(startPoint, endPoint, 0x00ff00);

	CHECK(line.GetArea() == 0);
	CHECK(line.GetStartPoint() == startPoint);
	CHECK(line.GetEndPoint() == endPoint);
	CHECK(line.GetPerimeter() == 5.0);
	CHECK(line.GetOutlineColor() == 0x00ff00);
}

TEST_CASE("check output information LineSegment")
{
	CPoint startPoint(0, 0);
	CPoint endPoint(3, 4);
	CLineSegment line(startPoint, endPoint, 0x00ff00);
	std::stringstream output;
	output << "Shape: Line\n";
	output << "Area: 0.00\n";
	output << "Perimeter: 5.00\n";
	output << "Start point:  0.00, 0.00\n";
	output << "End point: 3.00, 4.00\n";
	output << "Outline Color: 00ff00" << std::endl;

	CHECK(line.ToString() == output.str());
}

TEST_CASE("check method draw in line segment")
{
	CPoint point1(0, 0);
	CPoint point2(5, 5);

	CLineSegment line(point1, point2, 0x000000);
	CMockCanvas canvas;
	line.Draw(canvas);
	std::vector<CMockCanvas::MethodCanvas> sample = { CMockCanvas::MethodCanvas::DrawLine };

	CHECK(sample == canvas.GetMethodList());
}