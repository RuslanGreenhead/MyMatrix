#include "Matrix_utilities.h"
#include "Matrix_utilites_additional.h"
#include "Allocator_other.h"
#include "Complex.h"
#include "Complex.hpp"
#include "Fileswork.hpp"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <string>

// Расширенный функционал для матрицы
void test_1(){
    Matrix<int> E { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
    Matrix<int> m1 { {1, 2, 3}, {4, 5, 6},{7, 8, 9}};
    Matrix<int> m2 { {1, 2, 0}, {0, 33, 0},{0, 0, 4}};
    Matrix<> m3 {{0.0, 2.3, 0.0}, {0.0, 33.2, 0.0},{0.0, 0.0, 4.1}};
    Matrix<int> m4 { {0, 4, 0}, {0, 3, 0},{0, 0, 0}};
    Matrix<int> m5 { {13, 4, 0}, {0, 3, 0},{0, 0, -8}};
    Matrix<double> m6 { {13.0, 4.0, 0.0}, {0.0, 3.0, 0.0},{0.0, 0.0, -8.0}};

    cout << m1  << m1.minor(1,1);

    cout << "m2.det()"<< std::endl;
    cout << m2.det()<< std::endl;

    cout <<"m4" << endl << m4 << "m4.rank()" << std::endl;
    cout << m4.rank() << std::endl;

    cout << "m5.norm()" << std::endl;
    cout << m5.norm() << std::endl<< std::endl;

    cout <<" E.norm()"<< std::endl;
    cout << E.norm()<< std::endl<< std::endl;

    cout << "E.trace()"<< endl;
    cout << E.trace()<< endl<< std::endl;

    cout << "transpose(m1)" << endl;
    cout << transpose(m1);

    cout<< "inv(m5);" << endl;
    cout<< inv(m5) <<"m5 * inv(m5)"<<endl<< m5 * inv(m5);

    cout<< "pow (m5, 3)" << endl << pow (m5, 3)<< endl << "m5 * m5 * m5"<< endl << m5 * m5 * m5<< endl;
}

// Логическое сравнение матриц
void test_2(){
    Matrix<int> m5 { {13, 4, 0}, {0, 3, 0},{0, 0, -8}};
    Matrix<double> m6 { {13.0, 4.0, 0.0}, {0.0, 3.0, 0.0},{0.0, 0.0, -8.0}};
    Matrix<double> m7 { {13.1, 4.0, 0.0}, {0.0, 3.0, 0.0},{0.0, 0.0, -8.0}};

    cout  << "result of int(m5 == m6):"<< int(m5 == m6)<< endl;
    cout  << "result of int(m5 == m7):"<< int(m5 == m7)<< endl;

    cout << "result of inv(transpose(m6)) == transpose(inv(m6)):" << int (inv(transpose(m6)) == transpose(inv(m6)))<< endl;

    cout << "result of int (inv(m6 * m5) == inv(m6) * inv(m5))):"<< int (inv(m6 * m5) == inv(m6) * inv(m5))<< endl;};

//  Функционал для векторов
void test_3(){
    Matrix<int> m1  {1, 1, 1};
    Matrix<> m2  {1.1, 2.2, 3.3};

    Matrix<int> m3 = {1, 0, 0};
    Matrix<int> m4 = {-1, 0, 0};

    cout << "m1.norm()"<< std::endl;
    cout << m1.norm()<< std::endl;

    cout << "angle(m1, m2)"<< std::endl;
    cout << angle(m1, m2)<< std::endl;

    cout << "multy_vector(m1, m2)"<< std::endl;
    cout << multy_vector(m1, m2)<< std::endl;

    cout << "multy_scalar(m1, m2)"<< std::endl;
    cout << multy_scalar(m1, m2)<< std::endl;

    cout << "unit(m1)"<< std::endl;
    cout << unit(m1)<< std::endl;

    cout << "multy_vector(m3, m4) // collinear"<< std::endl;
    cout << multy_vector(m3, m4) << std::endl;

};

// Решение СЛАУ
void test_4(){
    Matrix<int> vec1  {1, 1, 1};
    Matrix<int> E { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };

    cout  << "solve (E, vec1):" << endl << solve (E, vec1)<< endl;

    Matrix<double> vec2  {1, 2, 3};
    Matrix<int> m1 { {1, 2, 3}, {4, 1, 0}, {0, 0, 8} };

    cout  << "solve (m1, vec2):" << endl << solve (m1, vec2)<< endl;

};

// Различные ошибки
void test_5(){
    Matrix<int> m1 { {1, 0},{ 0, 0},{ 1, 0} };
    Matrix<int> m2 { {1, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    Matrix<int> m3 { {1, 0}, {0, 5} };
    Matrix<int> E { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
    Matrix<int> vec { 1,2,3};
    Matrix<int> vec2 { 1,2};
//    m1.det();

//    m1.minor(0,6);
//    m1.minor(6,0);
//
//    m1.trace();
//
//    inv(m1);
//    inv(m2);

//    solve(E, m1);// не вектор
//    solve(m3,vec);// разные размеры матрицы и вектора
//    solve(m2,vec); // det = 0
//    solve(m1,vec);// не квадратная матрица

//    m1 == m2;

//    norm(m1); // это норма для вектора!!! m1.norma для матрицы

//    multy_scalar(m1, vec);
//    multy_scalar(vec, m1);
//    multy_scalar(vec, vec2);

//    multy_vector(m1, vec);
//    multy_vector(vec, m1);
//    multy_vector(vec, vec2);
//    multy_vector(vec2, vec);

//    unit(m1);
};

// Комплексные числа
void test_6(){
    Complex<int> A;
    cout << "Complex<int> A: " << A << endl;
    Complex<short> B(1);
    cout << "Complex<short> B(1): " << B << endl;
    Complex<> C(1, -2);
    cout << "Complex<> C(1, -2): " << C << endl;
    double r = C.real();
    double i = C.imag();
    cout << "r = " << r << ", i = " << i << endl;
    C.real(10);
    C.imag(7);
    cout << "C = " << C << endl;
    C += -2;
    cout << "C = " << C << endl;
    C *= Complex<int>(-1, -1);
    cout << "C = " << C << endl;
    cout << "C * 1: " << C * 1 << endl;
    cout << "2.0 * C: " << 2.0 * C << endl;
    Complex<> D(5, -5);
    cout << "C * D: " << C * D << endl;
    cin >> C;
    cout << C;
};

// Работа с файлами
void test_7(){
    Matrix<Complex<int>> A = {{Complex<int>(14, -11), Complex<int>(3, 4)}, {Complex<int>(), Complex<int>(5)}};
    cout << A << endl;
    TextMode<Complex<int>>::write("test.txt", A);
    auto B = TextMode<Complex<int>>::read("test.txt");
    cout << B << endl;

    BinaryMode<Complex<int>>::write("test_1.bin", A);
    Matrix<Complex<int>> C = BinaryMode<Complex<double>>::read("test_1.bin");
    cout << C << endl;
};

void test_8(){
    Matrix<int> A = {1};
    cout << A.det();
}