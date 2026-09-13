#include "MyVector.h"


Vector::Vector (double c1, double c2)
{
	x=c1;   y=c2;
}

Vector::Vector ()
{
	x = y = 0.;
}

void Vector::Out()
{
	cout << "\nVector:  x = " << x << ",  y = " << y;
}

//====== Переопределение операций =====//
Vector& Vector::operator= (const Vector& v)
{
	if (this == &v)
		return *this;
	x = v.x;
	y = v.y;
	return *this;
}

bool Vector::operator< (const Vector& v) const	
{
	return (x*x + y*y) < (v.x*v.x + v.y*v.y);
}

bool Vector::operator== (const Vector& v) const
{
	return x == v.x  &&  y == v.y;
}

bool Vector::BothGreaterThan (double val) const
{
	return x > val  &&  y > val;
}

//====== Обёртки-callback'и для алгоритмов STL =====//
bool BothGreaterThan2 (const Vector& v)
{
	return v.BothGreaterThan(2.);
}

bool PtrBothGreaterThan2 (Vector* p)
{
	return p->BothGreaterThan(2.);
}

void PrintVector (Vector& v)
{
	v.Out();
}
