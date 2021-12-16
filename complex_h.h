#include <iostream>
#pragma once
using namespace std;



template<typename T=double>
class Complex
{
private:
    T m_real;
    T m_imag;
public:
    explicit Complex(double real_p = 0, double imag_p = 0);  //Default constructor


    Complex(const Complex & obj); //Copy construct

    template<typename T2> //Copy construct another class
    Complex(const Complex<T2> & obj);


    T real() const noexcept; //Return real part

    template<typename T1> //edit real part
    void real(T1 && obj);


    T imag() const noexcept; //Return imag part


    template<typename T1> //edit imag part
    void imag(T1 && obj);

    template<typename T2> friend class Complex; //Make friend class for our class

    template<typename T2> //Complex = Complex
    Complex& operator=(const Complex<T2> & obj);


    template<typename T2> //Complex = real
    Complex& operator=(const T2 & obj);


    template<typename T2> // Complex *= real
    Complex& operator *= (const T2 & obj);


    template<typename T2> // Complex += real
    Complex& operator += (const T2 & obj);


    template<typename T2> // Complex -= real
    Complex& operator -= (const T2 & obj);


    template<typename T1, typename T2> //global real * Complex
    friend Complex<decltype(T1() + T2())> operator *(const  T1 & left, const Complex<T2> & right);

    template<typename T1, typename T2> //global Complex * real
    friend Complex<decltype(T1() + T2())> operator *(const  Complex<T1> & left, const T2 & right);

    template<typename T1, typename T2> //global Complex + real
    friend Complex<decltype(T1() + T2())> operator +(const  Complex<T1> & left, const T2 & right);

    template<typename T1, typename T2> //global real + Complex
    friend Complex<decltype(T1() + T2())> operator +(const  T2 & left, const Complex<T1> & right);

    template<typename T1, typename T2> //global Complex - real
    friend Complex<decltype(T1() + T2())> operator -(const  Complex<T1> & left, const T2 & right);

    template<typename T1, typename T2> //global real - Complex
    friend Complex<decltype(T1() + T2())> operator -(const  T2 & left, const Complex<T1> & right);


    template<typename T2> //Complex += Complex
    Complex& operator += (const Complex<T2> & obj);


    template<typename T2> //Complex -= Complex
    Complex& operator -= (const Complex<T2> & obj);


    template<typename T2> //Complex *= Complex
    Complex& operator *= (const Complex<T2> & obj);



    template<typename T1, typename T2> //global Complex + Complex
    friend Complex<decltype(T1() + T2())> operator +(const Complex<T1> & left, const Complex<T2> & right);

    template<typename T1, typename T2> //global Complex - Complex
    friend Complex<decltype(T1() + T2())> operator -(const Complex<T1> & left, const Complex<T2> & right);

    template<typename T1, typename T2> //global Complex * Complex
    friend Complex<decltype(T1() + T2())> operator *(const Complex<T1> & left, const Complex<T2> & right);

    template<typename T1> //Overloaded global operator << for print complex
    friend ostream & operator<< (ostream &out, const Complex<T1> &obj);

    template<typename T1> //Overloaded global operator >> for print complex
    friend Complex<T> operator >> (istream &in, const Complex<T1> &obj);

};

#include "complex_h.h"
