#pragma once

#include <cmath>
#include <limits>
#include "LinAlgError.h"

using std::runtime_error;
using namespace linalg;

namespace linalg {
    template<typename T, typename Alloc>
    T Matrix<T, Alloc>::det() const {
        if (m_rows != m_columns) throw LinAlgError("Is not a square matrix, cannot find Det", 10);

        if ((m_columns == 2) && (m_rows == 2)) {
            return (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);
        }

        T determinant = 0;

        for (int i = 0; i < m_rows; i++) {
            determinant += pow(-1, i) * (*this)(i, 0) * (*this).minor(i, 0).det();
        };


        return determinant;
    }

    template<typename T, typename Alloc>
    Matrix<T, Alloc> Matrix<T, Alloc>::minor(const int row, const int column) const {

        if (m_rows <= row) throw LinAlgError("Wrong row of element for taking minor ", 11);
        if (m_columns <= column) throw LinAlgError("Wrong column of element for taking minor ", 12);

        Matrix<T> result(m_columns - 1, m_rows - 1);

        int index_i = 0, index_k;

        for (int i = 0; i < result.m_rows; i++) {
            for (int k = 0; k < result.m_columns; k++) {

                if (i >= row) index_i = 1;
                else index_i = 0;

                if (k >= column) index_k = 1;
                else index_k = 0;


                (*this)(index_i, index_k);
                result(i, k);
                result(i, k) = (*this)(i + index_i, k + index_k);

                ++index_i;
                ++index_k;
            }
        }


        return result;
    }

    template<typename T, typename Alloc>
    int Matrix<T, Alloc>::rank() const {
        Matrix<decltype(T() + double())> temp((*this));
        T result = 0;

        for (int i = 0; i < temp.m_rows; i++) {


            for (int k = 0; k < temp.m_columns; k++) {
                try {
                    if ((*this)(i, i) == 0) throw std::runtime_error("O");
                    temp(i, k) = temp(i, k) / (*this)(i, i);
                }
                catch (runtime_error err) {
                    for (int h = i; h < temp.m_columns; h++) {
                        if (temp(i, h) != 0) {
                            for (int m = i; m < temp.m_rows; m++) {
                                T cell_temp;
                                cell_temp = temp(m, h);
                                temp(m, h) = temp(m, i);
                                temp(m, i) = cell_temp;
                            }
                        } else { continue; }
                    }
                }
            }


            for (int k = i; k < temp.m_rows; k++) {
                for (int j = i; j < temp.m_rows; j++) {
                    if ((i != k) && (i != 100)) temp(k, j) = temp(k, j) - temp(i, j) * temp(k, i);
                }
            }
        }

        for (int i = 0; i < temp.m_rows; i++) {
            if (temp(i, i) != 0) ++result;
        }

        return result;
    }

    template<typename T, typename Alloc>
    double Matrix<T, Alloc>::norm() const {
        double result = 0;

        for (int i = 0; i < m_rows; i++) {
            for (int k = 0; k < m_columns; k++) {
                result += (*this)(i, k) * (*this)(i, k);
            }
        }


        return pow(result, 0.5);
    }

    template<typename T1, typename Alloc>
    double Matrix<T1, Alloc>::trace() const {
        if (m_rows != m_columns) throw LinAlgError("Is not a square matrix, cannot find Trace", 11);

        double result;
        for (int i = 0; i < (*this).m_rows; i++) {
            result += (*this)(i, i);
        }
        return result;
    }

    template<typename T1, typename Alloc>
    Matrix<T1, Alloc> transpose(const Matrix<T1, Alloc> &obj) {
        Matrix<T1> result(obj.m_columns, obj.m_rows);

        for (int i = 0; i < obj.m_rows; i++) {
            for (int k = 0; k < obj.m_columns; k++) {
                result(i, k) += obj(k, i);
            }
        }

        return result;
    }

    template<typename T1, typename Alloc_1>
    auto inv(const Matrix<T1, Alloc_1> &obj) {

        if (obj.m_rows != obj.m_columns) throw LinAlgError("Is not a square matrix, cannot find inv matrix", 12);
        double determ = obj.det();
        if (determ == 0) throw LinAlgError("Det = 0, There is no inv matrix", 13);

        Matrix<decltype(double() + T1())> result(obj);

        for (int i = 0; i < obj.m_rows; ++i) {
            for (int k = 0; k < obj.m_columns; ++k) {
                result(i, k) = pow(-1, i + k) * transpose(obj).minor(i, k).det() / determ;
            }
        }

        return result;
    }

    template<typename T, typename Alloc>
    Matrix<T, Alloc> pow(const Matrix<T, Alloc> &obj, size_t number) {
        Matrix<T> result(obj);

        for (size_t i = 0; i < number - 1; i++) {
            result *= obj;
        }
        return result;
    }

