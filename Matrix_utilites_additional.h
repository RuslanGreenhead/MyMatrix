
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

// решает СЛАУ, где коэф-фы заданы матрицей mat
// столбец свободных членов - vec
template <typename T1, typename Alloc_1, typename T2, typename Alloc_2>
auto  solve (const Matrix<T1, Alloc_1> &mat,  const Matrix<T2, Alloc_2> &vec);

// сравнивает матрицы поэлементно, если они равного размера
template <typename T1, typename Alloc_1, typename T2, typename Alloc_2>
bool operator==(const Matrix<T1, Alloc_1> &right,  const Matrix<T2, Alloc_2> &left);


//Евклидова норма
template<typename T, typename Alloc>
double norm(const Matrix<T, Alloc>& obj);

//Скалярное произведение
template<typename T1, typename A1, typename T2,  typename A2>
double multy_scalar(const Matrix<T1, A1>& obj1, const Matrix<T2, A2>& obj2);

//Нахождение угола между векторами
template<typename T1, typename A1, typename T2, typename A2>
double angle(const Matrix<T1, A1>& obj1, const Matrix<T2, A2>& obj2);

//Векторное произведение
template<typename T1, typename A1, typename T2, typename A2>
auto multy_vector(const Matrix<T1, A1>& obj1, const Matrix<T2, A2>& obj2)->Matrix<decltype(T1()* T2())>;

//Вектор единичный
template<typename T, typename Alloc>
auto unit(const Matrix<T, Alloc>& obj)->Matrix<decltype(T() * double())>;
#include "Matrix_utilites_additional.hpp"