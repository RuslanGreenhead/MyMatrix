//
// Matrix utilities implementations
//

#pragma once

#include <iomanip> // input-output functionality
#include <sstream> // operating strings by stream methods

const int g_interval = 2;  // Number of gaps between symbols

template <typename T, typename Alloc>
size_t el_size_first(const Matrix<T, Alloc>& object) {
	std::stringstream ioss;
	size_t size = 0;
	for (size_t row = 0; row < object.get_rows(); ++row) {
		ioss << object(row, 0);
		size = std::max(size, ioss.str().size());
		ioss.str("");
	}
	return size;
}

template <typename T, typename Alloc>
size_t el_size_else(const Matrix<T, Alloc>& object) {
	std::stringstream ioss;
	size_t size = 0;
	for (size_t row = 0; row < object.get_rows(); ++row) {
		for (size_t column = 1; column < object.get_columns(); ++column) {
			ioss << object(row, column);
			size = std::max(size, ioss.str().size());
			ioss.str("");
		}
	}
	return size;
}

template <typename T, typename Alloc>
std::ostream& operator << (std::ostream& out, const Matrix<T, Alloc>& object) {
	if (object.get_rows() == 0) return out << "|empty|\n";
	size_t size_first = el_size_first(object);
	size_t size_else  = el_size_else(object) + g_interval;
	for (size_t row = 0; row < object.get_rows(); ++row) {
		out << '|';
		for (size_t column = 0; column < object.get_columns(); ++column) {
			out << std::right;
			if (column == 0)	out << std::setw(size_first);
			else				out << std::setw(size_else);
			out << object(row, column);
		}
		out << "|\n";
	}
    out << "\n";
	return out;
}

template<typename T1, typename A1, typename T2, typename A2>
auto operator + (const Matrix<T1, A1>& obj1, const Matrix<T2, A2>& obj2) -> Matrix<decltype(T1() + T2())>{
	if (obj1.get_rows() != obj2.get_rows() || obj1.get_columns() != obj2.get_columns())
		throw std::runtime_error("Error: different shapes for operator +!");
	Matrix<decltype(T1() + T2())> obj_new(obj1);
	obj_new += obj2;
	return obj_new;
}

template<typename T1, typename A1, typename T2, typename A2>
auto operator-(const Matrix<T1, A1>& obj1, const Matrix<T2, A2>& obj2) -> Matrix<decltype(T1() - T2())> {
	if (obj1.get_rows() != obj2.get_rows() || obj1.get_columns() != obj2.get_columns())
		throw std::runtime_error("Error: different shapes for operator -!");
	Matrix<decltype(T1() - T2())> obj_new(obj1);
	obj_new -= obj2;
	return obj_new;
}

template<typename T1, typename A1, typename T2, typename A2>
auto operator * (const Matrix<T1, A1>& obj1, const Matrix<T2, A2>& obj2) -> Matrix<decltype(T1()* T2() + T1() * T2())> {
	if (obj1.get_columns() != obj2.get_rows())
		throw std::runtime_error("Error: bad shapes for operator *!");
	Matrix<decltype(T1() * T2() + T1() * T2())> obj_new(obj1.get_rows(), obj2.get_columns());
	for (size_t col = 0; col < obj2.get_columns(); ++col) {
		for (size_t row = 0; row < obj1.get_rows(); ++row) {
			for (size_t term = 0; term < obj1.get_columns(); ++term){
				obj_new(row, col) += obj1(row, term) * obj2(term, col);
			}
		}
	}
	return obj_new;
}

template<typename T, typename Alloc, typename Other>
inline auto operator * (const Other& value, const Matrix<T, Alloc>& obj) -> Matrix<decltype(T()* Other())>{
	Matrix<decltype(T()* Other())> obj_new(obj);
	return obj_new *= value;
}

template<typename T, typename Alloc, typename Other>
inline auto operator * (const Matrix<T, Alloc>& obj, const Other& value)->Matrix<decltype(T()* Other())> {
	Matrix<decltype(T()* Other())> obj_new(obj);
	return obj_new *= value;
}