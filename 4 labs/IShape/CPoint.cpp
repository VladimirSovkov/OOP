#include "CPoint.h"
#include <iomanip>
#include <sstream>

CPoint::CPoint()
{
	this->x = 0;
	this->y = 0;
}

CPoint::CPoint(double x, double y)
{
	this->x = x;
	this->y = y;
}

std::string CPoint::ToString() const
{
	std::stringstream output;
	output << std::fixed << std::setprecision(2);
	output << x << ", " << y;
	return output.str();
}

bool CPoint::operator==(const CPoint& point) const
{
	return (this->x == point.x && this->y == point.y);
}
