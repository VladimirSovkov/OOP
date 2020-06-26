#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../StringList/StringList.h"


TEST_CASE("default constructor and list data retrieval")
{
	CStringList stringList;
	CHECK(0 == stringList.GetSize());
}

TEST_CASE("insert string")
{
	CStringList stringList;
	WHEN("add to start")
	{
		stringList.Insert("str2", stringList.begin());
		CHECK(1 == stringList.GetSize());
		CHECK("str2" == stringList.GetFrontElement());
		stringList.Insert("str1", stringList.begin());
		CHECK(2 == stringList.GetSize());
		CHECK("str1" == stringList.GetFrontElement());
	}

	WHEN("add to end")
	{
		stringList.Insert("str3", stringList.end());
		CHECK(1 == stringList.GetSize());
		CHECK("str3" == stringList.GetBackElement());

		stringList.Insert("str4", stringList.end());
		CHECK(2 == stringList.GetSize());
		CHECK("str4" == stringList.GetBackElement());
	}

	WHEN("add to any place")
	{
		stringList.PushBack("str1");
		stringList.PushBack("str2");
		auto it = ++stringList.begin();
		stringList.Insert("str1.5", it);
		it = ++stringList.begin();
		CHECK("str1.5" == *it);
	}

	WHEN("exceptions")
	{
		stringList.PushBack("str1");
		stringList.PushBack("str2");
		
		CStringList stringListCopy;
		auto it = stringListCopy.begin();
		CHECK_THROWS(stringList.Insert("errore", it));		
	}
}

TEST_CASE("add string to start and end list")
{
	CStringList stringList;

	WHEN("add to start")
	{
		stringList.PushFront("str2");
		CHECK("str2" == stringList.GetFrontElement());
		stringList.PushFront("str1");
		CHECK("str1" == stringList.GetFrontElement());
	}

	WHEN("add to end")
	{
		stringList.PushBack("str3");
		CHECK(1 == stringList.GetSize());
		CHECK("str3" == stringList.GetBackElement());

		stringList.PushBack("str4");
		CHECK(2 == stringList.GetSize());
		CHECK("str4" == stringList.GetBackElement());
	}
}

TEST_CASE("Get element")
{
	CStringList stringList;
	stringList.PushBack("str1");
	WHEN("back")
	{
		CHECK("str1" == stringList.GetBackElement());

		stringList.PushBack("str2");
		CHECK("str2" == stringList.GetBackElement());
	}

	WHEN("front")
	{
		CHECK("str1" == stringList.GetFrontElement());

		stringList.PushBack("str2");
		CHECK("str1" == stringList.GetFrontElement());
	}
}

TEST_CASE("check for emptiness")
{
	CStringList stringList;
	CHECK(true == stringList.IsEmpty());

	stringList.PushBack("str");
	CHECK(false == stringList.IsEmpty());
}

TEST_CASE("erase element")
{
	CStringList stringList;
	stringList.PushBack("str1");
	stringList.PushBack("str2");
	CHECK(2 == stringList.GetSize());

	WHEN("delete the first element")
	{
		stringList.Erase(stringList.begin());
		CHECK(1 == stringList.GetSize());
		CHECK("str2" == stringList.GetFrontElement());
	}

	WHEN("delete last element")
	{
		auto it = --stringList.end();
		stringList.Erase(it);
		CHECK(1 == stringList.GetSize());
		CHECK("str1" == stringList.GetFrontElement());
	}

	WHEN("delete an arbitrary element")
	{
		stringList.PushBack("str3");
		auto it = ++stringList.begin();
		stringList.Erase(it);
		CHECK(2 == stringList.GetSize());
		CHECK("str1" == stringList.GetFrontElement());
		CHECK("str3" == stringList.GetBackElement());
	}

	WHEN("exceptions")
	{
		CHECK_THROWS(stringList.Erase(stringList.end()));

		CStringList stringListCopy;

		CHECK_THROWS(stringListCopy.Erase(stringListCopy.begin()));

		stringListCopy.PushBack("str1");
		auto it = stringListCopy.begin();
		CHECK_THROWS(stringList.Erase(it));
	}
}

TEST_CASE("remove all items from the list")
{
	CStringList stringList;
	stringList.PushBack("str1");
	stringList.PushBack("str2");
	stringList.PushBack("str3");
	CHECK(3 == stringList.GetSize());

	stringList.Clear();
	CHECK(0 == stringList.GetSize());
	CHECK(true == stringList.IsEmpty());
}

TEST_CASE("constructor accepting a list of strings")
{
	CStringList stringList;
	stringList.PushBack("str1");
	stringList.PushBack("str2");
	stringList.PushBack("str3");

	CStringList copyStringList(stringList);
	CHECK(3 == copyStringList.GetSize());
	CHECK("str1" == copyStringList.GetFrontElement());
	CHECK("str3" == copyStringList.GetBackElement());
}

