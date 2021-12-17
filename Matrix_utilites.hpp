#pragma once

#include <iomanip> // input output manipulations
#include <sstream> // чтобы работать со строками через интерфейс потоков


const int g_interval = 2; // кол-во пробелов между элементами

// смотрит из каких символов состоит каждый элемент первого столбца матрицы при выводе в поток и возвращает наибольшее кол-во символов.
template <typename T, typename Alloc>
size_t el_size_first(const Matrix<T, Alloc>& object) {
	std::stringstream ioss; // поток для одновременной работы с вводом и выводом
	size_t size = 0; // сюда будем класть размер строки (т.е. кол-во символов)
	for (size_t row = 0; row < object.get_rows(); ++row) {
		ioss << object(row, 0); // отправил элемент в поток
		size = std::max(size, ioss.str().size()); // считал в строку всё, что есть буфере потока (получилась строка) и взял её размер (size())
		ioss.str(""); // перезаписали в буфер потока пустую строку
	}
	return size;
}

// смотрит из каких символов состоит каждый элемент второго+ столбцов матрицы при выводе в поток и возвращает наибольшее кол-во символов.
template <typename T, typename Alloc>
size_t el_size_else(const Matrix<T, Alloc>& object) {
	std::stringstream ioss; // поток для одновременной работы с вводом и выводом
	size_t size = 0; // сюда будем класть размер строки (т.е. кол-во символов)
	for (size_t row = 0; row < object.get_rows(); ++row) {
		for (size_t column = 1; column < object.get_columns(); ++column) {
			ioss << object(row, column); // отправил элемент в поток
			size = std::max(size, ioss.str().size()); // считал в строку всё, что есть буфере потока (получилась строка) и взял её размер (size())
			ioss.str(""); // перезаписали в буфер потока пустую строку
		}
	}
	return size;
}

//----------------------------------------------------------------------------------
// Операторы:

// Оператор вывода в поток:
template <typename T, typename Alloc>
std::ostream& operator << (std::ostream& out, const Matrix<T, Alloc>& object) {
	if (object.get_rows() == 0) return out << "|empty|\n";
	size_t size_first = el_size_first(object); // количество символов для заполнения одного элемента в первом столбце
	size_t size_else  = el_size_else(object) + g_interval; // количество символов для заполнения одного элемента в остальных столбцах
	for (size_t row = 0; row < object.get_rows(); ++row) {
		out << '|';
		for (size_t column = 0; column < object.get_columns(); ++column) { // остальные с отступом
			out << std::right;
			if (column == 0)	out << std::setw(size_first);
			else				out << std::setw(size_else);
			out << object(row, column);
		}
		out << "|\n";
		//if (row != object.get_rows() - 1) out << '\n'; // если строка не последняя, сделай отступ
	}
    out << "\n";
	return out;
}

// Оператор суммирования двух матриц (разных типов)
template<typename T1, typename A1, typename T2, typename A2>
auto operator+(const Matrix<T1, A1>& obj1, const Matrix<T2, A2>& obj2)->Matrix<decltype(T1() + T2())> {
	if (obj1.get_rows() != obj2.get_rows() || obj1.get_columns() != obj2.get_columns())
		throw std::runtime_error("Error: different shapes for operator +!");
	Matrix<decltype(T1() + T2())> obj_new(obj1);
	obj_new += obj2;
	return obj_new;
}


// Оператор разности двух матриц (разных типов)
template<typename T1, typename A1, typename T2, typename A2>
auto operator-(const Matrix<T1, A1>& obj1, const Matrix<T2, A2>& obj2) -> Matrix<decltype(T1() - T2())> {
	if (obj1.get_rows() != obj2.get_rows() || obj1.get_columns() != obj2.get_columns())
		throw std::runtime_error("Error: different shapes for operator -!");
	Matrix<decltype(T1() - T2())> obj_new(obj1);
	obj_new -= obj2;
	return obj_new;
}


// Оператор перемножения двух матриц (разных типов)
template<typename T1, typename A1, typename T2, typename A2>
auto operator*(const Matrix<T1, A1>& obj1, const Matrix<T2, A2>& obj2) -> Matrix<decltype(T1()* T2() + T1() * T2())> {
	if (obj1.get_columns() != obj2.get_rows())
		throw std::runtime_error("Error: bad shapes for operator *!");
	Matrix<decltype(T1()* T2() + T1() * T2())> obj_new(obj1.get_rows(), obj2.get_columns()); // пустая матрица, т.е. элементы которой построены с помощью дефолтных конструкторов
	for (size_t col = 0; col < obj2.get_columns(); ++col) {
		for (size_t row = 0; row < obj1.get_rows(); ++row) {
			for (size_t term = 0; term < obj1.get_columns(); ++term) {
				obj_new(row, col) += obj1(row, term) * obj2(term, col);
			}
		}
	}
	// Matrix<decltype(T1()* T2() + T1() * T2())> obj_new(obj1);	// так тоже сработает, но зачем лишний раз создавать дубликат левой матрицы
	// obj_new *= obj2;												// если *= всё равно перевыделит память => дубликат сотрётся
	return obj_new;
}


// Оператор перемножения числа на матрицу (разных типов)
template<typename T, typename Alloc, typename Other>
inline auto operator*(const Other& value, const Matrix<T, Alloc>& obj)->Matrix<decltype(T()* Other())> {
	Matrix<decltype(T()* Other())> obj_new(obj);
	return obj_new *= value;
}


// Оператор перемножения матрицы на число (разных типов)
template<typename T, typename Alloc, typename Other>
inline auto operator*(const Matrix<T, Alloc>& obj, const Other& value)->Matrix<decltype(T()* Other())> {
	Matrix<decltype(T()* Other())> obj_new(obj);
	return obj_new *= value;
}