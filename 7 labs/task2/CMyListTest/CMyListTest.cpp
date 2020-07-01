#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CMyList/CMyList.h"
#include<string>

TEST_CASE("default constructor and list data retrieval")
{
	WHEN("int type list")
	{
		CMyList<int> list;
		CHECK(0 == list.GetSize());
	}

	WHEN("string type list")
	{
		CMyList<std::string> list;
		CHECK(0 == list.GetSize());
	}

	WHEN("char type list")
	{
		CMyList<char> list;
		CHECK(0 == list.GetSize());
	}

	WHEN("double type list")
	{
		CMyList<double> list;
		CHECK(0 == list.GetSize());
	}
}

TEST_CASE("IsEmpty")
{
	CMyList<int> list;
	CHECK(list.IsEmpty());
	list.PushBack(1);
	CHECK(!list.IsEmpty());
}

TEST_CASE("insert to list")
{
	WHEN("int type list")
	{
		CMyList<int> list;
		list.Insert(1, list.begin());
		CHECK(1 == list.GetBackElement());
		CHECK(1 == list.GetFrontElement());
		CHECK(1 == list.GetSize());

		list.Insert(2, list.begin());
		CHECK(2 == list.GetFrontElement());
		CHECK(1 == list.GetBackElement());
		CHECK(2 == list.GetSize());

		list.Insert(3, list.end());
		CHECK(2 == list.GetFrontElement());
		CHECK(3 == list.GetBackElement());
		CHECK(3 == list.GetSize());
	}

	WHEN("string type list")
	{
		CMyList<std::string> list;
		list.Insert("str1", list.begin());
		CHECK("str1" == list.GetBackElement());
		CHECK("str1" == list.GetFrontElement());
		CHECK(1 == list.GetSize());

		list.Insert("str2", list.begin());
		CHECK("str2" == list.GetFrontElement());
		CHECK("str1" == list.GetBackElement());
		CHECK(2 == list.GetSize());

		list.Insert("str3", list.end());
		CHECK("str2" == list.GetFrontElement());
		CHECK("str3" == list.GetBackElement());
		CHECK(3 == list.GetSize());
	}

	WHEN("exceptions")
	{
		CMyList<int> intList;
		CMyList<int> intListCopy;
		CHECK_THROWS(intList.Insert(1, intListCopy.begin()));
		CHECK_THROWS(intList.Insert(1, intList.begin()--));
		CHECK_THROWS(intList.Insert(1, ++intList.end()));
	}
}

TEST_CASE("push back")
{
	WHEN("int type list")
	{
		CMyList<int> list;
		list.PushBack(1);
		CHECK(1 == list.GetBackElement());
		CHECK(1 == list.GetFrontElement());
		CHECK(1 == list.GetSize());

		list.PushBack(2);
		CHECK(1 == list.GetFrontElement());
		CHECK(2 == list.GetBackElement());
		CHECK(2 == list.GetSize());
	}

	WHEN("string type list")
	{
		CMyList<std::string> list;
		list.PushBack("str1");
		CHECK("str1" == list.GetBackElement());
		CHECK("str1" == list.GetFrontElement());
		CHECK(1 == list.GetSize());

		list.PushBack("str2");
		CHECK("str1" == list.GetFrontElement());
		CHECK("str2" == list.GetBackElement());
		CHECK(2 == list.GetSize());
	}
}

TEST_CASE("push front")
{
	WHEN("int type list")
	{
		CMyList<int> list;
		list.PushFront(1);
		CHECK(1 == list.GetBackElement());
		CHECK(1 == list.GetFrontElement());
		CHECK(1 == list.GetSize());

		list.PushFront(2);
		CHECK(2 == list.GetFrontElement());
		CHECK(1 == list.GetBackElement());
		CHECK(2 == list.GetSize());
	}

	WHEN("string type list")
	{
		CMyList<std::string> list;
		list.PushFront("str1");
		CHECK("str1" == list.GetBackElement());
		CHECK("str1" == list.GetFrontElement());
		CHECK(1 == list.GetSize());

		list.PushFront("str2");
		CHECK("str2" == list.GetFrontElement());
		CHECK("str1" == list.GetBackElement());
		CHECK(2 == list.GetSize());
	}
}

