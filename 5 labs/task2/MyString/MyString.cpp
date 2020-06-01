#include "MyString.h"

CMyString::CMyString()
	:m_length(0)
{
	m_pString = new char[m_length + 1];
	m_pString[0] = '\0';
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
	:m_length(length)
{
	m_pString = new char[m_length + 1];
	std::memcpy(m_pString, pString, length);
	m_pString[m_length] = '\0';
}

CMyString::CMyString(CMyString const& other)
	:CMyString(other.m_pString, other.m_length)
{
}

CMyString::CMyString(CMyString&& other) noexcept
	:m_pString(other.m_pString),
	m_length(other.m_length)
{
	other.m_pString = nullptr;
	other.m_length = 0;
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.size())
{
}

CMyString::~CMyString()
{
	delete[] m_pString;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_pString;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		throw std::out_of_range("out of bounds array");
	}
	
	if (length >= m_length - start)
	{
		return CMyString(m_pString + start, m_length - start);
	}
	else
	{
		return CMyString(m_pString + start, length);
	}
}

void CMyString::Clear()
{ 
	delete[] m_pString;
	m_length = 0;
	m_pString = new char[m_length + 1];
	m_pString[m_length] = '\0';
}

int MyStringComparison(const CMyString& firstLine, const CMyString& secondLine)
{
	if (firstLine.GetLength() > secondLine.GetLength())
	{
		return 1;
	}
	else if (firstLine.GetLength() < secondLine.GetLength())
	{
		return -1;
	}

	size_t length = firstLine.GetLength();
	for (size_t i = 0; i < length; i++)
	{
		if (firstLine[i] > secondLine[i])
		{
			return 1;
		}
		else if (firstLine[i] < secondLine[i])
		{
			return -1;
		}
	}

	return 0;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (&other != this)
	{
		CMyString temporary(other);
		std::swap(m_pString, temporary.m_pString);
		std::swap(m_length, temporary.m_length);
	}

	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (&other != this)
	{
		delete[] m_pString;
		m_pString = other.m_pString;
		m_length = other.m_length;
		other.m_length = 0;
		other.m_pString = nullptr;
	}

	return *this;
}

CMyString& CMyString::operator+=(const CMyString& other)
{
	*this = *this + other;
	return *this;
}

const char& CMyString::operator[](size_t id) const
{
	if (id > m_length)
	{
		throw std::out_of_range("out of bounds array");
	}
	return m_pString[id];
}

char& CMyString::operator[](size_t id)
{
	if (id > m_length)
	{
		throw std::out_of_range("out of bounds array");
	}
	return m_pString[id];
}

CMyString operator+(const CMyString& firstLine, const CMyString& secondLine)
{
	size_t length = firstLine.GetLength() + secondLine.GetLength();
	char* pString = new char[length + 1];
	std::memcpy(pString, firstLine.GetStringData(), firstLine.GetLength());
	std::memcpy(pString + firstLine.GetLength(), secondLine.GetStringData(), secondLine.GetLength());
	pString[length] = '\0';
	CMyString newMyString(pString, length);
	delete[] pString;
	return newMyString;
}

bool operator==(const CMyString& firstLine, const CMyString& secondLine)
{
	return firstLine.GetLength() == secondLine.GetLength() &&
		std::strcmp(firstLine.GetStringData(), secondLine.GetStringData()) == 0;
}

bool operator!=(const CMyString& firstLine, const CMyString& secondLine)
{
	return !(firstLine == secondLine);
}

bool operator>(const CMyString& firstLine, const CMyString& secondLine)
{
	return MyStringComparison(firstLine, secondLine) > 0;
}

bool operator<(const CMyString& firstLine, const CMyString& secondLine)
{
	return MyStringComparison(firstLine, secondLine) < 0;
}

bool operator>=(const CMyString& firstLine, const CMyString& secondLine)
{
	return !(firstLine < secondLine);
}

bool operator<=(const CMyString& firstLine, const CMyString& secondLine)
{
	return !(firstLine > secondLine);
}

std::ostream& operator<<(std::ostream& output, const CMyString& myString)
{
	output << myString.GetStringData();
	return output;
}

std::istream& operator>>(std::istream& input, CMyString& myString)
{
	char arraySymbol[255];
	input.getline(arraySymbol, 255);
	myString = arraySymbol;
	return input;
}


