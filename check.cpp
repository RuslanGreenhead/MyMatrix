#include "Matrix_utilities.h"
#include "Allocator_other.h" // другой алокатор, для проверки работы с другим (а не тем, что по умолчанию)

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <string>

class StrangeClass {
public:
	StrangeClass() { // дефолтный конструктор всегда кидает исключения
		throw std::runtime_error("StrangeClass() throwed exception!");
		++count; // до этого никогда не дойдёт
	}
	StrangeClass(double val) { 
		if (count == 2) // т.е. если это третий элемент, кидаем исключение...
			throw std::runtime_error("THIRED StrangeClass(double) throwed exception!");
		cout << "StrangeClass(double) get one parametr: " << val << endl;
		++count;
	}
	~StrangeClass() {
		cout << "~StrangeClass() destroyed element number: " << count << endl;
		--count;
	}
private:
	static size_t count;
};
size_t StrangeClass::count = 0;

void test_init() {
	cout << "-----------------------TEST_INIT-----------------------" << endl;
	Matrix<> m0; // пустая матрица (без какого-либо выделения памяти)
	cout << m0 << endl;

	Matrix<> m1(4); // матрица вида: 4 строки и 1 столбец (при заполнении использовались дефолтные конструкторы MyType())
	cout << m1 << endl; // m1 из double (т.к. по умолчанию)

	Matrix<int> m2(4, 6); // матрица вида: 4 строки и 6 столбцов (при заполнении использовались дефолтные конструкторы MyType()) 
	cout << m2 << endl;

	Matrix<int> m3(m2); // Конструктор копирования
	cout << m2 << endl;
	cout << m3 << endl;

	Matrix<> m4(m2); // Конструктор копирования шаблонный т.к. разные типы
	cout << m2 << endl;
	cout << m4 << endl;

	Matrix<int> m5(std::move(m2)); // Конструктор перемещения
	cout << m2 << endl;
	cout << m5 << endl;

	Matrix<> m6(std::move(m5)); // Конструктор копирования шаблонный т.к. разные типы
	cout << m5 << endl;
	cout << m6 << endl;

	Matrix<int> m7 = { {1, 2, 3}, {4, 5, 6} }; // initializer_list конструктор (тот же тип): матрица вида: 2 строки и 3 столбца 
	cout << m7 << endl;
	Matrix<int> m8 = { {1, 2, 3, 4, 5, 6} }; // initializer_list конструктор (тот же тип): матрица вида: 1 строка и 6 столбцов
	cout << m8 << endl;
	Matrix<char> m9 = { 1, 2, 3, 4, 5, 6 }; // initializer_list конструктор (другой тип): матрица вида: 6 строк и 1 столбец 
	cout << m9 << endl;
	Matrix<char> m10 = { {1}, {2}, {3}, {4}, {5}, {6} }; // initializer_list конструктор (другой тип): матрица вида: 6 строк и 1 столбец
	cout << m10 << endl;
	
	try { Matrix<int> m = { {1, 2, 3}, {4, 6}, {7, 8, 9} }; } // должен выкинуть исключение т.к. разное кол-во элементов в строках
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }

	try { Matrix<StrangeClass> m(4); } // должен выкинуть исключение т.к. дефолтный конструктор кидает исключения
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }

	try { Matrix<StrangeClass> m = { 11, 22, 33, 44 }; } // должен выкинуть исключение т.к. конструктор с 1 параметром его выкидывает при создании 3-го элемента
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }

	cout << "-------------------------------------------------------" << endl;
}

void test_assignment() {
	cout << "-----------------------TEST_ASSIGNMENT-----------------------" << endl;
	Matrix<> m_d = { {1.1, 2.1, 3.1}, {4.1, 5.1, 6.1}, {7.1, 8.1, 9.1} };
	cout << m_d << endl;
	Matrix<int> m1 = { 1, 2, 3, 4, 5, 6 };
	cout << m1 << endl;
	Matrix<int> m2; // пустая матрица
	cout << m2 << endl;

	m1 = m1; // сработала проверка на самоприсваивание

//	m2 = m1; // копирующее присваивание
	cout << m2 << endl;

	m2 = m_d; // копирующее присваивание шаблонное (т.к. типы разные)
	cout << m2 << endl;

	cout << m1 << endl; // вот каким m1 был
	cout << m2 << endl; // вот каким m2 был
	m2 = std::move(m1); // перемещающее приваивание (т.к. типы одинаковые)
	cout << m1 << endl; // теперь m1 поменялся m2
	cout << m2 << endl; // а вот каким m2 стал

	cout << m_d << endl; // вот каким m_d был
	cout << m2 << endl;  // вот каким m2 был
	m2 = std::move(m_d); // копирующее приваивание шаблонное (т.к. типы разные)
	cout << m_d << endl; // m_d не поменялся
	cout << m2 << endl;  // а вот каким m2 стал

	m2 += m_d; // разные типы, поэтому сужение при поэлементном +=
	cout << m2 << endl;
	m2 -= m_d; // разные типы, поэтому сужение при поэлементном -=
	cout << m2 << endl;
	m2 *= Matrix<double>{0, 1, 0}; // разные типы, поэтому сужение при поэлементных операциях
	cout << m2 << endl;
	m2 *= 2.5; // разные типы, поэтому сужение при поэлементном *=
	cout << m2 << endl; // не поменяется т.к. *static_cast<int>(1.5)
	m_d *= 0;
	cout << m_d << endl; // должна обнулиться

	try { m_d += Matrix<int>{1, 2, 3, 4}; }
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }

	try { m_d -= Matrix<int>{1, 2, 3, 4}; }
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }
	cout << "-------------------------------------------------------" << endl;
}

