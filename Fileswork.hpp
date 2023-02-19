//
// Functionality to write Matrix to file and read it from it
//

#pragma once
#include <iostream>
#include <fstream>
#include "cstring"
#include "Complex.hpp"
#include "Matrix.h"

using namespace std;
using namespace linalg;

template<typename T> struct BinaryMode {};
template<typename T> struct TextMode {};

template<> struct BinaryMode<int> {
    static void write(const char* file_name, const Matrix<int>& object) {
        std::ofstream fbout(file_name, std::ios::binary);
        size_t rows = object.get_rows();
        size_t columns = object.get_columns();
        fbout.write(reinterpret_cast<char*>(&rows), sizeof(size_t));
        fbout.write(reinterpret_cast<char*>(&columns), sizeof(size_t));
        for (size_t col = 0; col < columns; ++col) {
            for (size_t row = 0; row < rows; ++row) {
                fbout.write(reinterpret_cast<const char*>(&object(row, col)), sizeof(int));
            }
        }
        fbout.close();
    }
    static Matrix<int> read(const char* file_name) {
        std::ifstream fbin(file_name, std::ios::binary);
        size_t rows;
        fbin.read(reinterpret_cast<char*>(&rows), sizeof(size_t));
        size_t columns;
        fbin.read(reinterpret_cast<char*>(&columns), sizeof(size_t));
        Matrix<int> obj_new(rows, columns);
        int temp;
        for (size_t col = 0; col < columns; ++col) {
            for (size_t row = 0; row < rows; ++row) {
                fbin.read(reinterpret_cast<char*>(&temp), sizeof(int));
                obj_new(row, col) = temp;
            }
        }
        fbin.close();
        return obj_new;
    }
};

template<> struct TextMode<int> {
    static void write(const char* file_name, const Matrix<int>& object) {
        std::ofstream fout;
        fout.open(file_name, std::ios::out);
        fout<<"type: "<<typeid(int).name()<<endl<<"rows: "<<object.get_rows()<<endl<<"columns: "<<object.get_columns()<<endl<<object;
        fout.close();
    }
    static Matrix<int>  read(const char* file_name) {
        std::ifstream fin;
        fin.open(file_name, std::ios::in);
        if (!fin.is_open()) { throw runtime_error("File not found");}
        std::string str;
        std::string word;
        std::getline(fin, str);

        std::getline(fin, str);
        word=str.substr(6);
        size_t rows=atoi(word.c_str());

        std::getline(fin, str);
        word=str.substr(9);
        size_t columns=atoi(word.c_str());

        Matrix<int> obj_new(rows, columns);
        int temp;
        for (size_t row = 0; row < rows; ++row) {
            std::getline(fin, str);
            str.erase(str.begin(), str.begin()+1);
            str.erase(str.end()-1, str.end());
            stringstream x;        //Создание потоковой переменной
            x << str;
            for (size_t col = 0; col < columns; ++col) {
                x >> word;
                obj_new(row, col) = atoi(word.c_str());
            }
        }
        fin.close();
        return obj_new;

    }
};

template<> struct BinaryMode<double> {
    static void write(const char* file_name, const Matrix<double>& object) {
        std::ofstream fbout(file_name, std::ios::binary);
        size_t rows = object.get_rows();
        size_t columns = object.get_columns();
        fbout.write(reinterpret_cast<char*>(&rows), sizeof(size_t));
        fbout.write(reinterpret_cast<char*>(&columns), sizeof(size_t));
        for (size_t col = 0; col < columns; ++col) {
            for (size_t row = 0; row < rows; ++row) {
                fbout.write(reinterpret_cast<const char*>(&object(row, col)), sizeof(double));
            }
        }
        fbout.close();
    }
    static Matrix<double> read(const char* file_name) {
        std::ifstream fbin(file_name, std::ios::binary);
        size_t rows;
        fbin.read(reinterpret_cast<char*>(&rows), sizeof(size_t));
        size_t columns;
        fbin.read(reinterpret_cast<char*>(&columns), sizeof(size_t));
        Matrix<double> obj_new(rows, columns);
        double temp;
        for (size_t col = 0; col < columns; ++col) {
            for (size_t row = 0; row < rows; ++row) {
                fbin.read(reinterpret_cast<char*>(&temp), sizeof(double));
                obj_new(row, col) = temp;
            }
        }
        fbin.close();
        return obj_new;

    }
};

template<> struct TextMode<double> {
    static void write(const char* file_name, const Matrix<double>& object) {
        std::ofstream fout;
        fout.open(file_name, std::ios::out);
        fout<<"type: "<<typeid(double).name()<<endl<<"rows: "<<object.get_rows()<<endl<<"columns: "<<object.get_columns()<<endl<<object;
        fout.close();
    }
    static Matrix<double>  read(const char* file_name) {
        std::ifstream fin;
        fin.open(file_name, std::ios::in);
        std::string str;
        std::string word;
        std::getline(fin, str);

        std::getline(fin, str);
        word=str.substr(6);
        size_t rows=atoi(word.c_str());

        std::getline(fin, str);
        word=str.substr(9);
        size_t columns=atoi(word.c_str());

        Matrix<double> obj_new(rows, columns);
        double temp;
        for (size_t row = 0; row < rows; ++row) {
            std::getline(fin, str);
            str.erase(str.begin(), str.begin()+1);
            str.erase(str.end()-1, str.end());
            stringstream x;        //Создание потоковой переменной
            x << str;
            for (size_t col = 0; col < columns; ++col) {
                x >> word;
                obj_new(row, col) = atof(word.c_str());
            }
        }
        fin.close();
        return obj_new;

    }
};

