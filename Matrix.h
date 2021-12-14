#pragma once

#include<iostream>
#include"Allocator.h"

template<typename T = double, typename Alloc=Allocator<T>>
class Matrix {
public:
	template<typename Other, typename Alloc_Other> friend class Matrix; // Подружились с такими матрицами, чтобы пользоваться их внутренностями

	// Дефолтный конструктор
	explicit Matrix() noexcept {}

	// Конструктор с 2 параметрами (матрица) c 1 параметром (вектор)
	explicit Matrix(const size_t rows, const size_t columns = 1, Alloc alloc = Alloc()); 

	// Инициализировать вектор (вертикальный столбец)
	template<typename Other> 
	Matrix(std::initializer_list<Other> init_list, Alloc alloc = Alloc());

	// Инициализировать матрицу initializer_list сосотящий из initializer_list
	template<typename Other> 
	Matrix(std::initializer_list<std::initializer_list<Other>> init_list, Alloc alloc = Alloc());

	// Конструктор копирования
	Matrix(const Matrix& object);

	// Конструктор копирования от матрицы другого типа
	template<typename Other, typename Alloc_Other> 
	Matrix(const Matrix<Other, Alloc_Other>& object);

	// Перемещающий конструктор
	Matrix(Matrix&& object) noexcept; 

	// Деструктор
	~Matrix() noexcept; 

	// Оператор присваивания копирующий
	Matrix& operator = (const Matrix& object);	

	// Оператор присваивания копирующий от матрицы другого типа
	template<typename Other, typename Alloc_Other>
	Matrix& operator = (const Matrix<Other, Alloc_Other>& object);

	// Оператор присваивания перемещающий
	Matrix& operator = (Matrix&& object) noexcept;	
	
	// Оператор присваивающего суммирования c матрицей другого типа
	template<typename Other, typename Alloc_Other>  
	Matrix& operator += (const Matrix<Other, Alloc_Other>& object);

	// Оператор присваивающего вычитания c матрицей другого типа
	template<typename Other, typename Alloc_Other>  
	Matrix& operator -= (const Matrix<Other, Alloc_Other>& object);

	// Оператор присваивающего умножения на число другого типа
	template<typename Other>  
	Matrix& operator *= (const Other& value);

	// Оператор присваивающего умножения на матрицу другого типа
	template<typename Other, typename Alloc_Other>
	Matrix& operator *= (const Matrix<Other, Alloc_Other>& object);

	// Унарные операторы сложения и вычитания:
	Matrix& operator + () { return *this; }
	Matrix operator - () { return Matrix(*this) *= -1; }
	
	size_t get_columns() const noexcept { return m_columns; }
	size_t get_rows() const noexcept { return m_rows; }
	size_t size() const noexcept { return m_columns * m_rows; } // актуальное количество элементов матрицы
	size_t capacity() const noexcept { return m_capacity; } // вместимость матрицы

	T& operator() (size_t row, size_t column); // оператор вызова функции (принимает два аргумента будто [i][j])
	const T& operator() (size_t row, size_t column) const; // оператор вызова функции для константной матрицы

    T det()const;

    Matrix minor(const int i, const int k) const;

    int rank() const;

    double norm() const;

    double  trace () const;

    template <typename T1, typename Alloc_1>
    Matrix<T1, Alloc_1> friend transpose (const Matrix<T1, Alloc_1> &obj);

    template <typename T1, typename Alloc_1>
    auto  friend inv (const Matrix<T1, Alloc_1> &obj);

    template <typename T1, typename Alloc_1>
    Matrix<T1, Alloc_1>  friend pow (const Matrix<T1, Alloc_1> &obj,  size_t number );

private:
	T* m_ptr = nullptr;
	size_t m_rows = 0, m_columns = 0;
	size_t m_capacity = 0;
	Alloc m_alloc = {};
};

#include "Matrix.hpp" // там находятся все реализации
#include "Matrix_utilites.hpp"
#include "Matrix_utilites_additional.hpp"