#pragma once
#include <iostream>

// Прямоугольник, заданный координатами левого верхнего угла и размерами
class Rect
{
private:
	double x, y, w, h;
public:
	Rect(double x_ = 0., double y_ = 0., double w_ = 0., double h_ = 0.);

	double CenterDistance() const;

	bool operator< (const Rect& r) const;	// сортировка по удалению центра от начала координат

	friend std::ostream& operator<< (std::ostream& os, const Rect& r);
};
