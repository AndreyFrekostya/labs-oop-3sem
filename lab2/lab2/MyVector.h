// Класс Vector, инкапсулируюет функциональность вектора на плоскости
// Добавьте в класс все необходимые конструкторы и методы необходимые для функционирования в данной лабораторной

#include <iostream>
using namespace std;

class Vector
{
private:
	double x, y;	// Координаты вектора на плоскости
public:
	//========== Три конструктора
	Vector (double c1, double c2);
	Vector ();							// Default
	
	//====== Переопределение операций =====//
	Vector& operator= (const Vector& v);	// Присвоение
	bool operator< (const Vector& v) const;	// Сравнение (для sort())
	bool operator== (const Vector& v) const;	// Равенство (для remove())
	void Out();

	bool BothGreaterThan (double val) const;	
};

bool BothGreaterThan2 (const Vector& v);	
bool PtrBothGreaterThan2 (Vector* p);		
void PrintVector (Vector& v);				
