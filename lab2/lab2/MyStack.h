#pragma once

#include <iostream>

using namespace std;

class StackOverflow {};
class StackUnderflow {};

class StackOutOfRange
{
public:
	void Out() { cout << "\nIndex out of range"; }
};

template <class T, int N> class MyStack
{

private:
	T data[N];
	int size;
public:
	MyStack() : size(0) {}

	T& operator[] (int index)
	{
		if (index < 0 || index >= size)
			throw StackOutOfRange();
		return data[index];
	}

	int GetSize() { return size; }
	int Capacity() { return N; }

	void Push(const T& value)
	{
		if (size >= N)
			throw StackOverflow();
		data[size++] = value;
	}

	T Pop()
	{
		if (size <= 0)
			throw StackUnderflow();
		return data[--size];
	}

};
