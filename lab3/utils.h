#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cstring>
#include <cctype>
#include <algorithm>

#include "Point.h"

using namespace std;

//====================================================================================
// Вспомогательные шаблоны, функции и предикаты, не относящиеся к конкретному классу
//====================================================================================

// Универсальный шаблон для вывода на печать любой последовательности, у которой
// определены begin()/end() и для элементов которой определён operator<<
template <class T> void pr(T& v, std::string s)
{
	std::cout << "\n\n" << s << " Sequence:\n";

	typename T::iterator p;
	int i;

	for (p = v.begin(), i = 0; p != v.end(); p++, i++)
	{
		std::cout << i + 1 << ". " << *p << std::endl;
	}
	std::cout << "End Sequence" << std::endl;
}

// Компаратор для указателей на C-строки: сравниваем СОДЕРЖИМОЕ, а не адреса
struct CStrLess
{
	bool operator() (const char* a, const char* b) const
	{
		return strcmp(a, b) < 0;
	}
};

// Шаблонная функция для печати stack (LIFO). Контейнер берём ПО ЗНАЧЕНИЮ - то есть
// работаем с копией, а не с оригиналом, поэтому исходный стек после вывода не меняется.
// Если бы контейнер принимался по ссылке, то после вывода он бы полностью опустел,
// т.к. "заглянуть" в середину stack/queue/priority_queue нельзя - единственный
// способ получить данные - снимать их с "верхушки" через top()/front() и pop().
template <class T> void PrintStack(stack<T> s, string name)
{
	std::cout << "\n\n" << name << " stack Sequence:\n";
	int i = 1;
	while (!s.empty())
	{
		std::cout << i++ << ". " << s.top() << std::endl;
		s.pop();
	}
	std::cout << "End Sequence" << std::endl;
}

template <class T, class Container = std::deque<T>>
void PrintQueue(std::queue<T, Container> q, std::string name)
{
	std::cout << "\n\n" << name << " (queue, FIFO) Sequence:\n";
	int i = 1;
	while (!q.empty())
	{
		std::cout << i++ << ". " << q.front() << std::endl;
		q.pop();
	}
	std::cout << "End Sequence" << std::endl;
}

// Перегрузка для очередей указателей - выводим значение, на которое указывает
// front(), а не сам адрес (иначе operator<< напечатал бы указатель как void*)
template <class T, class Container = std::deque<T*>>
void PrintQueue(std::queue<T*, Container> q, std::string name)
{
	std::cout << "\n\n" << name << " (queue, FIFO) Sequence:\n";
	int i = 1;
	while (!q.empty())
	{
		std::cout << i++ << ". " << *q.front() << std::endl;
		q.pop();
	}
	std::cout << "End Sequence" << std::endl;
}

template <class T, class Container, class Compare>
void PrintPQueue(std::priority_queue<T, Container, Compare> pq, std::string name)
{
	std::cout << "\n\n" << name << " (priority_queue) Sequence:\n";
	int i = 1;
	while (!pq.empty())
	{
		std::cout << i++ << ". " << pq.top() << std::endl;
		pq.pop();
	}
	std::cout << "End Sequence" << std::endl;
}

// Шаблонная функция для печати map/multimap (пары "ключ - значение")
template <class Map>
void PrintMap(const Map& m, std::string name)
{
	std::cout << "\n\n" << name << " Sequence:\n";
	int i = 1;
	for (typename Map::const_iterator it = m.begin(); it != m.end(); ++it, ++i)
	{
		std::cout << i << ". " << it->first << " - " << it->second << std::endl;
	}
	std::cout << "End Sequence" << std::endl;
}

// Предикат для for_each - печать произвольного элемента
template <class T> void PrintElem(const T& t)
{
	std::cout << t << " ";
}

// Предикат для for_each - сдвиг точки на (dx, dy)
class ShiftPoint
{
private:
	double dx, dy;
public:
	ShiftPoint(double dx_, double dy_) : dx(dx_), dy(dy_) {}
	void operator() (Point& p) const { p.Shift(dx, dy); }
};

// Предикат для find_if - координаты x и y лежат в промежутке [min, max]
class PointCoordsInRange
{
private:
	double min, max;
public:
	PointCoordsInRange(double min_, double max_) : min(min_), max(max_) {}
	bool operator() (const Point& p) const
	{
		return p.X() >= min && p.X() <= max && p.Y() >= min && p.Y() <= max;
	}
};

// Предикат для transform - перевод ОДНОГО символа в нижний регистр
struct ToLowerChar
{
	char operator() (unsigned char c) const { return tolower(c); }
};

// Перевод СТРОКИ в нижний регистр с помощью transform (посимвольно, через ToLowerChar)
inline std::string ToLowerStr(const std::string& s)
{
	std::string res = s;
	std::transform(res.begin(), res.end(), res.begin(), ToLowerChar());
	return res;
}
