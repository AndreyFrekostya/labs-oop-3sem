#include "Utils.h"

StartsWithLetter::StartsWithLetter(char c) : letter(c) {}

bool StartsWithLetter::operator() (const string& s) const
{
	return !s.empty() && s[0] == letter;
}

EqualsString::EqualsString(const string& t) : target(t) {}

bool EqualsString::operator() (const string& s) const
{
	return s == target;
}
