#include "Triangle.h"

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3,
	uint32_t outlineColor, uint32_t fillColor)
	: m_vertex1(vertex1),
	m_vertex2(vertex2),
	m_vertex3(vertex3),
	m_outlineColor(outlineColor),
	m_fillColor(fillColor)
{
}

double GetLengthSegment(const CPoint& firstPoint, const CPoint& secondPoint)
{
	double firstLine = firstPoint.x - secondPoint.x;
	double secondLine = firstPoint.y - secondPoint.y;
	return sqrt(pow(firstLine, 2) + pow(secondLine, 2));
}

double CTriangle::GetArea() const
{
	double halfPerimeter = GetPerimeter() / 2;
	double line1 = GetLengthSegment(m_vertex1, m_vertex2);
	double line2 = GetLengthSegment(m_vertex2, m_vertex3);
	double line3 = GetLengthSegment(m_vertex3, m_vertex1);
	return sqrt(halfPerimeter*(halfPerimeter - line1)*(halfPerimeter - line2)*(halfPerimeter - line3));
}

double CTriangle::GetPerimeter() const
{
	double line1 = GetLengthSegment(m_vertex1, m_vertex2);
	double line2 = GetLengthSegment(m_vertex2, m_vertex3);
	double line3 = GetLengthSegment(m_vertex3, m_vertex1);
	return line1 + line2 + line3;
}

std::string CTriangle::ToString() const
{
	std::stringstream output;
	output << "Shape: Triangle\n";
	output << std::fixed << std::setprecision(2);
	output << "Area: " << GetArea() << std::endl;
	output << "Perimeter: " << GetPerimeter() << std::endl;
	output << "vertex1: " << m_vertex1.ToString() << std::endl;
	output << "vertex2: " << m_vertex2.ToString() << std::endl;
	output << "vertex3: " << m_vertex3.ToString() << std::endl;
	output << std::hex;
	output << "Fill Color: " << std::setw(6) << std::setfill('0') << m_fillColor << std::endl;
	output << "Outline Color: " << std::setw(6) << std::setfill('0') << m_outlineColor << std::endl;

	return output.str();
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

void CTriangle::Draw(ICanvas& canvas)
{
	canvas.DrawLine(m_vertex1, m_vertex2, m_outlineColor);
	canvas.DrawLine(m_vertex2, m_vertex3, m_outlineColor);
	canvas.DrawLine(m_vertex3, m_vertex1, m_outlineColor);

	std::vector<CPoint> pointsList {m_vertex1, m_vertex2, m_vertex3};
	canvas.FillPolygon(pointsList, m_fillColor);
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}