TEST_CASE("Erase()")
{
	WHEN("int type list")
	{
		CMyList<int> list;
		list.PushBack(1);
		list.PushBack(2);
		list.PushBack(3);
		list.PushBack(4);
		list.Erase(list.begin());
		CHECK(3 == list.GetSize());
		CHECK(2 == list.GetFrontElement());

		list.Erase(++list.begin());
		CHECK(2 == list.GetSize());
		CHECK(4 == *(++list.begin()));

		list.Erase(--list.end());
		CHECK(1 == list.GetSize());
		CHECK(2 == list.GetBackElement());
	}

	WHEN("string type list")
	{
		CMyList<std::string> list;
		list.PushBack("str1");
		list.PushBack("str2");
		list.PushBack("str3");
		list.PushBack("str4");
		list.Erase(list.begin());
		CHECK(3 == list.GetSize());
		CHECK("str2" == list.GetFrontElement());

		list.Erase(++list.begin());
		CHECK(2 == list.GetSize());
		CHECK("str4" == *(++list.begin()));

		list.Erase(--list.end());
		CHECK(1 == list.GetSize());
		CHECK("str2" == list.GetBackElement());
	}

	WHEN("exception")
	{
		CMyList<int> list;

		CHECK_THROWS(list.Erase(list.begin()));

		CMyList<int> copyList;
		list.PushBack(1);
		list.PushBack(2);
		copyList.PushBack(1);
		copyList.PushBack(2);
		CHECK_THROWS(list.Erase(copyList.begin()));
		
		CHECK_THROWS(list.Erase(list.end()));
		CHECK_THROWS(list.Erase(--list.begin()));
	}
}

TEST_CASE("clear()")
{
	WHEN("int type list")
	{
		CMyList<int> list;
		list.PushBack(1);
		list.PushBack(2);
		list.PushBack(3);
		CHECK(3 == list.GetSize());

		list.Clear();
		CHECK(0 == list.GetSize());
	}

	WHEN("string type list")
	{
		CMyList<std::string> list;
		list.PushBack("str1");
		list.PushBack("str2");
		list.PushBack("str3");
		CHECK(3 == list.GetSize());

		list.Clear();
		CHECK(0 == list.GetSize());
	}
}

TEST_CASE("operator* for CIterator")
{
	WHEN("int type list")
	{
		CMyList<int> list;
		list.PushBack(1);
		CHECK(1 == *(list.begin()));
	}

	WHEN("string type list")
	{
		CMyList<std::string> list;
		list.PushBack("str1");
		CHECK("str1" == *(list.begin()));
	}
	
	WHEN("exception")
	{
		CMyList<int> list;
		CHECK_THROWS(*list.end());
		CHECK_THROWS(*(--list.begin()));
	}
}

TEST_CASE("iterators begin, end, cbegin, cend")
{
	CMyList<int> intList;
	intList.PushBack(1);
	intList.PushBack(2);

	CMyList<std::string> stringList;
	stringList.PushBack("str1");
	stringList.PushBack("str2");

	WHEN("begin, cbegin")
	{
		CHECK(1 == *intList.begin());
		CHECK(1 == *intList.cbegin());

		CHECK("str1" == *stringList.begin());
		CHECK("str1" == *stringList.cbegin());
	}

	WHEN("end")
	{
		CHECK(2 == *(--intList.end()));
		auto intIt = intList.cend();
		intIt--;
		CHECK(2 == *intIt);

		CHECK("str2" == *(--stringList.end()));
		auto stringIt = stringList.cend();
		stringIt--;
		CHECK("str2" == *stringIt);

	}
}

