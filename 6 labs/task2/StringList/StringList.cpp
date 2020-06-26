#include "StringList.h"

CStringList::CStringList()
{
    std::unique_ptr<Node> lastNode = std::make_unique<Node>("", nullptr, nullptr);
    Node* pointerLastNode = lastNode.get();
    std::unique_ptr<Node> firstNode = std::make_unique<Node>("", nullptr, std::move(lastNode));
   
    m_firstNode = std::move(firstNode);
    m_lastNode = pointerLastNode;
    m_lastNode->prev = m_firstNode.get();
    m_size = 0;
}   

CStringList::CStringList(const CStringList& other)
    :CStringList()
{
    CStringList tmp;
    for (const auto& str : other)
    {
        tmp.Insert(str, tmp.end());
    }
    std::swap(*this, tmp);
}

CStringList::CStringList(CStringList&& other) noexcept
{
    Clear();
    m_firstNode = std::move(other.m_firstNode);
    m_lastNode = other.m_lastNode;
    m_size = other.m_size;

    CStringList emptyStringList;
    other.m_firstNode = std::move(emptyStringList.m_firstNode);
    other.m_lastNode = emptyStringList.m_lastNode;
    other.m_size = emptyStringList.m_size;
}

CStringList::CIterator CStringList::begin()
{
    return CIterator(m_firstNode->next.get());
}

CStringList::CIterator CStringList::end()
{
    return CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::begin() const
{
    return CIterator(m_firstNode->next.get());
}

const CStringList::CIterator CStringList::end() const
{
    return CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::cbegin() const
{
    return CIterator(m_firstNode->next.get());
}

const CStringList::CIterator CStringList::cend() const
{
    return CIterator(m_lastNode);
}

CStringList::CIterator CStringList::rbegin()
{
    return CIterator(m_lastNode->prev, true);
}

CStringList::CIterator CStringList::rend()
{
    return CIterator(m_firstNode.get(), true);
}

const CStringList::CIterator CStringList::crbegin() const
{
    return CIterator(m_lastNode->prev, true);
}

const CStringList::CIterator CStringList::crend() const
{
    return CIterator(m_firstNode.get(), true);
}

size_t CStringList::GetSize() const
{
    return m_size;
}

bool CStringList::IsEmpty() const
{
    return m_size == 0;
}

CStringList& CStringList::operator=(CStringList& other)
{
    if (&other != this)
    {
        CStringList tmp(other);
        std::swap(*this, tmp);
    }
    return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{
    if (&other != this)
    {
        Clear();
        m_firstNode = std::move(other.m_firstNode);
        m_lastNode = other.m_lastNode;
        m_size = other.m_size;

        CStringList emptyStringList;
        other.m_firstNode = std::move(emptyStringList.m_firstNode);
        other.m_lastNode = emptyStringList.m_lastNode;
        other.m_size = emptyStringList.m_size;
    }
    return *this;
}

bool CStringList::IsIteratorCorrect(const CIterator& it) const
{
   if (it == end())
    {
        return true;
    }
    auto objectIterator = this->begin();
    for (; objectIterator != end(); objectIterator++)
    {
        if (it == objectIterator)
        {
            return true;
        }
    }
    return false;
}

CStringList::~CStringList()
{
    Clear();
    m_firstNode = nullptr;
    m_lastNode = nullptr;
}

void CStringList::Insert(const std::string& str, const CIterator& it)
{
    if (!it.m_node)
    {
        throw std::runtime_error("this iterator does not exist");
    }
    else if(!IsIteratorCorrect(it))
    {
        throw std::runtime_error("such an iterator does not exist in the object");
    }
    auto newPointNode = std::make_unique<Node>(str, it.m_node->prev, std::move(it.m_node->prev->next));
    it.m_node->prev = newPointNode.get();
    newPointNode->prev->next = std::move(newPointNode);
    m_size++;
}

void CStringList::PushBack(const std::string& str)
{
    Insert(str, end());
}

void CStringList::PushFront(const std::string& str)
{
    Insert(str, begin());
}

std::string& CStringList::GetFrontElement() const
{
    if (IsEmpty())
    {
        throw std::runtime_error("unable to get item from empty list");
    }
    return m_firstNode->next->data;
}

std::string& CStringList::GetBackElement() const
{
    if (IsEmpty())
    {
        throw std::runtime_error("unable to get item from empty list");
    }
    return m_lastNode->prev->data;
}

std::string const& CStringList::GetFrontElement()
{
    if (IsEmpty())
    {
        throw std::runtime_error("unable to get item from empty list");
    }
    return m_firstNode->next->data;
}

std::string const& CStringList::GetBackElement()
{
    if (IsEmpty())
    {
        throw std::runtime_error("unable to get item from empty list");
    }
    return m_lastNode->prev->data;
}

void CStringList::Clear()
{
    while (!IsEmpty())
    {
        Erase(begin());
    }
}

void CStringList::Erase(const CIterator& it)
{
    if (IsEmpty())
    {
        throw std::runtime_error("cannot delete node in empty list");
    }
    else if (!IsIteratorCorrect(it))
    {
        throw std::runtime_error("such an iterator does not exist in the object");
    }
    else if (it == end())
    {
        throw std::out_of_range("unable to remove item from end position ()");
    }
    
    it.m_node->next->prev = it.m_node->prev;
    it.m_node->prev->next = std::move(it.m_node->next);
    --m_size;
}

CStringList::CIterator::CIterator()
{
    m_node = nullptr;
    m_isRevers = false;
}

CStringList::CIterator::CIterator(Node* node, bool isRevers)
    :m_node(node),
    m_isRevers(isRevers)
{
}

bool CStringList::CIterator::operator==(const CIterator& it) const
{
    return (m_node == it.m_node);
}

bool CStringList::CIterator::operator!=(const CIterator& it) const
{
    return m_node != it.m_node;
}

CStringList::CIterator& CStringList::CIterator::operator++()
{
    if (m_isRevers)
    {
        if (!m_node->prev)
        {
            throw std::out_of_range("you are trying to go beyond the list");
        }
        m_node = m_node->prev;
    }
    else
    {
        if (!m_node->next)
        {
            throw std::out_of_range("you are trying to go beyond the list");
        }
        m_node = m_node->next.get();
    }
    return *this;
}

CStringList::CIterator& CStringList::CIterator::operator--()
{
    if (m_isRevers)
    {
        if (!m_node->next->next)
        {
            throw std::out_of_range("you are trying to go beyond the list");
        }
        m_node = m_node->next.get();
    }
    else
    {
        if (!m_node->prev->prev)
        {
            throw std::out_of_range("you are trying to go beyond the list");
        }
        m_node = m_node->prev;
    }
    return *this;
}

CStringList::CIterator& CStringList::CIterator::operator++(int)
{
    ++*this;
    return *this;
}

CStringList::CIterator& CStringList::CIterator::operator--(int)
{
    --*this;
    return *this;
}

std::string& CStringList::CIterator::operator*() const
{
    if (!m_node->next || !m_node->prev)
    {
        throw std::out_of_range("you are trying to go beyond the list");
    }
    return m_node->data;
}
