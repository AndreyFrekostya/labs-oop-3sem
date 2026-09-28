#pragma once
#include <iostream>

// Простейшая динамическая строка - аналог класса MyString из предыдущей лабораторной
class MyString
{
private:
	char* m_pStr;
	void Copy(const char* s);
public:
	MyString();
	MyString(const char* s);
	MyString(const MyString& s);
	MyString& operator= (const MyString& s);
	~MyString();

	const char* GetString() const;
	int GetLength() const;

	friend std::ostream& operator<< (std::ostream& os, const MyString& s);
};
