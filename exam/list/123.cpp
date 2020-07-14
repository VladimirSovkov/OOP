#include <memory>
#include <iostream>

using namespace std;

struct Node
{
	// написать недостающий код
private:
	int m_value;
	unique_ptr<Node> m_next;
};

class List
{
public:
	class Iterator
	{
		// operator++ (префиксная версия)
		// operator++ (постфиксная версия)
		// operator*
		// operator==
		// operator!=
	};

	List()
	{
	}

	// копирование и присваивание реализовывать не требуется
	List(const List&) = delete;
	List& operator=(const List&) = delete;

	~List()
	{
		// при разрушении списка не должен возникать stack overflow
	}

	void PushFront(int value)
	{
		// написать недостающий код
	}

	Iterator begin()
	{
		// написать недостающий код
	}

	// Итератор, указывающий на позицию, следующую за последним элементом списка.
	Iterator end()
	{
		// написать недостающий код
	}
private:
	unique_ptr<Node> m_firstNode;
};

int main()
{
	List lst;
	lst.PushFront(3);
	lst.PushFront(2);
	lst.PushFront(4);

	for (int x : lst)
	{
		cout << x << ",";
	}

	// Должно быть выведено "4,2,3,"

	return 0;
}