TEST_CASE("iterators rbegin, rend, crbegin, crend")
{
	WHEN("int")
	{
		CMyList<int> intList;
		intList.PushBack(1);
		intList.PushBack(2);
		WHEN("rbegin, rend")
		{
			CHECK(2 == *intList.rbegin());
			CHECK(1 == *(--intList.rend()));
		}

		WHEN("crbegin, crend")
		{
			CHECK(2 == *intList.crbegin());
			auto it = intList.crend();
			CHECK(1 == *(--it));
		}
	}

	WHEN("string")
	{
		CMyList<std::string> stringList;
		stringList.PushBack("str1");
		stringList.PushBack("str2");
		WHEN("rbegin, rend")
		{
			CHECK("str2" == *stringList.rbegin());
			CHECK("str1" == *(--stringList.rend()));
		}

		WHEN("crbegin, crend")
		{
			CHECK("str2" == *stringList.crbegin());
			auto it = stringList.crend();
			CHECK("str1" == *(--it));
		}
	}
}


TEST_CASE("operator = for CIterator")
{
	WHEN("int")
	{
		CMyList<int> intList;
		intList.PushBack(1);
		intList.PushBack(2);
		intList.PushBack(3);
		CMyList<int> intListCopy;
		intListCopy = intList;

		CHECK(3 == intListCopy.GetSize());
		CHECK(1 == intListCopy.GetFrontElement());
		CHECK(3 == intListCopy.GetBackElement());

		intList = intList;
		CHECK(3 == intList.GetSize());
		CHECK(1 == intList.GetFrontElement());
		CHECK(3 == intList.GetBackElement());
	}

	WHEN("string")
	{
		CMyList<std::string> intList;
		intList.PushBack("1");
		intList.PushBack("2");
		intList.PushBack("3");
		CMyList<std::string> intListCopy;
		intListCopy = intList;

		CHECK(3 == intListCopy.GetSize());
		CHECK("1" == intListCopy.GetFrontElement());
		CHECK("3" == intListCopy.GetBackElement());
	}
}

TEST_CASE("Moving operator")
{
	WHEN("int")
	{
		CMyList<int> list;
		list.PushBack(1);
		list.PushBack(2);
		CMyList<int> listMoved;
		listMoved = std::move(list);

		CHECK(0 == list.GetSize());
		CHECK(2 == listMoved.GetSize());
		CHECK(1 == listMoved.GetFrontElement());

		listMoved = listMoved;
		CHECK(2 == listMoved.GetSize());
		CHECK(1 == listMoved.GetFrontElement());
	}
	WHEN("string")
	{
		CMyList<std::string> list;
		list.PushBack("1");
		list.PushBack("2");
		CMyList<std::string> listMoved;
		listMoved = std::move(list);

		CHECK(0 == list.GetSize());
		CHECK(2 == listMoved.GetSize());
		CHECK("1" == listMoved.GetFrontElement());
	}
}

TEST_CASE("copy constructor")
{
	WHEN("int")
	{
		CMyList<int> list;
		list.PushBack(1);
		list.PushBack(2);
		CMyList<int> copyList(list);
		CHECK(2 == copyList.GetSize());
		CHECK(1 == copyList.GetFrontElement());
	}

	WHEN("string")
	{
		CMyList<std::string> list;
		list.PushBack("str1");
		list.PushBack("str2");
		CMyList<std::string> copyList(list);
		CHECK(2 == copyList.GetSize());
		CHECK("str1" == copyList.GetFrontElement());
	}
}

