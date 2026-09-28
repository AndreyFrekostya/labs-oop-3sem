// Контейнеры STL:
//deque, stack, queue, priority_queue
//set, multiset, map, multimap
//Итераторы. Стандартные алгоритмы. Предикаты.

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>

#include "Point.h"
#include "Rect.h"
#include "MyString.h"
#include "utils.h"

using namespace std;

int main()
{

	//Очередь с двумя концами - контейнер deque

	//Создайте пустой deque с элементами типа Point. С помощью
	//assign заполните deque копиями элементов вектора. С помощью
	//разработанного Вами в предыдущем задании универсального шаблона
	//выведите значения элементов на печать
	{
		vector<Point> vPts = { Point(1,1), Point(2,3), Point(-1,4), Point(5,-2) };

		deque<Point> dqPts;
		dqPts.assign(vPts.begin(), vPts.end());
		pr(dqPts, "deque<Point>");
	}

	//Создайте deque с элементами типа MyString. Заполните его значениями
	//с помощью push_back(), push_front(), insert()
	//С помощью erase удалите из deque все элементы, в которых строчки
	//начинаются с 'A' или 'a'
	{
		deque<MyString> dqStr;

		dqStr.push_back(MyString("Bravo"));
		dqStr.push_front(MyString("apple"));
		dqStr.insert(dqStr.begin() + 1, MyString("Charlie"));
		dqStr.push_back(MyString("Avocado"));
		dqStr.push_front(MyString("Delta"));

		pr(dqStr, "deque<MyString> before erase");

		for (deque<MyString>::iterator it = dqStr.begin(); it != dqStr.end(); )
		{
			if (it->GetString()[0] == 'A' || it->GetString()[0] == 'a') {
				it = dqStr.erase(it);
			}
			else {
				it = it + 1 ;
			}
		}

		pr(dqStr, "deque<MyString> after erase 'A'/'a'");
	}

	////////////////////////////////////////////////////////////////////////////////////
	//stack

		//Создайте стек таким образом, чтобы
		//а) элементы стека стали копиями элементов вектора
		//б) при выводе значений как вектора, так и стека порядок значений был одинаковым
	{
		vector<int> v = { 1, 2, 3, 4, 5 };
		pr(v, "vector for stack");

		stack<int> st;
		for (vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); it++) {
			st.push(*it);
		}

		PrintStack(st, "stack<int>");
	}

		//Сравнение и копирование стеков
		//а) создайте стек и любым способом задайте значения элементов
		//б) создайте новый стек таким образом, чтобы он стал копией первого
		//в) сравните стеки на равенство
		//г) модифицируйте любой из стеком любым образом (push, pop, top)
		//д) проверьте, какой из стеков больше (подумайте, какой смысл вкладывается в такое сравнение)
	{
		stack<int> s1;
		s1.push(1); s1.push(2); s1.push(3); // a)

		stack<int> s2 = s1;	// б)

		cout << "\n\ns1 == s2 : " << (s1 == s2 ? "true" : "false"); // c)

		s2.push(4);	// г)

		cout << "\ns1 == s2 after push(4) to s2 : " << (s1 == s2 ? "true" : "false"); // д)

		// Сравнение стека по величине сводится к лексикографическому сравнению
		// снизу вверх - т.е. сначала сравниваются самые нижние элементы, и стек считается больше, если он либо имеет
		// больший элемент на первом несовпадении, либо является продолжением другого.
		cout << "\ns1 < s2 : " << (s1 < s2 ? "true" : "false");
	}


	////////////////////////////////////////////////////////////////////////////////////
	//queue

	//Создайте очередь, которая содержит указатели на объекты типа Point,
	//при этом явно задайте базовый контейнер.
	//Измените значения первого и последнего элементов посредством front() и back()
	//Подумайте, что требуется сделать при уничтожении такой очереди?

	// Указатели в очереди ссылаются на локальные объекты p1, p2, p3; при
	// уничтожении такой очереди уничтожаются только сами указатели, а объекты,
	// на которые они указывают, продолжают существовать
	{
		Point p1(1, 1), p2(2, 2), p3(3, 3);

		queue<Point*, list<Point*>> q;

		q.push(&p1);
		q.push(&p2);
		q.push(&p3);

		*q.front() = Point(100, 100);
		*q.back() = Point(300, 300);

		PrintQueue(q, "queue<Point*> after front/back");
	}
	////////////////////////////////////////////////////////////////////////////////////
	//priority_queue
	//а) создайте очередь с приоритетами, которая будет хранить адреса строковых литералов - const char*
	//б) проинициализируйте очередь при создании с помощью вспомогательного массива с элементами const char*
	//в) проверьте "упорядоченность" значений (с помощью pop() ) - если они оказываются не упорядоченными, подумайте:
	//		что сравнивается при вставке?
	// 
	//  priority_queue<const char*> по умолчанию использует less<const char*>,
	// который сравнивает адреса строк, а не их содержимое, поэтому порядок при pop()
	// оказывается случайным (зависящим от расположения литералов в памяти), а не
	// алфавитным. Чтобы сравнивалось содержимое строк, нужен собственный компаратор на strcmp
	{
		const char* arr[] = { "banana", "apple", "date", "fig", "cherry" };

		priority_queue<const char*> pqDefault(arr, arr + 5);

		PrintPQueue(pqDefault, "priority_queue<const char*> default");

		priority_queue<const char*, vector<const char*>, CStrLess> pqFixed(arr, arr + 5);

		PrintPQueue(pqFixed, "priority_queue<const char*> compares content");
	}


	////////////////////////////////////////////////////////////////////////////////////
	//set
	//a) создайте множество с элементами типа Point - подумайте, что необходимо определить
	//		в классе Point (и каким образом)
	//б) распечатайте значения элементов с помощью шаблона, реализованного в предыдущей лаб. работе
	//в) попробуйте изменить любое значение...
	//г) Создайте два множества, которые будут содержать одинаковые значения
	//		типа int, но занесенные в разном порядке
	//д) Вставьте в любое множество диапазон элементов из любого другого
	//	контейнера, например, элементов массива	(что происходит, если в массиве имеются дубли?)
	{
		// а) В классе Point должен быть определён operator< - именно по нему set
		// строит внутреннее упорядоченное дерево и определяет уникальность элементов.
		set<Point> setPts = { Point(3,4), Point(1,1), Point(0,0), Point(2,2), Point(-5,-5) };

		// б)
		pr(setPts, "set<Point>");

		// в) Элементы set хранятся как const - изменить значение через итератор напрямую нельзя 
		Point old = *setPts.begin();
		setPts.erase(setPts.begin());
		setPts.insert(Point(old.X() + 1, old.Y() + 1));
		pr(setPts, "set<Point> after erase+insert");

		// г)
		set<int> setA = { 5, 3, 1, 4, 2 };
		set<int> setB = { 1, 2, 3, 4, 5 };
		cout << "\n\nsetA == setB (same values, different insertion order): " << (setA == setB ? "true" : "false");

		// д)
		int arrDup[] = { 10, 20, 20, 30, 10, 40 };
		set<int> setC;
		setC.insert(arrDup, arrDup + 6);
		// Дубликаты (10 и 20) при вставке молча отбрасываются - set хранит только уникальные значения, insert() для уже имеющегося значения просто ничего не делает
		pr(setC, "set<int> from array with duplicates");
	}


	////////////////////////////////////////////////////////////////////////////////////
	//multiset
	{
		int arrDup[] = { 10, 20, 20, 30, 10, 40 };
		multiset<int> ms;
		ms.insert(arrDup, arrDup + 6);

		// В отличие от set, multiset хранит все элементы, включая дубликаты
		pr(ms, "multiset<int> from array with duplicates");

		cout << "\n\nmultiset count(10) = " << ms.count(10);
		cout << "\nmultiset count(20) = " << ms.count(20);
	}


	////////////////////////////////////////////////////////////////////////////////////
	//map
	//а) создайте map, который хранит пары "фамилия, зарплата" - pair<const char*, int>,
	//	при этом строки задаются строковыми литералами
	//б) заполните контейнер значениями посредством operator[] и insert()
	//в) распечатайте содержимое

	//е) замените один из КЛЮЧЕЙ на новый (была "Иванова", вышла замуж => стала "Петрова")
	{
		map<const char*, int, CStrLess> salaries;

		
		salaries["Ivanova"] = 50000;			
		salaries["Sidorov"] = 45000;		
		salaries.insert(pair<const char*, int>("Petrov", 60000));		

		PrintMap(salaries, "map<surname, salary>");

		int val = salaries["Ivanova"];
		salaries.erase("Ivanova");
		salaries["Petrova"] = val;

		PrintMap(salaries, "map after Ivanova -> Petrova");
	}


	////////////////////////////////////////////////////////////////////////////////////
	//multimap
	//а) создайте "англо-русский" словарь, где одному и тому же ключу будут соответствовать
	//		несколько русских значений - pair<string,string>, например: strange: чужой, странный...
	//б) Заполните словарь парами с помощью метода insert или проинициализируйте с помощью
	//		вспомогательного массива пара (пары можно конструировать или создавать с помощью шаблона make_pair)
	//в) Выведите все содержимое словаря на экран
	//г) Выведите на экран только варианты "переводов" для заданного ключа. Подсказка: для нахождения диапазона
	//		итераторов можно использовать методы lower_bound() и upper_bound()
	{
		pair<string, string> arr[] =
		{
			pair<string,string>("strange", "чужой"),
			make_pair(string("strange"), string("странный")),
			make_pair(string("strange"), string("необычный")),
			make_pair(string("good"), string("хороший")),
			make_pair(string("good"), string("добрый"))
		};

		multimap<string, string> dict;
		dict.insert(arr, arr + 5);
		dict.insert(make_pair(string("good"), string("качественный")));

		
		PrintMap(dict, "multimap dictionary");

		
		string key = "good";
		multimap<string, string>::iterator l = dict.lower_bound(key);
		multimap<string, string>::iterator h = dict.upper_bound(key);

		cout << "\n\nTranslations for \"" << key << "\": ";
		for (multimap<string, string>::iterator it = l; it != h; ++it) {
			cout << it->second << "  ";
		}
	}


	///////////////////////////////////////////////////////////////////

	//Итераторы

	//Реверсивные итераторы. Сформируйте set<Point>. Подумайте, что
	//нужно перегрузить в классе Point. Создайте вектор, элементы которого
	//являются копиями элементов set, но упорядочены по убыванию

	set<Point> setForIter = { Point(1,1), Point(3,3), Point(0,0), Point(2,2), Point(-4,0) };

	{
		vector<Point> vDesc(setForIter.rbegin(), setForIter.rend());
		pr(vDesc, "vector<Point> from set, descending");
	}

	//Потоковые итераторы. С помощью ostream_iterator выведите содержимое
	//vector и set из предыдущего задания на экран.
	{
		vector<Point> vDesc(setForIter.rbegin(), setForIter.rend());

		cout << "\n\nvector via ostream_iterator:\n";
		copy(vDesc.begin(), vDesc.end(), ostream_iterator<Point>(cout, ", "));

		cout << "\n\nset via ostream_iterator:\n";
		copy(setForIter.begin(), setForIter.end(), ostream_iterator<Point>(cout, ", "));
	}


	//Итераторы вставки. С помощью возвращаемых функциями:
	//back_inserter()
	//front_inserter()
	//inserter()
	//итераторов вставки добавьте элементы в любой из созданных контейнеров. Подумайте:
	//какие из итераторов вставки можно использовать с каждым контейнером.
	{
		vector<int> src = { 1, 2, 3, 4 };

		// back_inserter - требует push_back(): подходит для vector, deque, list
		vector<int> destV;
		copy(src.begin(), src.end(), back_inserter(destV));
		pr(destV, "back_inserter -> vector");

		// front_inserter - требует push_front(): подходит для deque, list,
		deque<int> destD;
		copy(src.begin(), src.end(), front_inserter(destD));
		pr(destD, "front_inserter -> deque");

		// inserter - требует insert(iterator, value): универсален, подходит практически для любого контейнера
		set<int> destS;
		copy(src.begin(), src.end(), inserter(destS, destS.begin()));
		pr(destS, "inserter -> set");
	}



	///////////////////////////////////////////////////////////////////

		//Обобщенные алгоритмы (заголовочный файл <algorithm>). Предикаты.

		// алгоритм for_each() - вызов заданной функции для каждого элемента любой последовательности
		//(массив, vector, list...)
		//С помощью алгоритма for_each в любой последовательности с элементами любого типа
		//распечатайте значения элементов
		//Подсказка : неплохо вызываемую функцию определить как шаблон
	{
		int arr[] = { 1, 2, 3, 4, 5 };
		vector<double> vd = { 1.1, 2.2, 3.3 };
		list<string> ls = { "aa", "bb", "cc" };

		cout << "\n\nfor_each over int[]: ";
		for_each(arr, arr + 5, PrintElem<int>);

		cout << "\n\nfor_each over vector<double>: ";
		for_each(vd.begin(), vd.end(), PrintElem<double>);

		cout << "\n\nfor_each over list<string>: ";
		for_each(ls.begin(), ls.end(), PrintElem<string>);
	}


	//С помощью алгоритма for_each в любой последовательности с элементами типа Point
	//измените "координаты" на указанное значение (такой предикат тоже стоит реализовать
		//как шаблон) и выведите результат с помощью предыдущего предиката
		vector<Point> vPoints = { Point(1,1), Point(2,2), Point(3,3), Point(-1,4) };
	{
		cout << "\n\nvector<Point> before shift: ";
		for_each(vPoints.begin(), vPoints.end(), PrintElem<Point>);

		for_each(vPoints.begin(), vPoints.end(), ShiftPoint(10, -10));

		cout << "\n\nvector<Point> after shift(10,-10): ";
		for_each(vPoints.begin(), vPoints.end(), PrintElem<Point>);
	}


	//С помощью алгоритма find() найдите в любой последовательности элементов Point
	//все итераторы на элемент Point с указанным значением.
	{
		Point target(12, -8);	// это (2,2) после сдвига на (10,-10)

		cout << "\n\nfind() all occurrences of " << target << " in vPoints:";
		vector<Point>::iterator it = vPoints.begin();
		bool found = false;
		while ((it = find(it, vPoints.end(), target)) != vPoints.end())
		{
			cout << "\nfound at index " << (it - vPoints.begin()) << ": " << *it;
			found = true;
			++it;
		}
		if (!found)
			cout << "\nnot found";
	}


	//С помощью алгоритма sort() отсортируйте любую последовательность элементов Point.
	////По умолчанию алгоритм сортирует последовательность по возрастанию.
	//Что должно быть определено в классе Point?
	// Замечание: обобщенный алгоритм sort не работает со списком, так как
	//это было бы не эффективно => для списка сортировка реализована методом класса!!!
	{
		// В классе Point должен быть определён operator< (используется алгоритмом sort по умолчанию)
		sort(vPoints.begin(), vPoints.end());
		pr(vPoints, "vector<Point> after sort() (ascending by distance from origin)");
	}


	//Создайте глобальную функцию вида: bool Pred1_1(const Point& ), которая будет вызываться
	//алгоритмом find_if(), передавая в качестве параметра очередной элемент последовательности.
	//С помощью алгоритма find_if() найдите в любой последовательности элементов Point
	//итератор на элемент Point, удовлетворяющий условию: координаты x и y лежат в промежутке
	//[-n, +m].
	{
		vector<Point>::iterator it = find_if(vPoints.begin(), vPoints.end(), PointCoordsInRange(-10, 12));
		cout << "\n\nfind_if(PointCoordsInRange(-10,12)): ";
		if (it != vPoints.end())
			cout << *it;
		else
			cout << "not found";
	}


	//С помощью алгоритма sort() отсортируйте любую последовательность элементов Rect,
	//располагая прямоугольники по удалению центра от начала координат.
	{
		vector<Rect> vRects = { Rect(10,10,2,2), Rect(0,0,1,1), Rect(-3,-3,2,2), Rect(1,1,1,1) };

		pr(vRects, "vector<Rect> before sort");

		sort(vRects.begin(), vRects.end());	// использует Rect::operator<

		pr(vRects, "vector<Rect> after sort (by center distance from origin)");
	}


	{//transform
		//Напишите функцию, которая с помощью алгоритма transform переводит
		//содержимое объекта string в нижний регистр.
		//Подсказка: класс string - это "почти" контейнер, поэтому для него
		// определены методы begin() и end()
		string s = "Hello, World! Mixed CASE 123";
		string sLower = s;
		transform(sLower.begin(), sLower.end(), sLower.begin(), ToLowerChar());

		cout << "\n\nstring before: " << s;
		cout << "\nstring after transform to lower case: " << sLower;

		//Заполните list объектами string. С помощью алгоритма transform сформируте
		//значения "пустого" set, конвертируя строки в нижний регистр
		list<string> lst = { "Apple", "BANANA", "Cherry", "apple" };
		set<string> lowered;

		transform(lst.begin(), lst.end(), inserter(lowered, lowered.begin()), ToLowerStr);

		pr(lowered, "set<string> lower-cased ");
	}
	{// map

		//Сформируйте любым способом вектор с элементами типа string.
		//Создайте (и распечатайте для проверки) map<string, int>, который будет
		//содержать упорядоченные по алфавиту строки и
		//количество повторений каждой строки в векторе
		vector<string> words = { "cat", "dog", "cat", "bird", "dog", "cat", "ant" };

		pr(words, "words vector");

		map<string, int> wordCount;
		for (vector<string>::iterator it = words.begin(); it != words.end(); ++it)
			wordCount[*it]++;

		PrintMap(wordCount, "map<string,int> word counts");
	}



	cout << endl;

	return 0;
}
