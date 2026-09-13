#include <iostream>
#include <cstring>
#include "MyString.h"

using namespace std;

void MyString::Copy (char* s)
{
	delete [] m_pStr;
	// Динамически выделяем требуемое количество памяти.
	int len = strlen(s) + 1;
	m_pStr = new char[len];
	// + 1, так как нулевой байт тоже нужно скопировать
	// Если память выделена, копируем строку-аргумент в строку-член класса
	if (m_pStr)
		strncpy(m_pStr, s, len);
}

// Определение конструктора.
MyString::MyString (char* s)
{
	m_pStr = 0;
	Copy(s);
}

// Конструктор копирования
MyString::MyString (const MyString& s)
{
	m_pStr = 0;
	Copy(s.m_pStr);
}

// Присвоение
MyString& MyString::operator= (const MyString& s)
{
	if (this == &s)
		return *this;
	Copy(s.m_pStr);
	return *this;
}

// Определение деструктора.
MyString::~MyString()
{
	// Освобождение памяти, занятой в конструкторе для строки-члена класса
	delete[] m_pStr;
}

// Метод класса
char* MyString::GetString()
{
	return m_pStr;
}

int MyString::GetLength()
{
	return strlen(m_pStr) + 1;
}

void MyString::Out()
{
	cout << m_pStr;
}