template<> struct BinaryMode<Complex<int>> {
    static void write(const char* file_name, const Matrix<Complex<int>>& object) {
        std::ofstream fbout(file_name, std::ios::binary);
        size_t rows = object.get_rows();
        size_t columns = object.get_columns();
        fbout.write(reinterpret_cast<char*>(&rows), sizeof(size_t));
        fbout.write(reinterpret_cast<char*>(&columns), sizeof(size_t));
        for (size_t col = 0; col < columns; ++col) {
            for (size_t row = 0; row < rows; ++row) {
                fbout.write(reinterpret_cast<const char*>(&object(row, col)), sizeof(Complex<int>));
            }
        }
        fbout.close();
    }
    static Matrix<Complex<int>> read(const char* file_name) {
        std::ifstream fbin(file_name, std::ios::binary);
        size_t rows;
        fbin.read(reinterpret_cast<char*>(&rows), sizeof(size_t));
        size_t columns;
        fbin.read(reinterpret_cast<char*>(&columns), sizeof(size_t));
        Matrix<Complex<int>> obj_new(rows, columns);
        Complex<int> temp;
        for (size_t col = 0; col < columns; ++col) {
            for (size_t row = 0; row < rows; ++row) {
                fbin.read(reinterpret_cast<char*>(&temp), sizeof(Complex<int>));
                obj_new(row, col) = temp;
            }
        }
        fbin.close();
        return obj_new;

    }
};

template<> struct TextMode<Complex<int>> {
    static void write(const char* file_name, const Matrix<Complex<int>>& object) {
        std::ofstream fout;
        fout.open(file_name, std::ios::out);
        fout<<"type: "<<typeid(Complex<int>).name()<<endl<<"rows: "<<object.get_rows()<<endl<<"columns: "<<object.get_columns()<<endl<<object;
        fout.close();
    }
    static Matrix<Complex<int>>  read(const char* file_name) {
        std::ifstream fin;
        fin.open(file_name, std::ios::in);
        std::string str;
        std::string word;
        std::getline(fin, str);

        std::getline(fin, str);
        word=str.substr(6);
        size_t rows=atoi(word.c_str());

        std::getline(fin, str);
        word=str.substr(9);
        size_t columns=atoi(word.c_str());

        Matrix<Complex<int>> obj_new(rows, columns);
        for (size_t row = 0; row < rows; ++row) {
            std::getline(fin, str);
            str.erase(str.begin(), str.begin()+1);
            str.erase(str.end()-1, str.end());
            stringstream x;        //Создание потоковой переменной
            x << str;
            for (size_t col = 0; col < columns; ++col) {
                Complex<int> a;
                x >>a;
                x >>str;
                obj_new(row, col) = a;
            }
        }
        fin.close();
        return obj_new;

    }
};

template<> struct BinaryMode<Complex<double>> {
    static void write(const char* file_name, const Matrix<Complex<double>>& object) {
        std::ofstream fbout(file_name, std::ios::binary);
        size_t rows = object.get_rows();
        size_t columns = object.get_columns();
        fbout.write(reinterpret_cast<char*>(&rows), sizeof(size_t));
        fbout.write(reinterpret_cast<char*>(&columns), sizeof(size_t));
        for (size_t col = 0; col < columns; ++col) {
            for (size_t row = 0; row < rows; ++row) {
                fbout.write(reinterpret_cast<const char*>(&object(row, col)), sizeof(Complex<double>));
            }
        }
        fbout.close();
    }
    static Matrix<Complex<double>> read(const char* file_name) {
        std::ifstream fbin(file_name, std::ios::binary);
        size_t rows;
        fbin.read(reinterpret_cast<char*>(&rows), sizeof(size_t));
        size_t columns;
        fbin.read(reinterpret_cast<char*>(&columns), sizeof(size_t));
        Matrix<Complex<double>> obj_new(rows, columns);
        Complex<double> temp;
        for (size_t col = 0; col < columns; ++col) {
            for (size_t row = 0; row < rows; ++row) {
                fbin.read(reinterpret_cast<char*>(&temp), sizeof(Complex<double>));
                obj_new(row, col) = temp;
            }
        }
        fbin.close();
        return obj_new;

    }
};

template<> struct TextMode<Complex<double>> {
    static void write(const char* file_name, const Matrix<Complex<double>>& object) {
        std::ofstream fout;
        fout.open(file_name, std::ios::out);
        fout<<"type: "<<typeid(Complex<double>).name()<<endl<<"rows: "<<object.get_rows()<<endl<<"columns: "<<object.get_columns()<<endl<<object;
        fout.close();
    }
    static Matrix<Complex<double>>  read(const char* file_name) {
        std::ifstream fin;
        fin.open(file_name, std::ios::in);
        std::string str;
        std::string word;
        std::getline(fin, str);

        std::getline(fin, str);
        word=str.substr(6);
        size_t rows=atoi(word.c_str());

        std::getline(fin, str);
        word=str.substr(9);
        size_t columns=atoi(word.c_str());

        Matrix<Complex<double>> obj_new(rows, columns);
        for (size_t row = 0; row < rows; ++row) {
            std::getline(fin, str);
            str.erase(str.begin(), str.begin()+1);
            str.erase(str.end()-1, str.end());
            stringstream x;        //Создание потоковой переменной
            x << str;
            for (size_t col = 0; col < columns; ++col) {
                Complex<double> a;
                x >>a;
                x >> str;
                cout<<str;
                obj_new(row, col) = a;
            }
        }
        fin.close();
        return obj_new;

    }
};