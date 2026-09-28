#include "Rect.h"
#include <cmath>

Rect::Rect(double x_, double y_, double w_, double h_)
	: x(x_), y(y_), w(w_), h(h_) {
}

double Rect::CenterDistance() const
{
	double cx = x + w / 2., cy = y + h / 2.;
	return sqrt(cx * cx + cy * cy);
}

bool Rect::operator< (const Rect& r) const
{
	return CenterDistance() < r.CenterDistance();
}

std::ostream& operator<< (std::ostream& os, const Rect& r)
{
	os << "Rect(x=" << r.x << ", y=" << r.y << ", w=" << r.w << ", h=" << r.h
		<< ", centerDist=" << r.CenterDistance() << ")";
	return os;
}
