#include "../../catch2/catch.hpp"
#include "../IShape/Triangle.h"
#include "MockCanvas.h"

TEST_CASE("check for get infomation Triangle")
{
	CPoint vertex1(4, 4);
	CPoint vertex2(2, 1);
	CPoint vertex3(6, 1);
	CTriangle triangle(vertex1, vertex2, vertex3, 0x00ff00, 0xff0000);

	CHECK(triangle.GetVertex1() == vertex1);
	CHECK(triangle.GetVertex2() == vertex2);
	CHECK(triangle.GetVertex3() == vertex3);
	CHECK(triangle.GetFillColor() == 0xff0000);
	CHECK(triangle.GetOutlineColor() == 0x00ff00);
}

TEST_CASE("check for counting values Triangle")
{
	CPoint vertex1(1, 1);
	CPoint vertex2(4, 5);
	CPoint vertex3(7, 1);
	CTriangle triangle(vertex1, vertex2, vertex3, 0x00ff00, 0xff0000);

	CHECK(triangle.GetArea() == 12.0);
	CHECK(triangle.GetPerimeter() == 16.0);
}

TEST_CASE("check get info to string Triangle")
{
	CPoint vertex1(4, 4);
	CPoint vertex2(2, 1);
	CPoint vertex3(6, 1);
	CTriangle triangle(vertex1, vertex2, vertex3, 0x00ff00, 0xff0000);

	std::stringstream output;
	output << "Shape: Triangle\n";
	output << "Area: 6.00\n";
	output << "Perimeter: 11.21\n";
	output << "vertex1: 4.00, 4.00\n";
	output << "vertex2: 2.00, 1.00\n";
	output << "vertex3: 6.00, 1.00\n";
	output << "Fill Color: ff0000\n";
	output << "Outline Color: 00ff00" << std::endl;

	CHECK(triangle.ToString() == output.str());
}

TEST_CASE("check method draw")
{
	CPoint vertex1(0, 0);
	CPoint vertex2(3, 3);
	CPoint vertex3(3, 0);

	CTriangle triangle(vertex1, vertex2, vertex2, 0x000000, 0x000000);
	CMockCanvas canvas;
	triangle.Draw(canvas);
	std::vector<CMockCanvas::MethodCanvas> sample = 
	{
		CMockCanvas::MethodCanvas::DrawLine, 
		CMockCanvas::MethodCanvas::DrawLine, 
		CMockCanvas::MethodCanvas::DrawLine, 
		CMockCanvas::MethodCanvas::FillPolygon
	};
	CHECK(canvas.GetMethodList() == sample);


}