TEST_CASE("move constructor")
{
	WHEN("int")
	{
		CMyList<int> list;
		list.PushBack(1);
		list.PushBack(2);
		CMyList<int> copyList(std::move(list));
		CHECK(0 == list.GetSize());
		CHECK(2 == copyList.GetSize());
		CHECK(1 == copyList.GetFrontElement());
	}

	WHEN("string")
	{
		CMyList<std::string> list;
		list.PushBack("str1");
		list.PushBack("str2");
		CMyList<std::string> copyList(std::move(list));
		CHECK(0 == list.GetSize());
		CHECK(2 == copyList.GetSize());
		CHECK("str1" == copyList.GetFrontElement());
	}
}

TEST_CASE("operator == for CIterator")
{
	WHEN("int")
	{
		CMyList<int> list;
		list.PushBack(1);
		list.PushBack(2);
		auto it1 = list.begin();
		auto it2 = list.begin();
		CHECK(it1 == it2);
		it2 = --list.end();
		CHECK(!(it1 == it2));
	}

	WHEN("string")
	{
		CMyList<std::string> list;
		list.PushBack("str1");
		list.PushBack("str2");
		auto it1 = list.begin();
		auto it2 = list.begin();
		CHECK(it1 == it2);
		it2 = --list.end();
		CHECK(!(it1 == it2));
	}
}

TEST_CASE("operator != for CIterator")
{
	WHEN("int")
	{
		CMyList<int> list;
		list.PushBack(1);
		list.PushBack(2);
		auto it1 = list.begin();
		auto it2 = list.begin();
		CHECK(!(it1 != it2));
		it2 = --list.end();
		CHECK(it1 != it2);

		CMyList<int> listCopy(list);
		CHECK(list.begin() != listCopy.begin());
	}

	WHEN("string")
	{
		CMyList<std::string> list;
		list.PushBack("str1");
		list.PushBack("str2");
		auto it1 = list.begin();
		auto it2 = list.begin();
		CHECK(!(it1 != it2));
		it2 = --list.end();
		CHECK(it1 != it2);
	}
}

TEST_CASE("Prefix operator for CIterator")
{
	CMyList<int> intList;
	intList.PushBack(1);
	intList.PushBack(2);
	intList.PushBack(3);

	CMyList<std::string> stringList;
	stringList.PushBack("str1");
	stringList.PushBack("str2");
	stringList.PushBack("str3");

	WHEN("increment")
	{
		WHEN("int")
		{
			auto it = intList.begin();
			++it;
			CHECK(2 == *it);
			++it;
			CHECK(3 == *it);
			++it;
			CHECK(intList.end() == it);

			CHECK_THROWS(++it);

			it = intList.rend();
			CHECK_THROWS(++it);
		}

		WHEN("string")
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
	}

	WHEN("decrement")
	{
		WHEN("int")
		{
			auto it = intList.end();
			--it;
			CHECK(3 == *it);
			--it;
			--it;
			CHECK(intList.begin() == it);

			CHECK_THROWS(--it);

			it = intList.rbegin();
			CHECK_THROWS(--it);
		}

		WHEN("string")
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
}

TEST_CASE("Postfix operator for CIterator")
{
	CMyList<int> intList;
	intList.PushBack(1);
	intList.PushBack(2);

	CMyList<std::string> stringList;
	stringList.PushBack("str1");
	stringList.PushBack("str2");

	WHEN("increment")
	{
		WHEN("string")
		{
			auto it = stringList.begin()++;
			CHECK("str2" == *it);
			it++;
			CHECK(stringList.end() == it);

			CHECK_THROWS(it++);

			it = stringList.rend();
			CHECK_THROWS(it++);
		}
		WHEN("int")
		{
			auto it = intList.begin()++;
			CHECK(2 == *it);
		}
	}

	WHEN("decrement")
	{
		WHEN("string")
		{
			auto it = stringList.end()--;
			CHECK("str2" == *it);
			it--;
			CHECK(stringList.begin() == it);

			CHECK_THROWS(it--);
			it = stringList.rbegin();
			CHECK_THROWS(it--);
		}

		WHEN("int")
		{
			auto it = --intList.end();
			CHECK(2 == *it);
		}
	}
}