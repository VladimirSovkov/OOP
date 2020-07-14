#include <memory>
#include <iostream>
#include <list>

using namespace std;

struct Node
{
	// написать недостающий код
	Node(int data, std::unique_ptr<Node>&& next)
		:m_value(std::move(data)),
		m_next(std::move(next))
	{
	}
	
	int m_value;
	unique_ptr<Node> m_next;
};

class List
{
	friend struct Node;
public:
	class Iterator
	{
		friend struct Node;

	public:
		Iterator(Node* node)
			:m_node(node)
		{
		};

		Iterator()
		{
			m_node = nullptr;
		}

		// operator++ (префиксна€ верси€)
		Iterator& operator++()
		{
			m_node = m_node->m_next.get();
			return *this;
		};
		
		// operator++ (постфиксна€ верси€)
		Iterator& operator++(int)
		{
			++*this;
			return *this;
		};

		// operator*
		int& operator*() const
		{
			return m_node->m_value;
		};

		// operator==
		bool operator == (const Iterator& it) const
		{
			return (m_node == it.m_node);
		};
		// operator!=
		bool operator != (const Iterator& it) const
		{
			return !(m_node == it.m_node);
			//return !(*this == it);
		};


	private:
		Node* m_node = nullptr;
	};

	List()
	{
		std::unique_ptr<Node> firstNode = std::make_unique<Node>(NULL, nullptr);
		m_firstNode = std::move(firstNode);
	}

	// копирование и присваивание реализовывать не требуетс€
	List(const List&) = delete;
	List& operator=(const List&) = delete;

	~List()
	{
		// при разрушении списка не должен возникать stack overflow
		while(begin() != end())
		{
			m_firstNode = std::move(m_firstNode->m_next);
		}
	}

	void PushFront(int value)
	{
		auto newPointNode = std::make_unique<Node>(value,std::move(m_firstNode));
		m_firstNode = std::move(newPointNode);
	}

	Iterator begin()
	{
		return Iterator(m_firstNode.get());
	}

	// »тератор, указывающий на позицию, следующую за последним элементом списка.
	Iterator end()
	{
		// написать недостающий код
		Iterator itNextEnd = begin();
		Iterator itEnd = itNextEnd;
		while (itNextEnd != nullptr)
		{
			itNextEnd++;
			if (itNextEnd == nullptr)
			{
				return itEnd;
			}
			itEnd++;
		}
		
		return itNextEnd;
	}

private:
	unique_ptr<Node> m_firstNode;
};

int main()
{
	List lst;

	return 1;
	lst.PushFront(3);
	lst.PushFront(2);
	lst.PushFront(4);
	//int a = *lst.end();


	for (int x : lst)
	{
		cout << x << ",";
	}

	// ƒолжно быть выведено "4,2,3,"

	return 0;
}
