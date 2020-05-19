#include "../../catch2/catch.hpp"
#include "../IShape/Rectangle.h"
#include "MockCanvas.h"

TEST_CASE("check for get infomation Rectangle")
{
	CPoint leftTop(2, 5);
	CRectangle rectangle(leftTop, 10, 5, 0x00ff00, 0xff0000);
	CHECK(rectangle.GetLeftTop() == leftTop);
	CHECK(rectangle.GetWidth() == 10);
	CHECK(rectangle.GetHeight() == 5);
	CHECK(rectangle.GetOutlineColor() == 0x00ff00);
	CHECK(rectangle.GetFillColor() == 0xff0000);
}

TEST_CASE("check for counting values Rectangle")
{
	CPoint leftTop(2, 5);
	CRectangle rectangle(leftTop, 10, 5, 0x00ff00, 0xff0000);
	CPoint rightBottom(leftTop.x + 10, leftTop.y - 5);
	CHECK(rectangle.GetRightBottom() == rightBottom);
	CHECK(rectangle.GetArea() == 50);
	CHECK(rectangle.GetPerimeter() == 30);
}

TEST_CASE("check for get info to string Rectangle")
{
	CPoint leftTop(2, 5);
	CRectangle rectangle(leftTop, 10, 5, 0x00ff00, 0xff0000);
	std::stringstream output;
	output << "Shape: Rectangle\n";
	output << "Area: 50.00\n";
	output << "Perimeter: 30.00\n";
	output << "Left top: 2.00, 5.00\n";
	output << "Right bottom: 12.00, 0.00\n";
	output << "Height: 5.00\n";
	output << "Width: 10.00\n";
	output << "Fill Color: ff0000\n";
	output << "Outline Color: 00ff00\n";

	CHECK(rectangle.ToString() == output.str());
}

TEST_CASE("check method Draw in rectangle")
{
	CPoint topLeft(0, 4);
	CRectangle rectangle(topLeft, 5, 3, 0x000000, 0x000000);
	CMockCanvas canvas;
	rectangle.Draw(canvas);
	std::vector<CMockCanvas::MethodCanvas> sample =
	{
		CMockCanvas::MethodCanvas::DrawLine,
		CMockCanvas::MethodCanvas::DrawLine,
		CMockCanvas::MethodCanvas::DrawLine,
		CMockCanvas::MethodCanvas::DrawLine,
		CMockCanvas::MethodCanvas::FillPolygon
	};
	CHECK(canvas.GetMethodList() == sample);
}