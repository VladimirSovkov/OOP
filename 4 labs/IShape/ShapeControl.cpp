#include "ShapeControl.h"
#include <regex>
#include <algorithm>


CShapeControl::CShapeControl(std::istream& command, std::ostream& answer)
	:m_command(command),
	m_answer(answer)
{
}

std::vector<std::string> ParseValuesShape(std::istringstream& valuesShape)
{
	std::vector<std::string> values;
	std::string valuesToString;
	while (valuesShape >> valuesToString)
	{
		values.push_back(valuesToString);
	}
	return values;
}

bool IsCorrectNumber(const std::string& line)
{
	std::smatch result;
	std::regex regularExpression("^([-]?)(\\d+)([.]?)(\\d*)$");
	if (!regex_search(line, result, regularExpression))
	{
		return false;
	}
	return true;
}

bool IsCorrectPoint(const std::string& x, const std::string& y)
{
	return IsCorrectNumber(x) && IsCorrectNumber(y);
}

bool IsColor(const std::string& line)
{
	std::smatch result;
	std::regex regularExpression("^([abcdefABCDEF\\d]+)$");
	if (!regex_search(line, result, regularExpression))
	{
		return false;
	}
	return true;
}

bool CShapeControl::AnswerCommand()
{
	std::string commandString;
	getline(m_command, commandString);
	std::istringstream commandStringStream(commandString);
	std::vector<std::string> valuesShape = ParseValuesShape(commandStringStream);
	if (valuesShape.empty())
	{

		return false;
	}

	if (valuesShape[0] == "rectangle")
	{
		return SetRectangle(valuesShape);;
	}
	else if (valuesShape[0] == "circle")
	{
		return SetCircle(valuesShape);
	}
	else if (valuesShape[0] == "triangle")
	{
		return SetTriangle(valuesShape);
	}
	else if (valuesShape[0] == "line")
	{
		return SetLineSegment(valuesShape);
	}
	else
	{
		m_answer << "Incorrect Shape\n";
		Info();
		return false;
	}
}

void CShapeControl::Info() const
{
	m_answer << "Information\n";
	m_answer << "line <first point> <second point> <color>\n";
	m_answer << "rectangle <upper left point> <width> <height> <outline color> <fill color>\n";
	m_answer << "circle <center point> <radius> <outline color> <fill color>\n";
	m_answer << "triangle <vertex 1> <vertex 2> <vertex 2> <outline color> <fill color>\n";
}

void CShapeControl::PrintShapeWithMaxArea() const
{
	if(!m_listsOfShape.empty())
	{ 
		auto it = std::max_element(m_listsOfShape.begin(), m_listsOfShape.end(), []
		(const std::shared_ptr<IShape>& firstShape, const std::shared_ptr<IShape>& secondShape)
			{ return firstShape->GetArea() < secondShape->GetArea(); });

		m_answer << (*it)->ToString();
	}
}


void CShapeControl::PrintShapeWithMinPerimeter() const
{
	if (!m_listsOfShape.empty())
	{
		auto it = std::min_element(m_listsOfShape.begin(), m_listsOfShape.end(), []
		(const std::shared_ptr<IShape>& firstShape, const std::shared_ptr<IShape>& secondShape)
			{return firstShape->GetArea() < secondShape->GetArea(); });

		m_answer << (*it)->ToString();
	}
}

void CShapeControl::DrawShapes() const
{
	GLFWwindow* window{};
	CCanvas canvas(window);
    if (!glfwInit())
		return;
    window = glfwCreateWindow(1024, 768, "Canvas", NULL, NULL);
    if (!window)
    {
		glfwTerminate();
		return;
    }
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT); 
		glClearColor(255, 255, 255, 0);
		for (auto shape : m_listsOfShape)
		{
			shape->Draw(canvas);
		}
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

