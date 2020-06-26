#pragma once
#include <string>
#include <memory>
#include <stdexcept>

class CStringList
{
public:
	struct Node
	{
		Node(std::string data, Node* prev, std::unique_ptr<Node>&& next)
			:data(std::move(data)),
			prev(prev),
			next(std::move(next))
		{
		}
		std::string data;
		Node* prev;
		std::unique_ptr<Node> next;
	};

	class CIterator
	{
		friend class CStringList;
		CIterator(Node *node, bool isRevers = false);
	public:
		CIterator();

		bool operator != (const CIterator& it) const;
		bool operator == (const CIterator& it) const;

		CIterator& operator++();
		CIterator& operator--();

		CIterator& operator++(int);
		CIterator& operator--(int);

		std::string& operator*() const;

	private:
		Node* m_node = nullptr;
		bool m_isRevers = false;
	};


	CStringList();
	CStringList(const CStringList& other);
	CStringList(CStringList&& other) noexcept;
	~CStringList();

	void Insert(const std::string& str, const CIterator& it);

	void PushBack(const std::string& str);
	void PushFront(const std::string& str);

	std::string& GetFrontElement() const;
	std::string& GetBackElement() const;
	std::string const& GetFrontElement();
	std::string const& GetBackElement();

	void Clear();
	void Erase(const CIterator& it);

	CIterator begin();
	CIterator end();
	const CIterator begin() const;
	const CIterator end() const;

	const CIterator cbegin()const;
	const CIterator cend() const;

	CIterator rbegin();
	CIterator rend();

	const CIterator crbegin() const;
	const CIterator crend() const;

	size_t GetSize() const;
	bool IsEmpty() const;

	CStringList& operator=(CStringList& other);
	CStringList& operator=(CStringList&& other) noexcept;

private:
	bool IsIteratorCorrect(const CIterator& it) const;

	size_t m_size;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode;
};

