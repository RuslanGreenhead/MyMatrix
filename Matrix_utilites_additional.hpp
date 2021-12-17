#pragma once

using std::runtime_error;

template <typename T, typename Alloc>
T Matrix<T, Alloc>::det()const {
    if ((m_columns == 2) && (m_rows == 2)){
        return (*this)(0,0) * (*this)(1,1) - (*this)(1,0) * (*this)(0,1);
    }

    T determinant = 0;

    for (int i = 0; i < m_rows; i++) {
        determinant += pow(-1 , i ) * (*this)(i,0) * (*this).minor(i,0).det();
    };


    return determinant;
}

template <typename T, typename Alloc>
Matrix<T, Alloc> Matrix<T, Alloc>::minor(const int row, const int column) const {
    Matrix<T> result( m_columns - 1, m_rows - 1);

    int index_i =0,  index_k;

    for (int i = 0; i < result.m_rows; i++) {
        for (int k = 0; k < result.m_columns; k++) {

            if (i >= row ) index_i = 1;
            else index_i = 0;

            if (k >= column ) index_k = 1;
            else index_k = 0;


            (*this)(index_i,index_k);
            result(i, k);
            result(i, k) = (*this)(i + index_i, k + index_k);

            ++ index_i;
            ++ index_k;
        }
    }


    return result;
}

template <typename T, typename Alloc>
int Matrix<T, Alloc>::rank() const {

    Matrix < decltype(T() + double()) > temp ((*this));
    T result =0 ;

    for (int i = 0; i < temp.m_rows; i++) {


        for (int k = 0; k < temp.m_columns; k++) {
            try{
                if ((*this)(i, i) == 0) throw std::runtime_error("O");
                temp(i, k) = temp(i, k) / (*this)(i, i);
            }
            catch (runtime_error err){
                for (int h = i; h < temp.m_columns; h++) {
                    if (temp(i,h) != 0){
                        for (int m = i; m < temp.m_rows; m++) {
                            T cell_temp;
                            cell_temp = temp(m,h);
                            temp(m,h) = temp(m,i);
                            temp(m,i) = cell_temp;
                        }
                    }

                    else{continue;}
                }
            }}


        for (int k = i; k < temp.m_rows; k++) {
            for (int j = i; j < temp.m_rows; j++) {
                if ((i != k) && (i != 100)) temp(k, j) = temp(k, j) - temp(i, j) * temp(k, i) ;
            }
        }}

    for (int i = 0; i < temp.m_rows; i++) {
        if (temp(i,i) != 0) ++result;
    }

    return result;
}

template <typename T, typename Alloc>
double Matrix<T, Alloc>::norm() const {
    double result = 0;

    for (int i = 0; i < m_rows; i++) {
        for (int k = 0; k < m_columns; k++) {
            result += (*this)(i,k) * (*this)(i,k);
        }
    }


    return  pow(result, 0.5);
}

template <typename T1, typename Alloc>
double Matrix<T1, Alloc>::trace() const {
    double result;
    for (int i = 0; i < (*this).m_rows; i++) {
        result += (*this)(i,i);
    }
    return result;
}

template <typename T1, typename Alloc>
Matrix<T1, Alloc> transpose(const Matrix<T1, Alloc> &obj) {
    Matrix<T1> result(obj.m_columns, obj.m_rows);

    for (int i = 0; i < obj.m_rows; i++) {
        for (int k = 0; k < obj.m_columns; k++) {
            result(i,k) += obj(k,i);
        }
    }

    return result;
}

template <typename T1, typename Alloc_1>
auto inv(const Matrix<T1, Alloc_1> &obj){

    Matrix< decltype(double() + T1()) > result (obj);

    double determ = obj.det();

    if (determ == 0) throw std::runtime_error("No Inv Matrix, det = 0");

    for (int i = 0; i < obj.m_rows; ++i){
        for (int k = 0; k < obj.m_columns;++k){
            result(i, k) = pow(-1, i+k) * transpose(obj).minor(i,k).det() / determ;
        }
    }

    return result;
}

template <typename T, typename Alloc>
Matrix<T, Alloc>  pow (const Matrix<T, Alloc> &obj,  size_t number){
Matrix<T> result (obj);

for (size_t i =0; i < number - 1; i++){
    result *= obj;
}
    return result;
}

template <typename T1, typename Alloc_1, typename T2, typename Alloc_2>
auto  solve (const Matrix<T1, Alloc_1> &mat,  const Matrix<T2, Alloc_2> &vec){

    // проверка на то что вектор это вектор
    // проверка на соответствие размеров
    // проверка на дет == 0

Matrix<> temp (mat);
Matrix<> result (mat.m_columns, 1);
double determ = temp.det();

for (int i =0;i < mat.m_columns; ++i){
    for (int j = 0; j < mat.m_rows; ++j) {temp(i,j) = vec(i,j);}
    result(i,1) = temp.det() / determ;
}
    return result;
}
//(row, ,column)
