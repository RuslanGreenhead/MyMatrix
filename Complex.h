//
// Complex number class declaration
//

#pragma once
#include <iostream>
using namespace std;


template<typename T=double>
class Complex
{
public:
    explicit Complex(double real_p = 0, double imag_p = 0);    //Default constructor
    Complex(const Complex& obj);                               //Copy constructor

    template<typename T_1>                                     //Copy constructor (another template)
    Complex(const Complex<T_1>& obj);

    T real() const noexcept;                                   //Return real part

    template<typename T_1>                                     //Edit real part
    void real(T_1&& obj);

    T imag() const noexcept;                                   //Return imaginary part

    template<typename T_1>                                     //Edit imaginary part
    void imag(T_1&& obj);

    template<typename T_1> friend class Complex;               //Make friend class for our class

    template<typename T_1>                                     //Complex = Complex
    Complex& operator=(const Complex<T_1>& obj);

    template<typename T_1>                                     //Complex = real
    Complex& operator=(const T_1& obj);

    template<typename T_1>                                     // Complex *= real
    Complex& operator *= (const T_1& obj);

    template<typename T_1>                                     // Complex += real
    Complex& operator += (const T_1& obj);

    template<typename T_1>                                     // Complex -= real
    Complex& operator -= (const T_1& obj);

    template<typename T1, typename T2> //global real * Complex
    friend Complex<decltype(T1() + T2())> operator *(const T1 & left, const Complex<T2> & right);

    template<typename T1, typename T2> //global Complex * real
    friend Complex<decltype(T1() + T2())> operator *(const Complex<T1> & left, const T2 & right);

    template<typename T1, typename T2> //global Complex + real
    friend Complex<decltype(T1() + T2())> operator +(const Complex<T1> & left, const T2 & right);

    template<typename T1, typename T2> //global real + Complex
    friend Complex<decltype(T1() + T2())> operator +(const T2 & left, const Complex<T1> & right);

    template<typename T1, typename T2> //global Complex - real
    friend Complex<decltype(T1() + T2())> operator -(const Complex<T1> & left, const T2 & right);

    template<typename T1, typename T2> //global real - Complex
    friend Complex<decltype(T1() + T2())> operator -(const T2 & left, const Complex<T1> & right);

    template<typename T2> //Complex += Complex
    Complex& operator += (const Complex<T2> & obj);

    template<typename T2> //Complex -= Complex
    Complex& operator -= (const Complex<T2> & obj);

    template<typename T2> //Complex *= Complex
    Complex& operator *= (const Complex<T2> & obj);

    template<typename T1, typename T2> //global Complex + Complex
    friend Complex<decltype(T1() + T2())> operator + (const Complex<T1> & left, const Complex<T2> & right);

    template<typename T1, typename T2> //global Complex - Complex
    friend Complex<decltype(T1() + T2())> operator - (const Complex<T1> & left, const Complex<T2> & right);

    template<typename T1, typename T2> //global Complex * Complex
    friend Complex<decltype(T1() + T2())> operator * (const Complex<T1> & left, const Complex<T2> & right);

    template<typename T1> //Overloaded global operator « for print complex
    friend ostream & operator << (ostream &out, const Complex<T1> &obj);

    template<typename T1> //Overloaded global operator » for print complex
    friend istream & operator >> (istream &in, Complex<T1> &obj);
private:
    T m_real;
    T m_imag;
};