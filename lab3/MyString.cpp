#include "MyString.h"
#include <cstring>

void MyString::Copy(const char* s)
{
	delete[] m_pStr;
	int len = strlen(s) + 1;
	m_pStr = new char[len];
	strncpy_s(m_pStr, len, s, len - 1);
}

MyString::MyString() { m_pStr = new char[1]; m_pStr[0] = 0; }
MyString::MyString(const char* s) { m_pStr = 0; Copy(s); }
MyString::MyString(const MyString& s) { m_pStr = 0; Copy(s.m_pStr); }
MyString& MyString::operator= (const MyString& s)
{
	if (this == &s) return *this;
	Copy(s.m_pStr);
	return *this;
}
MyString::~MyString() { delete[] m_pStr; }

const char* MyString::GetString() const { return m_pStr; }

int MyString::GetLength() const { return strlen(m_pStr); }


std::ostream& operator<< (std::ostream& os, const MyString& s)
{
	os << s.m_pStr;
	return os;
}
