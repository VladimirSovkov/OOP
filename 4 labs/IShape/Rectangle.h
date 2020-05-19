#pragma once
#include "CPoint.h"
#include <string>
#include <sstream>
#include <iomanip>
#include "ISolidShape.h"


class CRectangle: public ISolidShape
{
public:
	CRectangle(const CPoint& leftTop, 
		double width, double height, uint32_t outlineColor, uint32_t fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	void Draw(ICanvas& canvas) override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_leftTop;
	double m_width;
	double m_height;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};

