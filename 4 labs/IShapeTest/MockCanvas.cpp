#include "MockCanvas.h"

void CMockCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
	m_methodList.push_back(MethodCanvas::DrawLine);
}

void CMockCanvas::FillPolygon(std::vector<CPoint> points, uint32_t fillColor)
{	
	m_methodList.push_back(MethodCanvas::FillPolygon);
}

void CMockCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
	m_methodList.push_back(MethodCanvas::DrawCircle);
}

void CMockCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
	m_methodList.push_back(MethodCanvas::FillCircle);
}

std::vector<CMockCanvas::MethodCanvas> CMockCanvas::GetMethodList() const
{
	return m_methodList;
}