TEST_CASE("operator = for CStringList")
{
	CStringList stringList;
	stringList.PushBack("str1");
	stringList.PushBack("str2");
	stringList.PushBack("str3");
	
	CStringList copyStringList;
	copyStringList.PushBack("string");
	copyStringList = stringList;
	CHECK(3 == copyStringList.GetSize());
	CHECK("str1" == copyStringList.GetFrontElement());
	CHECK("str3" == copyStringList.GetBackElement());
	
	CHECK(3 == stringList.GetSize());

	WHEN("list is empty")
	{
		stringList.Clear();
		copyStringList = stringList;
		CHECK(0 == copyStringList.GetSize());
	}
}

TEST_CASE("operator* for CIterator")
{
	CStringList stringList;
	stringList.PushBack("str1");
	stringList.PushBack("str2");
	stringList.PushBack("str3");

	std::string str = *stringList.begin();
	CHECK("str1" == str);

	CHECK_THROWS(*stringList.end());
	CHECK_THROWS(*stringList.rend());
}

TEST_CASE("iterators begin, end, cbegin, cend")
{
	CStringList stringList;
	stringList.PushBack("str1");
	stringList.PushBack("str2");
	stringList.PushBack("str3");

	WHEN("begin, end")
	{
		CHECK("str1" == *stringList.begin());
		CHECK("str3" == *(--stringList.end()));
	}

	WHEN("cbegin, cend")
	{
		CHECK("str1" == *stringList.cbegin());
		auto it = stringList.cend();
		it--;
		CHECK("str3" == *(it));
	}
}

TEST_CASE("Prefix operator for CIterator")
{
	CStringList stringList;
	stringList.PushBack("str1");
	stringList.PushBack("str2");
	stringList.PushBack("str3");

	WHEN("increment")
	{
		auto it = stringList.begin();
		++it;
		CHECK("str2" == *it);
		++it;
		CHECK("str3" == *it);
		++it;
		CHECK(stringList.end() == it);

		CHECK_THROWS(++it);

		it = stringList.rend();
		CHECK_THROWS(++it);
	}

	WHEN("decrement")
	{
		auto it = stringList.end();
		--it;
		CHECK("str3" == *it);
		--it;
		--it;
		CHECK(stringList.begin() == it);
		
		CHECK_THROWS(--it);

		it = stringList.rbegin();
		CHECK_THROWS(--it);
	}
}

TEST_CASE("Postfix operator for CIterator")
{
	CStringList stringList;
	stringList.PushBack("str1");
	stringList.PushBack("str2");
	stringList.PushBack("str3");

	WHEN("increment")
	{
		auto it = stringList.begin()++;
		CHECK("str2" == *it);
		it++;
		CHECK("str3" == *it);
		it++;
		CHECK(stringList.end() == it);
		
		CHECK_THROWS(it++);

		it = stringList.rend();
		CHECK_THROWS(it++);
	}

	WHEN("decrement")
	{
		auto it = stringList.end()--;
		CHECK("str3" == *it);
		it--;
		it--;
		CHECK(stringList.begin() == it);
		
		CHECK_THROWS(it--);
		it = stringList.rbegin();
		CHECK_THROWS(it--);
	}
}

TEST_CASE("iterators rbegin, rend, crbegin, crend")
{
	CStringList stringList;
	stringList.PushBack("str1");
	stringList.PushBack("str2");
	stringList.PushBack("str3");
	WHEN("rbegin, rend")
	{
		CHECK("str3" == *stringList.rbegin());
		CHECK("str1" == *(--stringList.rend()));
	}

	WHEN("crbegin, crend")
	{
		CHECK("str3" == *stringList.crbegin());
		auto it = stringList.crend();
		it--;
		CHECK("str1" == *it);
	}
}

TEST_CASE("CStringList&& moving constructor")
{
	CStringList stringList;
	stringList.PushBack("str1");
	stringList.PushBack("str2");

	CStringList movedList(std::move(stringList));
	CHECK(0 == stringList.GetSize());
	CHECK(2 == movedList.GetSize());

	auto it = stringList.begin();
	CHECK(it == stringList.end());

	CHECK("str1" == movedList.GetFrontElement());
	CHECK("str2" == movedList.GetBackElement());
}

TEST_CASE("moving an object")
{
	CStringList stringList;
	stringList.PushBack("str1");
	stringList.PushBack("str2");

	CStringList movedList;
	movedList = std::move(stringList);
	CHECK(0 == stringList.GetSize());
	CHECK(2 == movedList.GetSize());

	auto it = stringList.begin();
	CHECK(it == stringList.end());

	CHECK("str1" == movedList.GetFrontElement());
	CHECK("str2" == movedList.GetBackElement());
}