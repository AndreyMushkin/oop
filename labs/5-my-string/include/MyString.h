#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <vector>

class MyIterator;

class MyString
{
public:

	MyString();
	MyString(const char* pString);
	MyString(const char* pString, size_t length);
	MyString(const std::string& stlString);
	MyString(const MyString& other);
	MyString(MyString&& other) noexcept;

	size_t GetLength() const;
	const char* GetStringData() const;
	MyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other) noexcept;
	MyString& operator+=(const MyString& other);

	const char operator[](size_t index) const;
	char& operator[](size_t index);

	MyIterator begin() const;
	MyIterator end() const;

private:
	void ExtendCapacity(size_t fitSize);
	size_t m_currentSize = 0;
	size_t m_currentCapacity = m_currentSize + 1;

	std::shared_ptr<char[]> m_stringData;
};

class MyIterator
{
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = char;
	using difference_type = size_t;
	using pointer = char*;
	using reference = char&;

	MyIterator();
	MyIterator(pointer data);

	pointer data() const;

	reference operator*();

	const bool operator!=(const MyIterator& other) const;

	MyIterator& operator++();

	MyIterator operator++(int);

private:
	char* m_data;
};

const MyString operator+(MyString lhs, const MyString& rhs);
const bool operator==(const MyString& lhs, const MyString& rhs);
const bool operator!=(const MyString& lhs, const MyString& rhs);
const bool operator<(const MyString& lhs, const MyString& rhs);
const bool operator>(const MyString& lhs, const MyString& rhs);
const bool operator>=(const MyString& lhs, const MyString& rhs);
const bool operator<=(const MyString& lhs, const MyString& rhs);

std::ostream& operator<<(std::ostream& stream, const MyString& string);
std::istream& operator>>(std::istream& stream, MyString& string);
