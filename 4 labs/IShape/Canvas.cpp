#include "Canvas.h"

CCanvas::CCanvas(GLFWwindow* window)
    :m_window(window)
{
}

RGB GetValueRGB(uint32_t color)
{
    RGB colorRGB;
    colorRGB.red = (color >> 16) & 0xFF;
    colorRGB.green = (color >> 8) & 0xFF;
    colorRGB.blue = (color) & 0xFF;

    return colorRGB;
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
    RGB color = GetValueRGB(lineColor);
    glBegin(GL_LINES);
    glColor3d(color.red, color.green, color.blue);
    glVertex2d(from.x, from.y);
    glVertex2d(to.x, to.y);
    glEnd();
}

void CCanvas::FillPolygon(std::vector<CPoint> points, uint32_t fillColor)
{
    RGB color = GetValueRGB(fillColor);
    glLineWidth(3);
    glBegin(GL_POLYGON);
    glColor3d(color.red, color.green, color.blue);
    for(auto point : points)
    {
        glVertex2d(point.x, point.y);
    }
    glEnd();
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
    RGB color = GetValueRGB(lineColor);
    glColor3d(color.red, color.green, color.blue);
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < NUMBER_SEGMENTS; i++)
    {
        double theta = PI_X_2 * i / NUMBER_SEGMENTS;
        glVertex2d(center.x + (radius * cos(theta)), center.y + (radius * sin(theta)));
    }
    glEnd();
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
    RGB color = GetValueRGB(fillColor);
    glColor3d(color.red, color.green, color.blue);
    glBegin(GL_POLYGON);
    for (int i = 0; i < NUMBER_SEGMENTS; i++)
    {
        double theta = PI_X_2 * i / NUMBER_SEGMENTS;
        glVertex2d(center.x + (radius * cos(theta)), center.y + (radius * sin(theta)));
    }
    glEnd();
}