void test_ij() {
	cout << "------------------------TEST_IJ------------------------" << endl;
	try { cout << Matrix<>{}(0, 0) << endl; } // пустая
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }

	try { cout << Matrix<>(5)(0, 1) << endl; } // 1 столбец
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }

	try { cout << Matrix<>(1, 5)(1, 0) << endl;} // 1 строка
	catch (std::exception& ex) { cerr << ex.what() << endl << endl; }

	Matrix<int> m = { {1, 2, 3}, {4, 5, 6} };
	cout << m << endl;
	cout << m(0, 2) << endl;
	m(0, 2) = 7; // теперь 1-ая строка, 3-ий элемент стал равен 7
	cout << m(0, 2) << endl;
	cout << m << endl;

	const Matrix<int> c_m = { {1, 2, 3}, {4, 5, 6} };
	cout << c_m << endl;
	cout << c_m(0, 2) << endl;
	//c_m(0, 2) = 7; // не должно скомпилироваться (ведь нельзя менять элементы константной матрицы)

	cout << "-------------------------------------------------------" << endl;
}

void test_cout() {
	cout << "-----------------------TEST_COUT-----------------------" << endl;
	Matrix<const char*> m{ {"This", "is", "my"}, {"best", "matrix", "ever"}};
	cout << m << endl;
	Matrix<std::string> m_str = m;
	cout << m_str << endl;
	m_str += Matrix<const char*>{ {"111", "22", "3"}, {"4", "55", "666"} };
	cout << m_str << endl;
	cout << "-------------------------------------------------------" << endl;
}

void test_arithmetic() {
	cout << "--------------------TEST_ARITHMETIC--------------------" << endl;
	Matrix<int> m_i = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	cout << m_i << endl;
	Matrix<double> m_d = { {1.2, 2.1, 3.5}, {4.4, 5.5, 6.1}, {7.5, 8.0, 9.1} };
	cout << m_d << endl;

	cout << "SUM unary:" << endl;
	cout << +m_i << endl;

	cout << "MINUS unary:" << endl;
	cout << -m_i << endl;

	cout << "SUM binary:" << endl;
	cout << m_i + m_d << endl;

	cout << "MINUS binary:" << endl;
	cout << m_i - m_d << endl;

	cout << "MULTIPLY by matrix:" << endl;
	cout << m_i * m_d << endl;

	cout << "MULTIPLY by value (left):" << endl;
	cout << 4 * m_d << endl;
	cout << "MULTIPLY by value (right):" << endl;
	cout << m_i * 1.5 << endl;

	try { Matrix<int>{ {1, 2}, { 4, 5 } } + m_d; }
	catch (std::exception& ex) { cerr << ex.what() << endl; }

	try { Matrix<int>{ {1, 2}, { 4, 5 } } - m_d; }
	catch (std::exception& ex) { cerr << ex.what() << endl; }

	try { Matrix<int>{ {1, 2}, { 4, 5 } } * m_d; }
	catch (std::exception& ex) { cerr << ex.what() << endl; }

	cout << "-------------------------------------------------------" << endl;
}

void test_capacity() {
	cout << "------------------_--TEST_CAPACITY-----------_---------" << endl;
	Matrix<int> m = { {1, 2}, {3 , 4}, {5, 6} };
	cout << m;
	cout << "capacity: " << m.capacity() << endl << endl;

	Matrix<int> m_1 = { {1, 2,   3},{4,   5, 6} };
  	m = m_1; // перевыделять память не пришлось
	cout << m;
	cout << "capacity: " << m.capacity() << endl << endl;

	Matrix<double> m_2 = { {1, 2}, {3 , 4}};
	m = m_2; // перевыделять память не пришлось
	cout << m;
	cout << "capacity: " << m.capacity() << endl << endl;

	Matrix<double> m_3 = { {1, 2}, {3 , 4}, {5, 6}, {7 , 8} };
	m = m_3; // вот теперь пришлось перевыделить память
	cout << m;
	cout << "capacity: " << m.capacity() << endl << endl;

	cout << "-------------------------------------------------------" << endl;
}

void test_alloc() {
	cout << "----------------------TEST_ALLOC-----------------------" << endl;
	Matrix<double> matrix1 = { {1, 2}, {4, 5} };
	Matrix<int, Allocator_other<int>> matrix2 = { {1, 2}, {4, 5} };
	cout << matrix1 + matrix2 << endl; // Удаётся сложить две матрицы с разными алокаторами
	matrix2 = matrix1; // Удаётся присвоить матрицу с другим алокатором
	cout << matrix2 << endl;
	cout << "-------------------------------------------------------" << endl;
}