bool CShapeControl::SetLineSegment(const std::vector<std::string>& valuesLineSegment)
{
	if (valuesLineSegment.size() == 6 && 
		IsCorrectPoint(valuesLineSegment[1], valuesLineSegment[2]) && 
		IsCorrectPoint(valuesLineSegment[3], valuesLineSegment[4] )&& 
		IsColor(valuesLineSegment[5]))
	{
		CPoint startPoint(std::stod(valuesLineSegment[1]), std::stod(valuesLineSegment[2]));
		CPoint endPoint(std::stod(valuesLineSegment[3]), std::stod(valuesLineSegment[4]));
		uint32_t color = std::stoul(valuesLineSegment[5], 0, 16);
		m_listsOfShape.push_back(std::make_shared<CLineSegment>(startPoint, endPoint, color));
		return true;
	}

	m_answer << "Incorrect command\n";
	m_answer << "line 1.1 1.1 5.0 5.0 00ff00" << std::endl;
	return false;
}

bool CShapeControl::SetCircle(const std::vector<std::string>& valuesCircle)
{
	if (valuesCircle.size() == 6 &&
		IsCorrectPoint(valuesCircle[1], valuesCircle[2]) &&
		IsCorrectNumber(valuesCircle[3]) &&
		IsColor(valuesCircle[4]) && IsColor(valuesCircle[5]))
	{
		CPoint center(std::stod(valuesCircle[1]), std::stod(valuesCircle[2]));
		double radius = std::stod(valuesCircle[3]);
		uint32_t outlineColor = std::stoul(valuesCircle[4], 0, 16);
		uint32_t fillColor = std::stoul(valuesCircle[5], 0, 16);
		m_listsOfShape.push_back(std::make_shared<CCircle>(center, radius, outlineColor, fillColor));

		return true;
	}

	m_answer << "Incorrect command\n";
	m_answer << "circle 1.0 0.0 2.0 00ff00 ff0000" << std::endl;
	return false;
}

bool CShapeControl::SetRectangle(const std::vector<std::string>& valuesRectangle)
{
	if (valuesRectangle.size() == 7 &&
		IsCorrectPoint(valuesRectangle[1], valuesRectangle[2]) &&
		IsCorrectNumber(valuesRectangle[3]) && IsCorrectNumber(valuesRectangle[4]) &&
		IsColor(valuesRectangle[5]) && IsColor(valuesRectangle[6]))
	{
		CPoint leftTop(std::stod(valuesRectangle[1]), std::stod(valuesRectangle[2]));
		double width = std::stod(valuesRectangle[3]);
		double height = std::stod(valuesRectangle[4]);
		uint32_t outlineColor = std::stoul(valuesRectangle[5], 0, 16);
		uint32_t fillColor = std::stoul(valuesRectangle[6], 0, 16);
		m_listsOfShape.push_back(std::make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor));

		return true;
	}

	m_answer << "Incorrect command\n";
	m_answer << "rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00" << std::endl;
	return false;
}

bool CShapeControl::SetTriangle(const std::vector<std::string>& valuesTriangle)
{
	if (valuesTriangle.size() == 9 &&
		IsCorrectPoint(valuesTriangle[1], valuesTriangle[2]) &&
		IsCorrectPoint(valuesTriangle[3], valuesTriangle[4]) &&
		IsCorrectPoint(valuesTriangle[5], valuesTriangle[6]) &&
		IsColor(valuesTriangle[7]) && IsColor(valuesTriangle[8]))
	{
		CPoint vertex1(std::stod(valuesTriangle[1]), std::stod(valuesTriangle[2]));
		CPoint vertex2(std::stod(valuesTriangle[3]), std::stod(valuesTriangle[4]));
		CPoint vertex3(std::stod(valuesTriangle[5]), std::stod(valuesTriangle[6]));
		uint32_t outlineColor = std::stoul(valuesTriangle[7], 0, 16);
		uint32_t fillColor = std::stoul(valuesTriangle[8], 0, 16);
		m_listsOfShape.push_back(std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor));

		return true;
	}

	m_answer << "Incorrect command\n";
	m_answer << "triangle 0.0 0.0 4.0 0.0 4.0 5.0 00ff00 ff0000" << std::endl;
	return false;
}