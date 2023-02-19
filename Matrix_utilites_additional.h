//
// Matrix additional utilities declarations
//

#pragma once

#include "Matrix.h"
#include "Matrix_utilities.h"

namespace linalg {

template <typename T1, typename Alloc>
linalg::Matrix<T1, Alloc> transpose(const Matrix<T1, Alloc> &obj);

template <typename T1, typename Alloc_1>
auto inv(const Matrix<T1, Alloc_1> &obj);

template <typename T, typename Alloc>
Matrix<T, Alloc>  pow(const Matrix<T, Alloc> &obj,  size_t number);

template <typename T1, typename Alloc_1, typename T2, typename Alloc_2>
auto  solve(const Matrix<T1, Alloc_1> &mat,  const Matrix<T2, Alloc_2> &vec);

template <typename T1, typename Alloc_1, typename T2, typename Alloc_2>
bool operator == (const Matrix<T1, Alloc_1> &right,  const Matrix<T2, Alloc_2> &left);


//Euclid norm
template<typename T, typename Alloc>
double norm(const Matrix<T, Alloc>& obj);

//Scalar multiplication
template<typename T1, typename A1, typename T2,  typename A2>
double multy_scalar(const Matrix<T1, A1>& obj1, const Matrix<T2, A2>& obj2);

//Angle between vectors
template<typename T1, typename A1, typename T2, typename A2>
double angle(const Matrix<T1, A1>& obj1, const Matrix<T2, A2>& obj2);

//Vector multiplication
template<typename T1, typename A1, typename T2, typename A2>
auto multy_vector(const Matrix<T1, A1>& obj1, const Matrix<T2, A2>& obj2)->Matrix<decltype(T1()* T2())>;
#include "Matrix_utilites.hpp" // там находятся все реализации

//Making a unit vector
template<typename T, typename Alloc>
auto unit(const Matrix<T, Alloc>& obj)->Matrix<decltype(T() * double())>;

}

#include "Matrix_utilites_additional.hpp"