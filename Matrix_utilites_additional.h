
#pragma once

#include "Matrix.h"
#include "Matrix_utilities.h"

// ещё есть методы их смотри в Matrix.h после черты

// создаёт транспанированную матрицу
template <typename T1, typename Alloc>
Matrix<T1, Alloc> transpose(const Matrix<T1, Alloc> &obj);

// создаёт обратную матрицу
// если Det != 0
template <typename T1, typename Alloc_1>
auto inv(const Matrix<T1, Alloc_1> &obj);

// возводит в степень
// в любую степень можно только квадр матрицу, ибо правила умножения
template <typename T, typename Alloc>
Matrix<T, Alloc>  pow (const Matrix<T, Alloc> &obj,  size_t number);

#include "Matrix_utilites_additional.hpp"