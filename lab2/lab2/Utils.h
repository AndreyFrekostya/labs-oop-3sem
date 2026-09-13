#pragma once

#include <iostream>
#include <string>

using namespace std;

template <class T> void pr(T& v, string s)
{
	cout << "\n\n" << s << " Sequence:\n";

	T::iterator p;
	int i;

	for (p = v.begin(), i = 0; p != v.end(); p++, i++)
	{
		cout << i + 1 << ". " << *p << endl;
	}
	cout << "End Sequence" << endl;
}

template <class T> void Swap(T& v1, T& v2)
{
	T temp = v1;
	v1 = v2;
	v2 = temp;
}

class StartsWithLetter
{
private:
	char letter;
public:
	StartsWithLetter(char c);
	bool operator() (const string& s) const;
};

class EqualsString
{
private:
	string target;
public:
	EqualsString(const string& t);
	bool operator() (const string& s) const;
};
