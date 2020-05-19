#pragma once
#include "IShape.h"
#include "ICanvas.h"
#include "Canvas.h"
#include "CPoint.h"
#include "LineSegment.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include <vector>
#include <sstream>
#include <memory>

class CShapeControl
{
public:
	CShapeControl(std::istream& command, std::ostream& answer);
	bool AnswerCommand();
	void Info() const;
	void PrintShapeWithMaxArea() const;
	void PrintShapeWithMinPerimeter() const;
	void DrawShapes() const;

private:
	bool SetLineSegment(const std::vector<std::string>& valuesLineSegment);
	bool SetCircle(const std::vector<std::string>& valuesCircle);
	bool SetRectangle(const std::vector<std::string>& valuesRectangle);
	bool SetTriangle(const std::vector<std::string>& valuesTriangle);

	std::istream& m_command;
	std::ostream& m_answer;
	std::vector<std::shared_ptr<IShape>> m_listsOfShape;
};

