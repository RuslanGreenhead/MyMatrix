//
// Matrix class declaration
//

#pragma once

#include<iostream>
#include"Allocator.h"

namespace linalg {
    template<typename T=double, typename Alloc=Allocator<T>>
    class Matrix {
    public:
        template<typename Other, typename Alloc_Other> friend class Matrix;        // Declaring other instantiations as friends

        explicit Matrix() noexcept = default;                                      // Default constructor
        explicit Matrix(size_t rows, size_t columns = 1, Alloc alloc = Alloc());   // Constructor with parameters
        Matrix(const Matrix &object);                                              // Copy constructor
        Matrix(Matrix &&object) noexcept;                                          // Move constructor
        ~Matrix() noexcept;                                                        // Destructor

        template<typename Other>
        Matrix(std::initializer_list<Other> init_list, Alloc alloc = Alloc());     // Initializing vector (single column matrix)

        template<typename Other>
        Matrix(std::initializer_list<std::initializer_list<Other>> init_list, Alloc alloc = Alloc());  // Init_list of Init_lists

        template<typename Other, typename Alloc_Other>
        Matrix(const Matrix<Other, Alloc_Other> &object);                          // Copy constructor (from another type)

        Matrix &operator=(const Matrix &object);                                   // Copy assignment
        Matrix &operator=(Matrix &&object) noexcept;                               // Move assignment

        template<typename Other, typename Alloc_Other>
        Matrix &operator=(const Matrix<Other, Alloc_Other> &object);               // Copy assignment (from another type)

        // Arithmetical assignment operators
        template<typename Other, typename Alloc_Other>
        Matrix &operator+=(const Matrix<Other, Alloc_Other> &object);

        template<typename Other, typename Alloc_Other>
        Matrix &operator-=(const Matrix<Other, Alloc_Other> &object);

        template<typename Other>
        Matrix &operator*=(const Other &value);

        template<typename Other, typename Alloc_Other>
        Matrix &operator*=(const Matrix<Other, Alloc_Other> &object);

        // Унарные операторы сложения и вычитания:
        Matrix &operator+() { return *this; }

        Matrix operator-() { return Matrix(*this) *= -1; }

        // Getter and setter
        size_t get_columns() const noexcept { return m_columns; }
        size_t get_rows() const noexcept { return m_rows; }

        // Size and capacity
        size_t size() const noexcept { return m_columns * m_rows; }   // Actual number of elements in matrix
        size_t capacity() const noexcept { return m_capacity; }       // Allocated memory in use

        // Indexing (func-like)
        T &operator()(size_t row, size_t column);
        const T &operator()(size_t row, size_t column) const;

        // Logical operators
        template<typename T1, typename Alloc_1, typename T2, typename Alloc_2>
        bool friend operator==(const Matrix<T1, Alloc_1> &mat, const Matrix<T2, Alloc_2> &ve);

        // -------------------------------Linear algebra methods and funcs-------------------------------

        T det() const;                                  // Determinant (1st column decomposition)
        Matrix minor(int row, int column) const;        // Minor for an element
        int rank() const;                               // Rank (reducing to the upper triangular form)
        double norm() const;                            // Frobenius norm
        double trace() const;                           // Trace

        // Transposing the matrix
        template<typename T1, typename Alloc_1>
        Matrix<T1, Alloc_1> friend transpose(const Matrix<T1, Alloc_1> &obj);

        // Finding an inverse matrix
        template<typename T1, typename Alloc_1>
        auto friend inv(const Matrix<T1, Alloc_1> &obj);

        // Matrix to power
        template<typename T1, typename Alloc_1>
        Matrix<T1, Alloc_1> friend pow(const Matrix<T1, Alloc_1> &obj, size_t number);

        // Solving linear-system
        template<typename T1, typename Alloc_1, typename T2, typename Alloc_2>
        auto friend solve(const Matrix<T1, Alloc_1> &mat, const Matrix<T2, Alloc_2> &vec);

        //Getters
        size_t num_cols() {return m_columns;}
        size_t num_rows() {return m_rows;}

    private:
        T *m_ptr = nullptr;                     // Pointer to data
        size_t m_rows = 0, m_columns = 0;       // Number of rows and columns
        size_t m_capacity = 0;                  // Capacity (allocated memory)
        Alloc m_alloc = {};                     // Allocator instance (memory-funcs toolkit)
    };
}
#include "Matrix.hpp"
#include "Matrix_utilites.hpp"
#include "Matrix_utilites_additional.hpp"