#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MyString/MyString.h"
#include <sstream>

TEST_CASE("check default constructor")
{
	CMyString myString;
	std::string emptyLine = "";
	CHECK(0 == myString.GetLength());
	CHECK(emptyLine == myString.GetStringData());
}

TEST_CASE("check constructor initializing the string with the terminating character")
{
	CMyString myString("Hello");
	std::string line = "Hello";
	CHECK(5 == myString.GetLength());
	CHECK(line == myString.GetStringData());
}

TEST_CASE("check constructor initializing data character array of a given length")
{
	char* abc = new char[5] {'h', 'e', 'l', 'l', 'o'};
	CMyString myString(abc, 5);
	std::string line = "hello";
	CHECK(5 == myString.GetLength());
	CHECK(line == myString.GetStringData());
}

TEST_CASE("check copy constructor")
{
	CMyString myStringFrist("Hello world!");
	CMyString myStringSecond(myStringFrist);
	CHECK(myStringFrist.GetLength() == myStringSecond.GetLength());
	std::string line = "Hello world!";
	CHECK(line == myStringFrist.GetStringData());
	CHECK(line == myStringSecond.GetStringData());
}

TEST_CASE("check constructor receiving std::string")
{
	WHEN("empty string")
	{
		std::string emptyLine = "";
		CMyString myString(emptyLine);
		CHECK(myString.GetLength() == 0);
		CHECK(myString.GetStringData() == emptyLine);
	}

	WHEN("line with word")
	{
		std::string line = "word";
		CMyString myString(line);
		CHECK(myString.GetLength() == 4);
		CHECK(myString.GetStringData() == line);
	}
}

TEST_CASE("check get length")
{
	WHEN("empty string")
	{
		CMyString myString;
		CHECK(myString.GetLength() == 0);
	}

	WHEN("line with word")
	{
		CMyString myString("word");
		CHECK(myString.GetLength() == 4);
	}
}

TEST_CASE("get string data")
{
	WHEN("empty string")
	{
		CMyString myString;
		std::string emptyLine = "";
		CHECK(emptyLine == myString.GetStringData());
	}
	
	WHEN("line with word")
	{
		CMyString myString("word");
		std::string line = "word";
		CHECK(line == myString.GetStringData());
	}
}

TEST_CASE("return substring")
{
	CMyString myString("Hello world!");

	WHEN("out of range error")
	{
		CHECK_THROWS(myString.SubString(12));
	}

	WHEN("no way out from area")
	{
		CMyString line(myString.SubString(6, 5));
		CHECK(std::string("world") == line.GetStringData());
	}

	WHEN("length bounds violation")
	{
		CMyString line(myString.SubString(6, 20));
		CHECK(std::string("world!") == line.GetStringData());
	}
}

TEST_CASE("clear string")
{
	CMyString myString("word");
	myString.Clear();
	CHECK(0 == myString.GetLength());
	CHECK(std::string("") == myString.GetStringData());
}

TEST_CASE("operator =")
{
	CMyString myString("word");
	WHEN("appropriate oneself")
	{
		myString = myString;
		CHECK(std::string("word") == myString.GetStringData());
		CHECK(4 == myString.GetLength());
	}

	WHEN("assignment(copying)")
	{
		CMyString line;
		line = myString;

		CHECK(4 == line.GetLength());
		CHECK(std::string("word") == line.GetStringData());
		CHECK(std::string("word") == myString.GetStringData());
	}

	WHEN("assignment(moving)")
	{
		CMyString line;
		line = std::move(myString);
		CHECK(std::string("word") == line.GetStringData());
		CHECK(4 == line.GetLength());
		CHECK(nullptr == myString.GetStringData());
		CHECK(0 == myString.GetLength());
	}
}

