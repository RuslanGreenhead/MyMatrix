//
// Matrix utilities declarations
//

#pragma once

#include "Matrix.h"
using namespace linalg;

template<typename T, typename Alloc>
std::ostream& operator << (std::ostream &out, const Matrix<T, Alloc> &object);

template<typename T1, typename A1, typename T2, typename A2>
auto operator + (const Matrix<T1, A1> &obj1, const Matrix<T2, A2> &obj2) -> Matrix<decltype(T1() + T2())>;

template<typename T1, typename A1, typename T2, typename A2>
auto operator - (const Matrix<T1, A1> &obj1, const Matrix<T2, A2> &obj2) -> Matrix<decltype(T1() - T2())>;

template<typename T1, typename A1, typename T2, typename A2>
auto operator * (const Matrix<T1, A1> &obj1, const Matrix<T2, A2> &obj2) -> Matrix<decltype(T1() * T2() + T1() * T2())>;

template<typename T, typename Alloc, typename Other>
auto operator * (const Other &value, const Matrix<T, Alloc> &obj) -> Matrix<decltype(T() * Other())>;

template<typename T, typename Alloc, typename Other>
auto operator * (const Matrix<T, Alloc> &obj, const Other &value) -> Matrix<decltype(T() * Other())>;

#include "Matrix_utilites.hpp"