#pragma once
#include "../IShape/ICanvas.h"


class CMockCanvas: public ICanvas
{
public:
	enum class MethodCanvas
	{
		DrawLine, 
		FillPolygon, 
		DrawCircle,
		FillCircle
	};

	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override;
	void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) override;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor) override;
	void FillCircle(CPoint center, double radius, uint32_t fillColor) override;

	std::vector<MethodCanvas> GetMethodList() const;

private:
	std::vector<MethodCanvas> m_methodList = {};
};

