#pragma once
#include <string>

class CPoint
{
public:
	CPoint();
	CPoint(double x, double y);
	
	double x;
	double y;
	
	std::string ToString() const;

	bool operator==(const CPoint& point) const;
};