TEST_CASE("operator +")
{
	CMyString firstLine("Hello");
	std::string str4 = " world";
	const char* str5 = new char[7]{ ' ', 'w', 'o', 'r', 'l', 'd', '\0' };

	WHEN("CMyString + CMyString")
	{
		CMyString secondLine(" world!");
		CMyString answer = firstLine + secondLine;
		CHECK(12 == answer.GetLength());
		CHECK(std::string("Hello world!") == answer.GetStringData());
	}

	WHEN("std::string CMyString")
	{
		std::string secondLine = " world!";
		CMyString answer = firstLine + secondLine;
		CHECK(12 == answer.GetLength());
		CHECK(std::string("Hello world!") == answer.GetStringData());
	}

	WHEN("const char* с CMyString")
	{
		const char* secondLine = new char[8]{ ' ', 'w', 'o', 'r', 'l', 'd', '!', '\0' };
		CMyString answer = firstLine + secondLine;
		CHECK(12 == answer.GetLength());
		CHECK(std::string("Hello world!")== answer.GetStringData());
	}
}

TEST_CASE("operator ==")
{
	CMyString firstLine("word");

	WHEN("two equal lines")
	{
		CMyString secondLine("word");
		CHECK(firstLine == secondLine);
	}

	WHEN("different lines of the same length")
	{
		CMyString secondLine("WoRd");
		CHECK(!(firstLine == secondLine));
	}

	WHEN("two different lines")
	{
		CMyString secondLine("qwerty");
		CHECK(!(firstLine == secondLine));
	}
}

TEST_CASE("operator !=")
{
	CMyString firstLine("word");

	WHEN("two equal lines")
	{
		CMyString secondLine("word");
		CHECK(!(firstLine != secondLine));
	}

	WHEN("different lines of the same length")
	{
		CMyString secondLine("WoRd");
		CHECK(firstLine != secondLine);
	}

	WHEN("two different lines")
	{
		CMyString secondLine("qwerty");
		CHECK(firstLine != secondLine);
	}
}

TEST_CASE("operator +=")
{
	CMyString firstLine("Hello ");
	CMyString secondLine("world!");
	CMyString answer("Hello world!");
	firstLine += secondLine;
	CHECK(answer == firstLine);
} 

TEST_CASE("operator >")
{
	CMyString firstLine("word");
	WHEN("first > second")
	{
		CMyString secondLine("a");
		CHECK(firstLine > secondLine);
	}

	WHEN("same length")
	{
		CMyString secondLine("worc");
		CHECK(firstLine > secondLine);
	}

	WHEN("equal lines")
	{
		CMyString secondLine("word");
		CHECK(!(firstLine > secondLine));
	}

	WHEN("first < second")
	{
		CMyString secondLine("aaaaaa");
		CHECK(!(firstLine > secondLine));
	}
}

TEST_CASE("operator <")
{
	CMyString firstLine("word");
	WHEN("first < second")
	{
		CMyString secondLine("aaaaa");
		CHECK(firstLine < secondLine);
	}

	WHEN("same length")
	{
		CMyString secondLine("wore");
		CHECK(firstLine < secondLine);
	}

	WHEN("equal lines")
	{
		CMyString secondLine("word");
		CHECK(!(firstLine < secondLine));
	}

	WHEN("first > second")
	{
		CMyString secondLine("a");
		CHECK(!(firstLine < secondLine));
	}
}

TEST_CASE("operator >=")
{
	CMyString firstLine("word");
	CMyString secondLine("a");
	CHECK(firstLine >= secondLine);

	secondLine = firstLine;
	CHECK(firstLine >= secondLine);
}

TEST_CASE("operator <=")
{
	CMyString firstLine("word");
	CMyString secondLine("a");
	CHECK(secondLine <= firstLine);

	secondLine = firstLine;
	CHECK(secondLine <= firstLine);
}

TEST_CASE("operator []")
{
	CMyString myString("word");
	WHEN("for reading")
	{
		CHECK('r' == myString[2]);
	}

	WHEN("for recording")
	{
		myString[3] = 'k';
		CHECK('k' == myString[3]);
	}

	WHEN("out of bounds array")
	{
		CHECK_THROWS(myString[5]);
	}
}

TEST_CASE("operator >>")
{
	std::stringstream input("Hello world!");
	CMyString myString;
	input >> myString;
	CHECK(12 == myString.GetLength());
	CHECK(std::string("Hello world!") == myString.GetStringData());
}

TEST_CASE("operator <<")
{
	std::stringstream output;
	CMyString myString("Hello world!");
	output << myString;
	CHECK("Hello world!" == output.str());
}