#include "Point.h"

Point::Point(double x_, double y_) : x(x_), y(y_) {}

double Point::X() const { return x; }
double Point::Y() const { return y; }

void Point::Shift(double dx, double dy) { x += dx; y += dy; }

bool Point::operator< (const Point& p) const
{
	return (x * x + y * y) < (p.x * p.x + p.y * p.y);
}
bool Point::operator== (const Point& p) const
{
	return x == p.x && y == p.y;
}

std::ostream& operator<< (std::ostream& os, const Point& p)
{
	os << "Point(" << p.x << ", " << p.y << ")";
	return os;
}
