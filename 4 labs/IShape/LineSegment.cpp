#include "LineSegment.h"

CLineSegment::CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t outlineColor)
	:m_startPoint(startPoint),
	m_endPoint(endPoint),
	m_outlineColor(outlineColor)
{
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return sqrt(pow(m_startPoint.x - m_endPoint.x, 2) + pow(m_startPoint.y - m_endPoint.y, 2));
}

std::string CLineSegment::ToString() const
{
	std::stringstream output;
	output << std::fixed << std::setprecision(2);
	output << "Shape: Line\n";
	output << "Area: " << GetArea() << std::endl;
	output << "Perimeter: " << GetPerimeter() << std::endl;
	output << "Start point:  " << m_startPoint.ToString() << std::endl;
	output << "End point: " << m_endPoint.ToString() << std::endl;
	output << std::hex;
	output << "Outline Color: " << std::setw(6) << std::setfill('0') << m_outlineColor << std::endl;

	return output.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

void CLineSegment::Draw(ICanvas& canvas)
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}
