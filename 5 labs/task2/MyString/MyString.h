#pragma once
#include <string>
#include <utility>
#include <iostream>

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other) noexcept;
	CMyString(std::string const& stlString);

	~CMyString();
	size_t GetLength()const; 
	const char* GetStringData()const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX)const;
	void Clear();

	CMyString& operator=(const CMyString& other);
	CMyString& operator=(CMyString&& other) noexcept;

	CMyString& operator+=(const CMyString& other);

	const char& operator[](size_t id) const;
	char& operator[](size_t id);
private:
	char* m_pString;
	size_t m_length;
	
};

CMyString operator+(const CMyString& firstLine, const CMyString& secondLine);

bool operator==(const CMyString& firstLine, const CMyString& secondLine);
bool operator!=(const CMyString& firstLine, const CMyString& secondLine);

bool operator>(const CMyString& firstLine, const CMyString& secondLine);
bool operator<(const CMyString& firstLine, const CMyString& secondLine);
bool operator>=(const CMyString& firstLine, const CMyString& secondLine);
bool operator<=(const CMyString& firstLine, const CMyString& secondLine);

std::ostream& operator<<(std::ostream& output, const CMyString& myString);
std::istream& operator>>(std::istream& input, CMyString& myString);
