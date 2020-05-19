#include "Circle.h"
#include <math.h>

CCircle::CCircle(CPoint& center, double radius, uint32_t outlineColor, uint32_t fillColor)
	:m_center(center),
	m_radius(radius),
	m_outlineColor(outlineColor),
	m_fillColor(fillColor)
{
}

double CCircle::GetArea() const
{
	return PI * pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return 2.0 * PI * m_radius;
}

std::string CCircle::ToString() const
{
	std::stringstream output;
	output << std::fixed << std::setprecision(2);
	output << "Shape: Circle\n";
	output << "Area: " << GetArea() << std::endl;
	output << "Perimeter: " << GetPerimeter() << std::endl;
	output << "Centre: " << m_center.ToString() << std::endl;
	output << "Radius: "<< m_radius << std::endl;
	output << std::hex;
	output << "Fill Color: " << std::setw(6) << std::setfill('0') << m_fillColor << std::endl;
	output << "Outline Color: " << std::setw(6) << std::setfill('0') << m_outlineColor << std::endl;

	return output.str();
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

void CCircle::Draw(ICanvas& canvas)
{
	canvas.DrawCircle(m_center, m_radius, m_outlineColor);
	canvas.FillCircle(m_center, m_radius, m_fillColor);
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
