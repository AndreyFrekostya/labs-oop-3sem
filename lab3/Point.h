#pragma once
#include <iostream>

// Точка на плоскости - аналог класса Point из предыдущей лабораторной
class Point
{
private:
	double x, y;
public:
	Point(double x_ = 0., double y_ = 0.);

	double X() const;
	double Y() const;

	void Shift(double dx, double dy);

	bool operator< (const Point& p) const;	// нужен для set/sort - упорядочиваем по расстоянию от начала координат
	bool operator== (const Point& p) const;

	friend std::ostream& operator<< (std::ostream& os, const Point& p);
};
