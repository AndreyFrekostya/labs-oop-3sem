// Добавьте в класс все необходимые конструкторы и методы необходимые для функционирования в данной лабораторной

class MyString
{
private:
	char* m_pStr;		// Элемент данных класса (адрес строки)
public:
    MyString ();
	MyString (char* s);	// Объявление конструктора
	MyString (const MyString& s);			// Конструктор копирования
	MyString& operator= (const MyString& s);	// Присвоение
    ~MyString();		// Объявление деструктора

	void Copy (char* s);
	char* GetString();	// Объявление метода (accessor)
	int GetLength();	// Объявление метода (длина строки)
	void Out();			// Вывод содержимого строки в консоль
};
