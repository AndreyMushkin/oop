#pragma once
#include <iterator>
#include <stdexcept>
#include "ListNode.h"

class ListBaseIterator
{
public:
	friend class StringList;

	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = size_t;

	bool operator!=(const ListBaseIterator& other) const;
	bool operator==(const ListBaseIterator& other) const;

protected:
	// сделать деструктор защищенным
	// добавить конструктор по умолчанию
	ListBaseIterator(NodePtr data);

	std::string* operator->() const;
	std::string& operator*() const;

	void operator++();
	NodePtr operator++(int);

	void operator--();
	NodePtr operator--(int);

	NodePtr m_nodePtr;
};

class ListConstIterator : public ListBaseIterator
{
public:
	using value_type = const std::string;
	using pointer = const std::string*;
	using reference = const std::string&;

	ListConstIterator(NodePtr data);
	ListConstIterator(const class ListIterator& other);

	pointer operator->() const;

	reference operator*() const;

	ListConstIterator& operator++();
	ListConstIterator operator++(int);

	ListConstIterator& operator--();
	ListConstIterator operator--(int);
};

class ListIterator : public ListBaseIterator
{
public:
	friend class ListConstIterator;

	using value_type = std::string;
	using pointer = std::string*;
	using reference = std::string&;

	ListIterator(NodePtr data);

	pointer operator->() const;

	reference operator*() const;

	ListIterator& operator++();
	ListIterator operator++(int);

	ListIterator& operator--();
	ListIterator operator--(int);
};

// использовать std::reverse_iterator<T>
class ListConstReverseIterator : public ListConstIterator
{
public:
	ListConstReverseIterator(NodePtr data);
	ListConstReverseIterator(const class ListReverseIterator& other);

	ListConstReverseIterator& operator++();
	ListConstReverseIterator operator++(int);

	ListConstReverseIterator& operator--();
	ListConstReverseIterator operator--(int);
};

class ListReverseIterator : public ListIterator
{
public:
	friend class ListConstReverseIterator;

	ListReverseIterator(NodePtr data);

	ListReverseIterator& operator++();
	ListReverseIterator operator++(int);

	ListReverseIterator& operator--();
	ListReverseIterator operator--(int);
};