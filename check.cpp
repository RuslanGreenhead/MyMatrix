#include "Matrix_utilities.h"
#include "Matrix_utilites_additional.h"
#include "Allocator_other.h" // другой алокатор, для проверки работы с другим (а не тем, что по умолчанию)

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <string>

void test_1(){
    Matrix<int> E { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
    Matrix<int> m1 { {1, 2, 3}, {4, 5, 6},{7, 8, 9}};
    Matrix<int> m2 { {1, 2, 0}, {0, 33, 0},{0, 0, 4}};
    Matrix<> m3 { {0.0, 2.3, 0.0}, {0.0, 33.2, 0.0},{0.0, 0.0, 4.1}};
    Matrix<int> m4 { {0, 4, 0}, {0, 3, 0},{0, 0, 0}};
    Matrix<> m5 { {13, 4, 0}, {0, 3, 0},{0, 0, -8}};


    cout << m1  << m1.minor(0,0);

    int a = m2.det();
    cout << m2  << a;

    cout << m4.rank() << std::endl;

    cout << m5.norm() << std::endl;
    cout << E.norm();

    cout << E.trace()<< endl;

    cout << transpose(m1) << endl;

    cout<< inv(m5);

    cout << pow (m5, 3)<< endl << m5 * m5 * m5;

}