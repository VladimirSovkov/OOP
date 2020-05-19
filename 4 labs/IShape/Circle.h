#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include "CPoint.h"
#include "ISolidShape.h"

const double PI = 3.1415926;

class CCircle: public ISolidShape
{
public:
	CCircle(CPoint& center, double radius, uint32_t outlineColor, uint32_t fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	void Draw(ICanvas& canvas) override;

	CPoint GetCenter() const;
	double GetRadius() const;

private:
	CPoint m_center;
	double m_radius;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};

