//
// Complex number class implementation
//

#pragma once
#include "Complex.h"


template<typename T>
Complex<T>::Complex(double real_p, double imag_p){
    m_real = T(real_p);
    m_imag = T(imag_p);
}

template<typename T>
Complex<T>::Complex(const Complex & obj){  //Copy construct
    m_real = obj.m_real;
    m_imag = obj.m_imag;
}

template<typename T>
template<typename T2>
Complex<T>::Complex(const Complex<T2> & obj){ //Copy construct another class
    m_real = obj.m_real;
    m_imag = obj.m_imag;
}

template<typename T>
T Complex<T>::real() const noexcept{ //Return real part
    return m_real;
}

template<typename T>
template<typename T1> //edit real part
void Complex<T>::real(T1 && obj){
    m_real = decltype(T(), T1())(obj);
}

template<typename T>
T Complex<T>::imag() const noexcept{  //Return imag part
    return m_imag;
}

template<typename T>
template<typename T1>  //Edit imag part
void Complex<T>::imag(T1 && obj){
    m_imag = decltype(T(), T1())(obj);
}

template<typename T>
template<typename T2> //Complex = Complex
Complex<T>& Complex<T>::operator=(const Complex<T2> & obj){
    m_real = obj.m_real;
    m_imag = obj.m_imag;
    return *this;
}

template<typename T>
template<typename T2> //Complex = real
Complex<T>& Complex<T>::operator=(const T2 & obj){
    m_real = obj;
    return *this;
}

template<typename T>
template<typename T2> // Complex *= real
Complex<T>& Complex<T>::operator *= (const T2 & obj){
    m_real *= obj;
    m_imag *= obj;
    return *this;
}

template<typename T>
template<typename T2> // Complex += real
Complex<T>& Complex<T>::operator += (const T2 & obj){
    m_real += obj;
    return *this;
}

template<typename T>
template<typename T2> // Complex -= real
Complex<T>& Complex<T>::operator -= (const T2 & obj){
    m_real -= obj;
    return *this;
}

template<typename T1, typename T2> //global real * Complex
Complex<decltype(T1() + T2())> operator *(const T1 & left, const Complex<T2> & right){
    Complex<decltype(T1() + T2())> tmp(right);
    tmp *= left;
    return tmp;
}

template<typename T1, typename T2> //global Complex * real
Complex<decltype(T1() + T2())> operator *(const Complex<T1> & left, const T2 & right){
    Complex<decltype(T1() + T2())> tmp(left);
    tmp *= right;
    return tmp;
}

template<typename T1, typename T2> //global Complex + real
Complex<decltype(T1() + T2())> operator +(const Complex<T1> & left, const T2 & right){
    Complex<decltype(T1() + T2())> tmp(left);
    tmp += right;
    return tmp;
}

template<typename T1, typename T2> //global real + Complex
Complex<decltype(T1() + T2())> operator +(const T2 & left, const Complex<T1> & right){
    Complex<decltype(T1() + T2())> tmp(right);
    tmp += left;
    return tmp;
}

template<typename T1, typename T2> //global Complex - real
Complex<decltype(T1() + T2())> operator -(const Complex<T1> & left, const T2 & right){
    Complex<decltype(T1() + T2())> tmp(left);
    tmp -= right;
    return tmp;
}

template<typename T1, typename T2> //global real - Complex
Complex<decltype(T1() + T2())> operator -(const T2 & left, const Complex<T1> & right){
    Complex<decltype(T1() + T2())> tmp(right);
    tmp.m_real = left - tmp.m_real;
    return tmp;
}

template<typename T>
template<typename T2> //Complex += Complex
Complex<T>& Complex<T>::operator += (const Complex<T2> & obj){
    m_real += obj.m_real;
    m_imag += obj.m_imag;
    return *this;
}

template<typename T>
template<typename T2> //Complex -= Complex
Complex<T>& Complex<T>::operator -= (const Complex<T2> & obj){
    m_real -= obj.m_real;
    m_imag -= obj.m_imag;
    return *this;
}

template<typename T>
template<typename T2> //Complex *= Complex
Complex<T>& Complex<T>::operator *= (const Complex<T2> & obj){
    Complex<T> tmp;
    tmp.m_real = m_real * obj.m_real - (m_imag * obj.m_imag);
    tmp.m_imag = m_real * obj.m_imag + m_imag * obj.m_real;
    *this = tmp;
    return *this;
}

template<typename T1, typename T2> //global Complex + Complex
Complex<decltype(T1() + T2())> operator +(const Complex<T1> & left, const Complex<T2> & right){
    Complex<decltype(T1() + T2())> tmp(left.m_real, left.m_imag);
    tmp += right;
    return tmp;
}

template<typename T1, typename T2> //global Complex - Complex
Complex<decltype(T1() + T2())> operator -(const Complex<T1> & left, const Complex<T2> & right){
    Complex<decltype(T1() + T2())> tmp(left.m_real, left.m_imag);
    tmp -= right;
    return tmp;
}

template<typename T1, typename T2> //Two Complex * Complex
Complex<decltype(T1() + T2())> operator *(const Complex<T1> & left, const Complex<T2> & right){
    Complex<decltype(T1() + T2())> tmp(left.m_real, left.m_imag);
    tmp *= right;
    return tmp;
}

template<typename T> //Overloaded global operator « for print complex
ostream & operator << (ostream &out, const Complex<T> &obj){
    out << obj.m_real << " ";
    if (obj.m_imag >= 0) out << "+ " << obj.m_imag << "*i";
    else out << "- " << (-1) * obj.m_imag << "*i";

    return out;
}

template<typename T> //Overloaded global operator » for print complex
istream & operator >> (istream &in, Complex<T> &obj){
    char tmp;
    T num;
    in >> num;

    obj.m_real = num;
    in >> tmp;
    if(tmp == '-' || tmp == '+'){
        in >> num;
        if (tmp == '-'){
            obj.m_imag = (-1) * num;
        }else{
            obj.m_imag = num;
        }
        in >> tmp;
        in >> tmp;
    }
    if(tmp == '*'){
        obj.m_imag = obj.m_real;
        obj.m_real = 0;
        in >> tmp;
    }

    return in;
}