    template<typename T1, typename Alloc_1, typename T2, typename Alloc_2>
    auto solve(const Matrix<T1, Alloc_1> &mat, const Matrix<T2, Alloc_2> &vec) {

        if (vec.get_columns() != 1) throw LinAlgError("It's not a vector, cannot resolve equalization", 14);
        if (vec.m_rows != mat.m_rows) throw LinAlgError("Different row amounts, cannot resolve equalization", 15);
        if (mat.m_rows != mat.m_columns)
            throw LinAlgError("Not square matrix provides not normal system, cannot resolve equalization", 16);
        double determ = mat.det();
        if (determ == 0) throw LinAlgError("Det = 0, cannot resolve equalization", 17);


        Matrix<> temp(mat);
        Matrix<> result(mat.m_columns, 1);

        for (int i = 0; i < mat.m_columns; ++i) {
            for (int j = 0; j < mat.m_rows; ++j) { temp(i, j) = vec(i, j); }
            result(i, 1) = temp.det() / determ;
        }
        return result;
    }


    template<typename T1, typename Alloc_1, typename T2, typename Alloc_2>
    bool operator==(const Matrix<T1, Alloc_1> &right, const Matrix<T2, Alloc_2> &left) {

        typedef decltype(T1() + T2()) T3;
        if ((right.m_rows != left.m_rows) || (right.m_columns != left.m_columns)) {
            throw LinAlgError("Not equal sizes, operation == can not be done", 18);
        }

        for (int i = 0; i < right.m_rows; i++) {
            for (int k = 0; k < right.m_columns; k++) {
                if (std::fabs(T3(right(i, k)) - T3(left(i, k))) >= std::numeric_limits<double>::epsilon()) {
                    return 0;
                }
            }
        }
        return 1;
    }
}
//----------------------------------------|векторы|-----------------------------------------------


#include<math.h>

namespace linalg {
//Евклидова норма
    template<typename T, typename Alloc>
    // Оператор перемножения матрицы на число (разных типов)
    double norm(const Matrix<T, Alloc> &obj) {
        if (obj.get_columns() != 1)
            throw LinAlgError("Is not a vector, normalization is impossible",
                              1);// тут должна быть проверка линилж еррор на то что это вектор, те либо столбцы либо строки равны 1
        double norma = 0;
        for (int i = 0; i < obj.get_rows(); ++i) {
            norma += pow(obj(i, 0), 2);
        }
        return std::pow(norma, 0.5);
    }

    template<typename T1, typename A1, typename T2, typename A2>
    double multy_scalar(const Matrix<T1, A1> &obj1, const Matrix<T2, A2> &obj2) {
        if (obj1.get_columns() != 1) throw LinAlgError("obj1 is not a vector, scalar multiplication is impossible", 2);
        if (obj2.get_columns() != 1) throw LinAlgError("obj2 is not a vector, scalar multiplication is impossible", 3);
        if (obj1.get_rows() != obj2.get_rows())
            throw LinAlgError("Number of rows is not equal, scalar multiplication is impossible", 4);

        //проверка на вектор и  совпадение колва строк
        double scal = 0;
        for (int i = 0; i < obj1.get_rows(); ++i) {
            scal += obj1(i, 0) * obj2(i, 0);
        }
        return scal;
    }

    template<typename T1, typename A1, typename T2, typename A2>
    double angle(const Matrix<T1, A1> &obj1, const Matrix<T2, A2> &obj2) {
        return acos(multy_scalar(obj1, obj2) / ((norm(obj1) * norm(obj2))));
    }

    template<typename T1, typename A1, typename T2, typename A2>
    auto multy_vector(const Matrix<T1, A1> &obj1, const Matrix<T2, A2> &obj2) -> Matrix<decltype(T1() * T2())> {
        Matrix<decltype(T1() * T2())> temp(3, 1);
        if (obj1.get_columns() != 1) throw LinAlgError("obj1 is not a vector, vector multiplication is impossible", 5);
        if (obj2.get_columns() != 1) throw LinAlgError("obj2 is not a vector, vector multiplication is impossible", 6);
        if (obj1.get_rows() != 3)
            throw LinAlgError("Dimension vector obj1 is not 3, vector multiplication is impossible", 7);
        if (obj2.get_rows() != 3)
            throw LinAlgError("Dimension vector obj3 is not 3, vector multiplication is impossible", 8);

        //проверка на вектора и что вектора размерности три
        for (int i = 0; i < obj1.get_rows(); ++i) {
            temp(i, 0) = obj1((1 + i) % 3, 0) * obj2((2 + i) % 3, 0) - obj1((2 + i) % 3, 0) * obj2((1 + i) % 3, 0);
        }
        return temp;
    }

    template<typename T, typename Alloc>
    auto unit(const Matrix<T, Alloc> &obj) -> Matrix<decltype(T() * double())> {
        if (int a = obj.get_columns() != 1)
            throw LinAlgError("Is not a vector, cannot find unit vector",
                              9);// тут должна быть проверка линилж еррор на то что это вектор, те либо столбцы либо строки равны 1
        double koef = (1.0 / norm(obj));
        Matrix<decltype(T() * double())> temp = obj * koef;
        return temp;
    }
}
