#include "Rectangle.h"

CRectangle::CRectangle(const CPoint& leftTop, double width, 
	double height, uint32_t outlineColor, uint32_t fillColor)
	:m_leftTop(leftTop),
	m_width(width),
	m_height(height),
	m_outlineColor(outlineColor),
	m_fillColor(fillColor)
{
}

double CRectangle::GetArea() const
{
	return m_height * m_width;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_height + m_width);
}

std::string CRectangle::ToString() const
{
	std::stringstream output;
	output << "Shape: Rectangle\n";
	output << std::fixed << std::setprecision(2);
	output << "Area: " << GetArea() << std::endl;
	output << "Perimeter: " << GetPerimeter() << std::endl;
	output << "Left top: " << m_leftTop.ToString() << std::endl;
	output << "Right bottom: " << GetRightBottom().ToString() << std::endl;
	output << "Height: " << m_height << std::endl;
	output << "Width: " << m_width << std::endl;
	output << std::hex;
	output << "Fill Color: " << std::setw(6) << std::setfill('0') << m_fillColor << std::endl;
	output << "Outline Color: " << std::setw(6) << std::setfill('0') << m_outlineColor << std::endl;

	return output.str();
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

void CRectangle::Draw(ICanvas& canvas)
{
	CPoint leftBottom(m_leftTop.x, m_leftTop.y - m_height);
	CPoint rightTop(m_leftTop.x + m_width, m_leftTop.y);
	CPoint rightBottom = GetRightBottom();
	std::vector<CPoint> pointList{ m_leftTop, rightTop, rightBottom, leftBottom };
	
	canvas.DrawLine(m_leftTop, rightTop, m_outlineColor);
	canvas.DrawLine(rightTop, rightBottom, m_outlineColor);
	canvas.DrawLine(rightBottom, leftBottom, m_outlineColor);
	canvas.DrawLine(leftBottom, m_leftTop, m_outlineColor);

	canvas.FillPolygon(pointList, m_fillColor);
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	CPoint rightBottom(m_leftTop.x + m_width, m_leftTop.y - m_height);
	return rightBottom;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}
