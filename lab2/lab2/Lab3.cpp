//=======================================================================
//	Лабораторная №3. Шаблоны функций. Шаблоны классов. Стандартные шаблоны С++.
//				Обработка исключений.
//=======================================================================
//Используйте недостающие файлы из лабораторной 2
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include "MyVector.h"
#include "MyString.h"
#include "Utils.h"
#include "MyStack.h"

using namespace std;

int main()
{

	//===========================================================
	// Шаблоны функций
	//===========================================================
	// Создайте шаблон функции перестановки двух параметров - Swap().
	// Проверьте работоспособность созданного шаблона с помощью
	// приведенного ниже фрагмента.
	{
		int i = 1, j = -1;
		Swap (i, j);
		cout << i << " " << j << endl;

		double a = 0.5, b = -5.5;
		Swap (a, b);
		cout << a << " " << b << endl;

		Vector u(1,2), w(-3,-4);
		Swap(u, w);
		u.Out();
		w.Out();

		// Если вы достаточно развили класс MyString в предыдущей работе,
		// то следующий фрагмент тоже должен работать корректно.
		
		MyString s1 ("Your fault"), s2 ("My forgiveness");
		Swap (s1, s2);
		s1.Out();
		s2.Out();

		cout << endl;
	}
	//===========================================================
	// Шаблоны классов
	//===========================================================
	// Создайте шаблон класса MyStack для хранения элементов любого типа T.
	// В качестве основы для стека может быть выбран массив.
	// Для задания максимального размера стека может быть использован
	// параметр-константа шаблона
	// Обязательными операциями со стеком являются "Push" и "Pop","GetSize" и "Capacity"
	// Необязательной - может быть выбор по индексу (operator[]).
	// Для того, чтобы гарантировать корректное выполнение этих операций 
	// следует генерировать исключительные ситуации.
	
	// С помощью шаблона MyStack создайте стек переменных типа int, затем
	// стек переменных типа double и, наконец, стек из переменных типа Vector 
	// Если вы подготовите три класса для обработки исключений,
	// то следующий фрагмент должен работать
	try
	{
		cout << "\tTest MyStack\n";
		MyStack <int, 3> stack;

		cout << "\nInteger Stack capacity: " << stack.Capacity();

		stack.Push(1);
		stack.Push(2);
		stack.Push(3);

		cout << "\nInteger Stack has: " << stack.GetSize() << " elements";

//		stack.Push(4);	// Здесь должно быть "выброшено" исключение

		cout << "\nInteger Stack pops: " << stack.Pop();
		cout << "\nInteger Stack pops: " << stack.Pop();

		cout << "\nInteger Stack has: " << stack.GetSize() << " elements";
		stack.Pop();
//		stack.Pop();		// Здесь должно быть "выброшено" исключение
		stack.Push(2);

//		int i = stack[3];	// Здесь должно быть "выброшено" исключение

		MyStack<Vector, 5> ptStack;

		cout << "\nVector Stack capacity: " << ptStack.Capacity();

		ptStack.Push(Vector(1,1));
		ptStack.Push(Vector(2,2));

		cout << "\nVector Stack pops: ";
		// Используйте метод класса Vector для вывода элемента
		ptStack.Pop().Out();

		cout << "\nVector Stack has: " << ptStack.GetSize() << " elements";
	}
	catch (StackOverflow)
	{
		cout << "\nStack overflow";
	}
	catch (StackUnderflow)
	{
		cout << "\nStack underflow";
	}
	catch (StackOutOfRange o)
	{
		o.Out();
	}

	//=======================================================================
	// Контейнеры стандартной библиотеки. Последовательности типа vector
	//=======================================================================
	
	// Создайте пустой вектор целых чисел. Узнайте его размер с помощью метода size(),
	// С помощью метода push_back() заполните вектор какими-либо значениями.
	// Получите новый размер вектора и выведите значения его элементов.
	// В процессе работы с вектором вы можете кроме количества реально заполненных
	// элементов (size()) узнать максимально возможное количество элементов (max_size()),
	// а также зарезервированную память (capacity()).

	vector<int> v;
	int n = v.size();

	cout << "\n" << n << endl;

	v.push_back(-1);
	v.push_back(-2);

	pr (v, "vector");


	n = v.size();

	cout << n << endl;

	v.push_back(-1);

	n = v.capacity();

	cout << n << endl;

	n = v.max_size();

	cout << n << endl;
		
	// Так как мы часто будем выводить последовательности, то целесообразно
	// создать шаблон функции для вывода любого контейнера.
	// Проанализируйте коды такого шабдлона (pr), который приведен выше
	// Используйте его для вывода вашего вектора

	pr (v, "Vector of ints");

	// Используем другой конструктор для создания вектора вещественных
	// с начальным размером в 2 элемента и заполнением (222.).
	// Проверим параметры вектора. Затем изменим размер вектора и его заполнение
	// (метод - resize()) и вновь проверим параметры.

	vector<double> vd(2, 222.);
	pr (vd, "Vector of doubles");
	n = vd.size();
	cout << n << endl;
	n = vd.capacity();
	cout << n << endl;
	n = vd.max_size();
	cout << n << endl;

	vd.resize(5, 333.);

	pr (vd, "After resize");
	n = vd.size();
	cout << n << endl;
	n = vd.capacity();
	cout << n << endl;
	n = vd.max_size();
	cout << n << endl;

	// Используя метод at(), а также операцию выбора [], измените значения
	// некоторых элементов вектора и проверьте результат.
	vd.at(0) = 111.;
	vd[1] = 999.;
	pr (vd, "After at");

	// Создайте вектор вещественных, который является копией существующего.
	vector<double> wd(vd);
	pr (wd, "Copy");

	// Создайте вектор, который копирует часть существующей последовательности
	vector<double> ud(vd.begin() + 1, vd.begin() + 3);
	cout << *(vd.begin()) << endl;
	pr (ud, "Copy part");

	// Создайте вектор вещественных, который является копией части обычного массива.
	double ar[] = { 0., 1., 2., 3., 4., 5. };

	vector<double> va(ar + 1, ar + 4);
	pr (va, "Copy part of array");

	// Создайте вектор символов, который является копией части обычной строки
	char s[] = "Array is a succession of chars";

	vector<char> vc(s, s + 5);
	pr (vc, "Copy part of c-style string");

	// Создайте вектор элементов типа Vector и инициализируйте
	// его вектором с координатами (1,1).

	vector<Vector> vv(3, Vector(1,1));

	cout << "\n\nvector of Vectors\n";
	for (int i=0;  i < vv.size();  i++)
		vv[i].Out();

	// Создайте вектор указателей на Vector и инициализируйте его адресами
	// объектов класса Vector

	vector<Vector*> vp;
	for (int i=0;  i < vv.size();  i++)
		vp.push_back(&vv[i]);

	cout << "\n\nvector of pointers to Vector\n";

	for (int i=0;  i < vp.size();  i++)
		vp[i]->Out();

	// Научитесь пользоваться методом assign и операцией
	// присваивания = для контейнеров типа vector.
	vp.assign(vv.size(), &vv[0]);

	cout << "\n\nAfter assign\n";
	for (int i=0;  i < vp.size();  i++)
		vp[i]->Out();

	vector<Vector*> vpAssigned;
	vpAssigned = vp;

	cout << "\n\nAfter operator=\n";
	for (int i = 0; i < vpAssigned.size(); i++)
		vpAssigned[i]->Out();

	// Декларируйте новый вектор указателей на Vector и инициализируйте его
	// с помощью второй версии assign
	vector<Vector*> vpNew;
	vpNew.assign(vp.begin(), vp.end());

	cout << "\n\nNew vector after assign\n";
	for (int i=0;  i < vpNew.size();  i++)
		vpNew[i]->Out();
	

	// На базе шаблона vector создание двухмерный массив и
	// заполните его значениями разными способами.
	// Первый вариант - прямоугольная матрица
	// Второй вариант - ступенчатая матрица

	//========= Прямоугольная матрица
	int rows = 4, cols = 3;
	vector<vector<double>> vddRect(rows, vector<double>(cols));

	for (int i=0;  i < vddRect.size();  i++)
		for (int j=0;  j < vddRect[i].size();  j++)
			vddRect[i][j] = i * cols + j;

	cout << "\n\nTest rect matrix\n";
	for (int i=0;  i < vddRect.size();  i++)
	{
		cout << endl;
		for (int j=0;  j < vddRect[i].size();  j++)
			cout << vddRect[i][j] << "  ";
	}

	//========= Ступенчатая матрица
	vector<vector<double>> vdd(5);

	for (int i=0;  i < vdd.size();  i++)
		vdd[i] = vector<double>(i+1, double(i));

	cout << "\n\n\tTest vector of vector<double>\n";
	for (int i=0;  i < vdd.size();  i++)
	{
		cout << endl;
		for (int j=0;  j < vdd[i].size();  j++)
			cout << vdd[i][j] << "  ";
	}
  


	//===================================
	// Простейшие действия с контейнерами
	//===================================
	//3б. Получение значения первого и последнего элементов последовательности.
	//Получение размера последовательности. Присваивание значений
	//элементов одной последовательности элементам другой - assign().

	//Создайте и проинициализируйте вектор из элементов char. Размер -
	//по желанию.
	vector<char> vChar1 = { 'A', 'B', 'C', 'D', 'E' };

	//Создайте и проинициализируйте массив из элементов char. Размер -
	//по желанию.
	char cMas[] = "Hello, world!";

	//Получите значение первого элемента вектора ( front() )
	cout << "\n\nvChar1 front: " << vChar1.front();

	//Получите значение последнего элемента вектора ( back() )
	cout << "\nvChar1 back: " << vChar1.back();

	//Получите размер вектора
	cout << "\nvChar1 size: " << vChar1.size();

	//Присвойте вектору любой диапазон из значений массива cMas.
	vChar1.assign(cMas + 2, cMas + 8);

	//Проверьте размер вектора, первый и последний элементы.
	cout << "\n\nAfter assign from cMas:";
	cout << "\nvChar1 size: " << vChar1.size();
	cout << "\nvChar1 front: " << vChar1.front();
	cout << "\nvChar1 back: " << vChar1.back();


	//3в. Доступ к произвольным элементам вектора с проверкой - at()
	//и без проверки - []
	//Создайте неинициализированный вектор из 8 элементов char - vChar2.
	vector<char> vChar2(8);

	//С помощью at() присвойте четным элементам вектора значения
	//элементов vChar1 из предыдущего задания,
	for (int i = 0; i < 4; i++)
		vChar2.at(i * 2) = vChar1.at(i);

	//а с помощью [] присвойте нечетным элементам вектора vChar2 значения
	//массива {'K','U','K','U'}.
	char kMas[] = { 'K', 'U', 'K', 'U' };
	for (int i = 0; i < 4; i++)
		vChar2[i * 2 + 1] = kMas[i];

	pr (vChar2, "vChar2");

	//Попробуйте "выйти" за границы вектора с помощью at() и
	//с помощью []. Обратите внимание: что происходит при
	//попытке обращения к несуществующему элементу в обоих случаях
	try
	{
		vChar2.at(100) = 'X';	// at() проверяет границы и выбрасывает исключение
	}
	catch (out_of_range& e)
	{
		cout << "\n\nout_of_range " << endl;
	}

	//vChar2[100] = 'X';	// [] границы не проверяет - неопределенное поведение

	//3г.Добавьте в конец вектора vChar2  - букву Z (push_back()). Для
	//расширения кругозора можете ее сразу же и выкинуть (pop_back())
	vChar2.push_back('Z');
	pr (vChar2, "After push_back('Z')");

	vChar2.pop_back();
	pr (vChar2, "After pop_back()");

	//3д. Вставка-удаление элемента последовательности insert() - erase()
	//Очистка последовательности - clear()

	//Вставьте перед каждым элементом вектора vChar2 букву 'W'
	for (size_t i = 0;  i < vChar2.size();  i = i + 2)
		vChar2.insert(vChar2.begin() + i, 'W');

	pr (vChar2, "After insert 'W' before each element");

	//Вставьте перед 5-ым элементом вектора vChar2 3 буквы 'X'
	vChar2.insert(vChar2.begin() + 4, 3, 'X');

	pr (vChar2, "After insert 3 'X' before 5th element");

	//Вставьте перед 2-ым элементом вектора vChar2 с третьего по
	//шестой элементы массива "aaabbbccc"
	char abcMas[] = "aaabbbccc";
	vChar2.insert(vChar2.begin() + 1, abcMas + 2, abcMas + 6);

	pr (vChar2, "After insert range from abcMas before 2nd element");

	//Сотрите c первого по десятый элементы vChar2
	vChar2.erase(vChar2.begin(), vChar2.begin() + 10);

	pr (vChar2, "After erase first 10 elements");

	//Уничтожьте все элементы последовательности - clear()
	vChar2.clear();

	pr (vChar2, "After clear");
	cout << "\nvChar2 size: " << vChar2.size();

	//Создание двухмерного массива


/////////////////////////////////////////////////////////////////////
	//Задание 4. Списки. Операции, характерные для списков.
	//Создайте два пустых списка из элементов Vector - ptList1 и
	//ptList2
	list<Vector> ptList1, ptList2;

	//Наполните оба списка значениями с помощью методов push_back(),
	//push_front, insrert()
	ptList1.push_back(Vector(3,4));
	ptList1.push_front(Vector(10,10));
	ptList1.insert(ptList1.end(), Vector(1,1));

	ptList2.push_back(Vector(2,2));
	ptList2.push_front(Vector(6,8));
	ptList2.insert(ptList2.end(), Vector(0,1));

	cout << "\n\nptList1 before sort:\n";
	for (list<Vector>::iterator it = ptList1.begin();  it != ptList1.end();  it++)
		it->Out();

	cout << "\n\nptList2 before sort:\n";
	for (list<Vector>::iterator it = ptList2.begin();  it != ptList2.end();  it++)
		it->Out();

	//Отсортируйте списки - sort().
	//Подсказка: для того, чтобы работала сортировка, в классе Vector
	//должен быть переопределен оператор "<"
	ptList1.sort();
	ptList2.sort();

	cout << "\n\nptList1 after sort:\n";
	for (list<Vector>::iterator it = ptList1.begin();  it != ptList1.end();  it++)
		it->Out();

	cout << "\n\nptList2 after sort:\n";
	for (list<Vector>::iterator it = ptList2.begin();  it != ptList2.end();  it++)
		it->Out();

	//Объедините отсортированные списки - merge(). Посмотрите: что
	//при этом происходит со вторым списком.
	ptList1.merge(ptList2);

	cout << "\n\nptList1 after merge:\n";
	for (list<Vector>::iterator it = ptList1.begin();  it != ptList1.end();  it++)
		it->Out();

	cout << "\n\nptList2 after merge, size = " << ptList2.size() << ":\n";
	for (list<Vector>::iterator it = ptList2.begin();  it != ptList2.end();  it++)
		it->Out();

	//Исключение элемента из списка - remove()
	//Исключите из списка элемент с определенным значением.
	//Подсказка: для этого необходимо также переопределить
	//в классе Vector оператор "=="
	ptList1.remove(Vector(2,2));

	cout << "\n\nptList1 after remove(Vector(2,2)):\n";
	for (list<Vector>::iterator it = ptList1.begin();  it != ptList1.end();  it++)
		it->Out();

/////////////////////////////////////////////////////////////////////
	//Задание 5. Стандартные алгоритмы.Подключите заголовочный файл
	// <algorithm>
	//5а. Выведите на экран элементы ptList1 из предыдущего
	//задания с помощью алгоритма for_each()
	cout << "\n\nptList1 via for_each:\n";
	for_each(ptList1.begin(), ptList1.end(), PrintVector);

	//5б.С помощью алгоритма find() найдите итератор на элемент Vector с
	//определенным значением. С помощью алгоритма find_if() найдите
	//итератор на элемент, удовлетворяющий определенному условию,
	//например, обе координаты точки должны быть больше 2.
	//Подсказка: напишите функцию-предикат, которая проверяет условие
	//и возвращает boolean-значение (предикат может быть как глобальной
	//функцией, так и методом класса)
	list<Vector>::iterator itFound = find(ptList1.begin(), ptList1.end(), Vector(3,4));
	cout << "\n\nfind(Vector(3,4)):";
	if (itFound != ptList1.end()) {
		itFound->Out();
	}
	else {
		cout << "not found" ;
	}

	list<Vector>::iterator itFoundIf = find_if(ptList1.begin(), ptList1.end(), BothGreaterThan2);
	cout << "\n\nfind_if(both coords > 2):";
	if (itFoundIf != ptList1.end()) {
		itFoundIf->Out();
	}
	else {
		cout << " not found";
	}

	//Создайте список из указателей на элеметы Vector. С помощью
	//алгоритма find_if() и предиката (можно использовать предикат -
	//метод класса Vector, определенный в предыдущем задании) найдите в
	//последовательности элемент, удовлетворяющий условию
	list<Vector*> ptrList;
	for (list<Vector>::iterator it = ptList1.begin(); it != ptList1.end(); it++) {
		ptrList.push_back(&(*it));
	}

	list<Vector*>::iterator itPtrFound = find_if(ptrList.begin(), ptrList.end(), PtrBothGreaterThan2);
	cout << "\n\nfind_if() over list of pointers (both coords > 2):";
	if (itPtrFound != ptrList.end()) {
		(*itPtrFound)->Out();
	}
	else {
		cout << " not found";
	}

	//5в. Создайте список элементов Vector. Наполните список
	//значениями. С помощью алгоритма replace() замените элемент
	//с определенным значением новым значением. С помощью алгоритма
	//replace_if() замените элемент, удовлетворяющий какому-либо
	//условию на определенное значение. Подсказка: условие
	//задается предикатом.

	//Сформировали значения элементов списка
	list<Vector> ptList3;
	ptList3.push_back(Vector(1,1));
	ptList3.push_back(Vector(3,4));
	ptList3.push_back(Vector(5,5));
	ptList3.push_back(Vector(0,0));

	cout << "\n\nptList3 before replace:\n";

	for_each(ptList3.begin(), ptList3.end(), PrintVector);

	replace(ptList3.begin(), ptList3.end(), Vector(3,4), Vector(100,100));

	cout << "\n\nptList3 after replace(Vector(3,4) -> Vector(100,100)):\n";

	for_each(ptList3.begin(), ptList3.end(), PrintVector);

	replace_if(ptList3.begin(), ptList3.end(), BothGreaterThan2, Vector(-1,-1));

	cout << "\n\nptList3 after replace_if(both coords > 2 -> Vector(-1,-1)):\n";

	for_each(ptList3.begin(), ptList3.end(), PrintVector);

	//5г. Создайте вектор строк (string). С помощью алгоритма count()
	//сосчитайте количество одинаковых строк. С помощью алгоритма
	//count_if() сосчитайте количество строк, начинающихся с заданной
	//буквы
	vector<string> vStr = { "apple", "banana", "apple", "avocado", "cherry", "apple" };

	int cntApple = count(vStr.begin(), vStr.end(), string("apple"));

	cout << "\n\ncount(\"apple\") = " << cntApple;

	int cntA = count_if(vStr.begin(), vStr.end(), StartsWithLetter('a'));

	cout << "\ncount_if(starts with 'a') = " << cntA;

	//5д. С помощью алгоритма count_if() сосчитайте количество строк,
	//которые совпадают с заданной строкой. Подсказка: смотри тему
	//объекты-функции
	int cntEq = count_if(vStr.begin(), vStr.end(), EqualsString("apple"));

	cout << "\ncount_if(equals \"apple\") = " << cntEq;

	cout <<"\n\n";
}