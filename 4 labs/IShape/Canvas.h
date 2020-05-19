#pragma once
#include "ICanvas.h"


struct RGB
{
	int red = 0;
	int green = 0;
	int blue = 0;
};

class CCanvas : public ICanvas
{
public:
	CCanvas(GLFWwindow* window);
	
	const int NUMBER_SEGMENTS = 100;
	const double PI_X_2 = 2.0 * 3.1415926;

	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override;
	void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) override;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor) override;
	void FillCircle(CPoint center, double radius, uint32_t fillColor) override;
private:
	
	GLFWwindow* m_window;
};